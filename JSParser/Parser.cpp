#include"Parser.h"
#include"Tag.h"
#include"utils.h"

Parser::Parser(Lexer* l) :lex(l),top(nullptr),globalLE() {

}

void Parser::move() {
	look = lex->scan();
	if(look==nullptr){
		look = new Token(LAST);
	};

}

void Parser::singleLine(bool showTree) {

	move();

	Node * node = nullptr;
	switch (look->tag) {
	case VAR:
		node = parseVariableDeclaration();
		break;

	case FUNCTION:
		node = parseFunctionDeclaration();
		break;

	case '{':
	case IF:
	case DO:
	case WHILE:
	case FOR:
		node = parseStmt();
		break;

	default:
		node = parseSequenceExpr();
		break;
	}

	
	cout<<node->getValue()<<endl;

	if (showTree) { 
		cout << endl;
		node->display();
	}
}

void Parser::error(string s) {
	throw "Error: Near line " + toStr(lex->line) + ": " + s;
}

void Parser::match(int t) {
	if (t == look->tag) move();
	else error("can't match:"+toStr((char)t));
}

void Parser::run() {
	if (top) delete top;

	top = new Program();

	move();

	while (!lex->eof()) {
		Node* node = program();
		if (node) top->append(node);
	}
}

Node* Parser::program() {
	Node * node=nullptr;
	switch (look->tag) {
	case VAR:
		node = parseVariableDeclaration();
		if(look->tag ==';') match(';');
		break;

	case FUNCTION:
		node = parseFunctionDeclaration();
		break;

	case '{':
	case IF:
	case DO:
	case WHILE:
	case FOR:
		node = parseStmt();
		break;

	default:
		node = parseSequenceExpr();
		if(look->tag==';') match(';');
		break;
	}

	return node;
}

void Parser::display() {
	top->display();
}



StringConstant* Parser::parseStringConstant() {
	if (look->tag != STRING) {
		error("Unexpected token " + look->toString());
	}

	StringConstant* str = new StringConstant(look->toString());

	move();

	return str;
}

NumberLiteral* Parser::parseNumberLiteral() {
	if (look->tag != NUMBER) {
		error("Unexpected token " + look->toString());
	}

	NumberLiteral* ltrl = new NumberLiteral(look->getValue());
	
	move();
	
	return ltrl;
}

Identifier* Parser::parseIdentifier() {
	if (look->tag != ID) {
		error("Unexpected token " + look->toString());
	}
	string name = look->toString();

	unordered_map<string, Identifier*>::iterator got = globalLE.find(name);


	Identifier* id = nullptr;
	if (got == globalLE.end()) {
		id = new Identifier(name);
		globalLE.insert(pair<string, Identifier*>(name, id));
	}
	else {
		id = (*got).second;
	}

	move();
	
	return id;
}

VariableDeclaration* Parser::parseVariableDeclaration() {
	match(VAR);

	VariableDeclaration* variableDeclaration = new VariableDeclaration();

	VariableDeclarator* vd = nullptr;
	 do{
		vd = parseVariableDeclarator();
		if (look->tag == ',') {
			match(',');
		}
		variableDeclaration->append(vd);
	}while (look->tag == ID);
	
	return variableDeclaration;
}

VariableDeclarator* Parser::parseVariableDeclarator() {
	VariableDeclarator*  variableDeclaration=nullptr;//新结点
	Identifier* id=nullptr;//声明的变量

	if (look->tag == ID) {

		id = parseIdentifier();


		if (look->tag == '=') {
			match('=');
			
			Expr* expr = nullptr;

			if (look->tag == FUNCTION) {
				expr = parseFunctionExpr();
			}
			else {
				expr = parseExpr();
			}

			variableDeclaration = new VariableDeclarator(id, expr);
		}
		else {
			variableDeclaration = new VariableDeclarator(id, nullptr);
		}

	}
	else {
		error("Unexpected token " + look->toString());
	}

	return variableDeclaration;
}

FunctionDecl* Parser::parseFunctionDeclaration() {
	FunctionDecl* functionDecl = nullptr;
	
	match(FUNCTION);
	Identifier* id = parseIdentifier();
	functionDecl = new FunctionDecl(id);

	match('(');
	while (look->tag != ')') {
		Identifier* id = parseIdentifier();
		functionDecl->appendParam(id);
		if (look->tag == ',') {
			match(',');
		}
	}
	match(')');

	BlockStmt* body = parseBlockStmt(true);
	functionDecl->appendBody(body);

	return functionDecl;
}

Stmt* Parser::parseStmt() {
	Stmt* stmt = nullptr;

	switch (look->tag)
	{
	case '{':
		stmt = parseBlockStmt();
		break;

	case IF:
		stmt = parseIfStatement();
		break;

	case WHILE:
		stmt = parseWhileStmt();
		break;

	case DO:
		stmt = parseDoWhileStmt();
		match(';');
		break;

	case FOR:
		stmt = parseForStmt();
		break;

	default:
		error("Error in parseStmt");
		break;
	}

	return stmt;
}

BlockStmt* Parser::parseBlockStmt(bool canReturn) {

	BlockStmt* block = new BlockStmt();
	match('{');

	while (look->tag != '}') {
		Node* node = nullptr;
		switch (look->tag)
		{
		case VAR: 
			node = parseVariableDeclaration();
			if(look->tag==';') match(';');
			break;

		case FUNCTION:
			node = parseFunctionDeclaration();
			break;
		
		case IF:
		case WHILE:
		case DO:
		case FOR:
		case '{':
			node = parseStmt();
			break;

		case RETURN:
			if (canReturn) { 
				node = parseReturnStmt(); 
			}
			else {
				error("Illegal return statement");
			}
			break;

		default:
			node = parseSequenceExpr();
			if (look->tag == ';') match(';');
			break;
		}

		if(node) block->append(node);
	};

	match('}');
	return block;
}

IfStmt* Parser::parseIfStatement() {
	IfStmt* ifstmt = nullptr;

	match(IF);
	match('(');

	Expr* test = parseLogicExpr();
	if(!test)error("Unexpected Token:" + look->toString());
	match(')');
	Node* consequent = nullptr;
	if (look->tag == '{') {
		consequent = parseBlockStmt();
	}
	else {
		consequent = parseExpr();
		if(look->tag==';') match(';');
	}

	if (look!=nullptr && look->tag == ELSE) {
		move();
		Node * alternate = nullptr;
		if (look->tag == '{') {
			alternate = parseBlockStmt();
		}
		else {
			alternate = parseExpr();
			if (look->tag == ';') match(';');
		}
		ifstmt = new IfStmt(test, consequent, alternate);
	}
	else {
		ifstmt = new IfStmt(test, consequent, nullptr);
	}


	return ifstmt;
}

WhileStmt* Parser::parseWhileStmt() {
	WhileStmt* whilestmt = nullptr;
	
	match(WHILE);
	match('(');
	Expr* test = parseLogicExpr();
	if (!test) error("Unexpected Token:" + look->toString());

	match(')');
	Node* body = nullptr;
	if (look->tag == '{') {
		body = parseBlockStmt();
	}
	else {
		body = parseExpr();
		if(look->tag==';') match(';');
	}

	whilestmt = new WhileStmt(test, body);

	return whilestmt;
}

DoWhileStmt* Parser::parseDoWhileStmt() {
	DoWhileStmt* dowhilestmt = nullptr;

	match(DO);

	Node* body = parseBlockStmt();

	match(WHILE);
	match('(');
	Expr* test = parseLogicExpr();
	if(!test)error("Unexpected Token:" + look->toString());

	match(')');

	dowhilestmt = new DoWhileStmt(test, body);

	return dowhilestmt;
}

ForStmt* Parser::parseForStmt() {
	ForStmt* forstmt = nullptr;

	match(FOR);

	match('(');
	Node* init = nullptr;
	if (look->tag == VAR) {
		init = parseVariableDeclaration();
	}
	else {
		init = parseSequenceExpr();
	}
	match(';');

	Expr* test = parseLogicExpr();

	match(';');

	Expr* update = parseSequenceExpr();

	match(')');

	Node* body = nullptr;

	if (look->tag == '{') {
		body = parseBlockStmt();
	}
	else {
		body = parseExpr();
		if(look->tag==';') match(';');
	}

	forstmt = new ForStmt(body, init, test, update);

	return forstmt;
}

ReturnStmt* Parser::parseReturnStmt() {
	match(RETURN);
	Expr* expr = nullptr;
	if (look->tag != ';') {
		 expr = parseSequenceExpr();
	}

	ReturnStmt* returnStmt = new ReturnStmt(expr);

	return returnStmt;
}

Expr* Parser::parseExpr(bool shouldParseCall) {
	Expr* expr = nullptr;
	switch (look->tag)
	{
	case ID:
	case '-':
	case '+':
	case '!':
	case '(':
	case NUMBER:
	case TRUE:
	case FALSE:
		expr = parseLogicExpr();
		break;

	case '[':
		expr = parseArrayExpr();
		break;

	case ADD:
	case MINUS:
		expr = parseUpdateExpr();
		break;

	case NEW:
		expr = parseNewExpr();
		break;

	case '\"':
		match('\"');
		expr = parseStringConstant();
		match('\"');
		break;

	case '\'':
		match('\'');
		expr = parseStringConstant();
		match('\'');
		break;


	default:
		break;
	}

	if (shouldParseCall&&look->tag == '(') {
		expr = parseCallExpr(expr);
	}

	return expr;
}

Expr* Parser::parseSequenceExpr() {
	Expr* expr = nullptr;

	expr = parseExpr();

	if (!expr)error("Unexpected token " + look->toString());

	if (look->tag != ',') {
		return expr;
	}

	SequenceExpr* sequenceExpr = new SequenceExpr();
	sequenceExpr->append(expr);
	while (look->tag == ',') {
		match(',');
		expr = parseExpr();
		sequenceExpr->append(expr);
	}

	return sequenceExpr;
}

Expr* Parser::parseArrayExpr() {
	ArrayExpr* arrayExpr = new ArrayExpr();
	match('[');

	while (look->tag != ']') {
		Expr* element = parseExpr();
		arrayExpr->append(element);
		if (look->tag == ',') match(',');
	}
	match(']');

	return arrayExpr;
}

Expr* Parser::parseNewExpr() {

	match(NEW);

	Expr* callee = parseExpr(false);

	NewExpr* newExpr = new NewExpr(callee);

	if (look->tag == '(') {
		match('(');
		while (look->tag != ')') {
			Expr* argument = parseExpr();
			newExpr->append(argument);
			if (look->tag == ',') match(',');
		}
		match(')');
	}

	return newExpr;
}

Expr* Parser::parseCallExpr(Expr* callee) {
	CallExpr* callExpr = new CallExpr(callee);
	match('(');
	while (look->tag != ')') {
		Expr* argument = parseExpr();
		callExpr->append(argument);
		if (look->tag == ',') match(',');
	}
	match(')');

	return callExpr;
}

Expr* Parser::parseFunctionExpr() {
	FunctionExpr* functionExpr = nullptr;

	match(FUNCTION);
	Identifier* id = nullptr;
	if (look->tag == ID) {
	 id = parseIdentifier();
	}
	functionExpr = new FunctionExpr(id);

	match('(');
	while (look->tag != ')') {
		Identifier* id = parseIdentifier();
		functionExpr->appendParam(id);
		if (look->tag == ',') {
			match(',');
		}
	}
	match(')');

	BlockStmt* body = parseBlockStmt(true);
	functionExpr->appendBody(body);

	return functionExpr;
}

Expr* Parser::parseUpdateExpr(Expr* arg) {
	Expr* expr = nullptr;
	Token* op = look;

	Expr* argument = arg;

	bool prefix = (argument ==nullptr) ? true : false;

	if (prefix) {
		move();
		argument = parseIdentifier();
	}

	expr = new UpdateExpr(op, argument, prefix);
	
	move();

	return expr;
}

Expr* Parser::parseAssignmentExpr() {
	Expr* expr = nullptr;

	Identifier* id = parseIdentifier();

	if (look->tag == '=') {
		Token* eq = look;
		move();

		Expr* right =nullptr;

		if (look->tag == FUNCTION) {
			right = parseFunctionExpr();
		}
		else {
			right = parseExpr();
		}

		expr = new AssignmentExpr(eq, id, right);
	}
	else if(look->tag==ADD||look->tag==MINUS){
		expr = parseUpdateExpr(id);
	}
	else {
		expr = id;
	}

	return expr;
}

Expr* Parser::parseLogicExpr() {
	Expr* left = join();
	while (look->tag == OR) {
		Token* op = look;
		move();
		left = new LogicExpr(op, left, join());
	}

	return left;
}

Expr* Parser::join() {
	Expr* left = equality();
	while (look->tag == AND) {
		Token* op = look;
		move();
		left = new LogicExpr(op, left, equality());
	}

	return left;
}

Expr* Parser::equality() {
	Expr* left = rel();
	while (look->tag == EQ || look->tag == NE) {
		Token* op = look;
		move();
		left = new BinaryExpr(op, left, rel());
	}

	return left;
}

Expr* Parser::rel() {
	Expr* left = parseBinaryExpr();
	Token* op = nullptr;
	switch (look->tag)	
	{
	case '<':
	case LE:
	case GE:
	case '>':
		op = look;
		move();
		left = new BinaryExpr(op, left, parseBinaryExpr());
	default:
		break;
	}

	return left;
}

Expr* Parser::parseBinaryExpr() {

	Expr* left = nullptr;

	left = getTerm();
	
	Token* op = nullptr;

	while (look->tag == '+' || look->tag == '-') {
		op = look;
		move();
		left = new BinaryExpr(op, left, getTerm());
	}

	return left;
}

Expr* Parser::getTerm() {
	Expr* right = parseUnaryExpr();
	Token* op = nullptr;
	while (look->tag == '*' || look->tag == '/') {
		op = look;
		move();
		right = new BinaryExpr(op, right, parseUnaryExpr());
	}

	return right;
}

Expr* Parser::parseUnaryExpr() {
	Expr* unaryExpr = nullptr;
	if (look->tag == '-' || look->tag == '!' || look->tag == '+') {
		Token* op = look;

		move();
		Expr* argument = parseUnaryExpr();
		unaryExpr = new UnaryExpr(op, argument);

	}
	else if (look->tag == '(') {
		match('(');
		unaryExpr = parseLogicExpr();
		match(')');
	}
	else {
		switch (look->tag)
		{
		case NUMBER:
			unaryExpr = parseNumberLiteral();
			break;
		case ID:
			unaryExpr = parseAssignmentExpr();
			break;
		case TRUE:
			unaryExpr = new BoolLiteral("true");
			move();
			break;
		case FALSE:
			unaryExpr = new BoolLiteral("false");
			move();
			break;

		default:
			break;
		}
	}

	return unaryExpr;
}