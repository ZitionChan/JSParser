#include"Parser.h"
#include"Tag.h"
#include"utils.h"

Parser::Parser(Lexer& l) : lex(l), top(nullptr), globalLE() {}

Token* Parser::LookaheadLexer::peek() {
	if (look == nullptr) {
		cerr << "getting token... ";
		look = lex.scan();
		cerr << look->toString() << endl;
	}
	return look;
}

Token* Parser::peek(std::initializer_list<int> ts, bool ignoreNewLine) {
	if (ignoreNewLine) {
		while (tryMatch('\n', false))
			;
	}

	if (peek() == nullptr)
		return nullptr;

	for (int t : ts) {
		if (t == peek()->tag)
			return peek();
	}
	return nullptr;
}

void Parser::singleLine(bool showTree) {
	Node* node = program();

	if (node)
		cout << node->getValue() << endl;

	if (showTree) {
		cout << endl;
		node->display();
	}
}

void Parser::LookaheadLexer::error(string s) {
	throw "Error: Near line " + toStr(lex.line) + ": " + s;
}

Token* Parser::match(int t) {
	auto token = tryMatch(t);
	if (token == nullptr)
		error("can't match:" + toStr((char)t));

	return token;
}

Token* Parser::tryMatch(std::initializer_list<int> ts, bool ignoreNewLine) {
	auto token = peek(ts, ignoreNewLine);
	if (token == nullptr) {
		return nullptr;
	}
	move();
	return token;
}

Token* Parser::LookaheadLexer::move() {
	auto token = look;
	look = nullptr;
	return token;
}

void Parser::run() {
	if (top) delete top;

	top = new Program();

	while (peek()) {
		Node* node = program();
		if (node) top->append(node);
	}
}

Node* Parser::program() {
	Node* node;
	if (peek(VAR)) {
		node = parseVariableDeclaration();
		tryMatch(';');
	}
	else if (peek(FUNCTION))
		node = parseFunctionDeclaration();
	else if (peek({ '{', IF, DO, WHILE, FOR }))
		node = parseStmt();
	else {
		node = parseSequenceExpr();
		tryMatch(';');
	}

	return node;
}

void Parser::display() {
	top->display();
}

StringConstant* Parser::parseStringConstant() {
	auto token = match(STRING);

	StringConstant* str = new StringConstant(token->toString());

	return str;
}

NumberLiteral* Parser::parseNumberLiteral() {
	auto token = match(NUMBER);

	NumberLiteral* ltrl = new NumberLiteral(token->getValue());

	return ltrl;
}

Identifier* Parser::parseIdentifier() {
	auto token = match(ID);
	string name = token->toString();

	unordered_map<string, Identifier*>::iterator got = globalLE.find(name);


	Identifier* id = nullptr;
	if (got == globalLE.end()) {
		id = new Identifier(name);
		globalLE.insert(pair<string, Identifier*>(name, id));
	}
	else {
		id = (*got).second;
	}

	return id;
}

VariableDeclaration* Parser::parseVariableDeclaration() {
	match(VAR);

	VariableDeclaration* variableDeclaration = new VariableDeclaration();

	VariableDeclarator* vd = nullptr;
	do {
		vd = parseVariableDeclarator();
		tryMatch(',');
		variableDeclaration->append(vd);
	} while (peek(ID));

	return variableDeclaration;
}

VariableDeclarator* Parser::parseVariableDeclarator() {
	VariableDeclarator* variableDeclaration = nullptr; //新结点
	Identifier* id = nullptr;//声明的变量

	auto token = match(ID);

	id = parseIdentifier();

	if (tryMatch('=')) {
		Expr* expr = nullptr;

		if (peek(FUNCTION)) {
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

	return variableDeclaration;
}

FunctionDecl* Parser::parseFunctionDeclaration() {
	FunctionDecl* functionDecl = nullptr;

	match(FUNCTION);
	Identifier* id = parseIdentifier();
	functionDecl = new FunctionDecl(id);

	match('(');
	while (peek(')')) {
		Identifier* id = parseIdentifier();
		functionDecl->appendParam(id);
		tryMatch(',');
	}
	match(')');

	BlockStmt* body = parseBlockStmt(true);
	functionDecl->appendBody(body);

	return functionDecl;
}

Stmt* Parser::parseStmt() {
	Stmt* stmt = nullptr;

	if (peek('{'))
		stmt = parseBlockStmt();
	else if (peek(IF))
		stmt = parseIfStatement();
	else if (peek(WHILE))
		stmt = parseWhileStmt();
	else if (peek(DO)) {
		stmt = parseDoWhileStmt();
		match(';');
	}
	else if (peek(FOR))
		stmt = parseForStmt();
	else
		error("Error in parseStmt");


	return stmt;
}

BlockStmt* Parser::parseBlockStmt(bool canReturn) {

	BlockStmt* block = new BlockStmt();
	match('{');

	while (!peek('}')) {
		Node* node = nullptr;
		if (peek(VAR)) {
			node = parseVariableDeclaration();
			tryMatch(';');
		}
		else if (peek(FUNCTION))
			node = parseFunctionDeclaration();
		else if (peek({ IF, WHILE, DO, FOR, '{' }))
			node = parseStmt();
		else if (peek(RETURN)) {
			if (canReturn) {
				node = parseReturnStmt();
			}
			else {
				error("Illegal return statement");
			}
		}
		else {
			node = parseSequenceExpr();
			tryMatch(';');
		}

		if (node) block->append(node);
	};

	match('}');
	return block;
}

IfStmt* Parser::parseIfStatement() {
	IfStmt* ifstmt = nullptr;

	match(IF);
	match('(');

	Expr* test = parseLogicExpr();
	match(')');
	Node* consequent = nullptr;
	if (peek('{')) {
		consequent = parseBlockStmt();
	}
	else {
		consequent = parseExpr();
		match(';');
	}

	if (peek(ELSE)) {
		Node* alternate = nullptr;
		if (peek('{')) {
			alternate = parseBlockStmt();
		}
		else {
			alternate = parseExpr();
			match(';');
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

	match(')');
	Node* body = nullptr;
	if (peek('{')) {
		body = parseBlockStmt();
	}
	else {
		body = parseExpr();
		match(';');
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

	match(')');

	dowhilestmt = new DoWhileStmt(test, body);
	return dowhilestmt;
}

ForStmt* Parser::parseForStmt() {
	ForStmt* forstmt = nullptr;

	match(FOR);

	match('(');
	Node* init = nullptr;
	if (peek(VAR)) {
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

	if (peek('{')) {
		body = parseBlockStmt();
	}
	else {
		body = parseExpr();
		match(';');
	}

	forstmt = new ForStmt(body, init, test, update);

	return forstmt;
}

ReturnStmt* Parser::parseReturnStmt() {
	match(RETURN);
	Expr* expr = nullptr;
	if (!peek(';')) {
		expr = parseSequenceExpr();
	}

	ReturnStmt* returnStmt = new ReturnStmt(expr);

	return returnStmt;
}

Expr* Parser::parseExpr(bool shouldParseCall) {
	Expr* expr = nullptr;
	if (peek({ ID, '-', '+', '!', '(', NUMBER, TRUE, FALSE }))
		expr = parseLogicExpr();
	else if (peek('['))
		expr = parseArrayExpr();
	else if (peek({ ADD, MINUS }))
		expr = parseUpdateExpr();
	else if (peek(NEW))
		expr = parseNewExpr();
	else if (tryMatch('\"')) {
		expr = parseStringConstant();
		match('\"');
	}
	else if (tryMatch('\'')) {
		expr = parseStringConstant();
		match('\'');
	}

	if (shouldParseCall && peek('(')) {
		expr = parseCallExpr(expr);
	}

	return expr;
}

Expr* Parser::parseSequenceExpr() {
	Expr* expr = nullptr;

	expr = parseExpr();

	cerr << "first expr." << endl;
	if (!peek(',', false)) {
		cerr << "only one expr." << endl;
		return expr;
	}

	SequenceExpr* sequenceExpr = new SequenceExpr();
	sequenceExpr->append(expr);
	while (tryMatch(',', false)) {
		expr = parseExpr();
		sequenceExpr->append(expr);
	}

	return sequenceExpr;
}

Expr* Parser::parseArrayExpr() {
	ArrayExpr* arrayExpr = new ArrayExpr();
	match('[');

	while (!tryMatch(']')) {
		Expr* element = parseExpr();
		arrayExpr->append(element);
		tryMatch(',');
	}

	return arrayExpr;
}

Expr* Parser::parseNewExpr() {

	match(NEW);

	Expr* callee = parseExpr(false);

	NewExpr* newExpr = new NewExpr(callee);

	if (tryMatch('(')) {
		while (!tryMatch(')')) {
			Expr* argument = parseExpr();
			newExpr->append(argument);
			tryMatch(',');
		}
	}

	return newExpr;
}

Expr* Parser::parseCallExpr(Expr* callee) {
	CallExpr* callExpr = new CallExpr(callee);
	match('(');
	while (!tryMatch(')')) {
		Expr* argument = parseExpr();
		callExpr->append(argument);
		tryMatch(',');
	}

	return callExpr;
}

Expr* Parser::parseFunctionExpr() {
	FunctionExpr* functionExpr = nullptr;

	match(FUNCTION);
	Identifier* id = nullptr;
	if (peek(ID)) {
		id = parseIdentifier();
	}
	functionExpr = new FunctionExpr(id);

	match('(');
	while (!tryMatch(')')) {
		Identifier* id = parseIdentifier();
		functionExpr->appendParam(id);
		tryMatch(',');
	}

	BlockStmt* body = parseBlockStmt(true);
	functionExpr->appendBody(body);

	return functionExpr;
}

Expr* Parser::parseUpdateExpr(Expr* arg) {
	Token* op = move();

	Expr* argument = arg;

	bool prefix = argument == nullptr;

	if (prefix) {
		argument = parseIdentifier();
	}

	auto expr = new UpdateExpr(op, argument, prefix);

	return expr;
}

Expr* Parser::parseAssignmentExpr() {
	Expr* expr = nullptr;

	Identifier* id = parseIdentifier();

	if (auto eq = tryMatch('=')) {
		Expr* right = nullptr;

		if (peek(FUNCTION)) {
			right = parseFunctionExpr();
		}
		else {
			right = parseExpr();
		}

		expr = new AssignmentExpr(eq, id, right);
	}
	else if (peek({ ADD, MINUS })) {
		expr = parseUpdateExpr(id);
	}
	else {
		expr = id;
	}

	return expr;
}

Expr* Parser::parseLogicExpr() {
	Expr* left = join();
	while (auto op = tryMatch(OR)) {
		left = new LogicExpr(op, left, join());
	}

	return left;
}

Expr* Parser::join() {
	Expr* left = equality();
	while (auto op = tryMatch(AND)) {
		left = new LogicExpr(op, left, equality());
	}

	return left;
}

Expr* Parser::equality() {
	Expr* left = rel();
	while (auto op = tryMatch({ EQ, NE })) {
		left = new BinaryExpr(op, left, rel());
	}

	return left;
}

Expr* Parser::rel() {
	Expr* left = parseBinaryExpr();
	if (auto op = tryMatch({ '<', LE, GE, '>' })) {
		left = new BinaryExpr(op, left, parseBinaryExpr());
	}

	return left;
}

Expr* Parser::parseBinaryExpr() {
	Expr* left = getTerm();
	while (auto op = tryMatch({ '+', '-' })) {
		left = new BinaryExpr(op, left, getTerm());
	}

	return left;
}

Expr* Parser::getTerm() {
	Expr* right = parseUnaryExpr();
	while (auto op = tryMatch({ '*', '/' })) {
		right = new BinaryExpr(op, right, parseUnaryExpr());
	}

	return right;
}

Expr* Parser::parseUnaryExpr() {
	Expr* unaryExpr = nullptr;
	if (auto op = tryMatch({ '-', '!', '+' })) {
		Expr* argument = parseUnaryExpr();
		unaryExpr = new UnaryExpr(op, argument);
	}
	else if (tryMatch('(')) {
		unaryExpr = parseLogicExpr();
		match(')');
	}
	else if (peek(NUMBER)) {
		unaryExpr = parseNumberLiteral();
	}
	else if (peek(ID)) {
		unaryExpr = parseAssignmentExpr();
	}
	else if (tryMatch(TRUE)) {
		unaryExpr = new BoolLiteral("true");
	}
	else if (tryMatch(FALSE)) {
		unaryExpr = new BoolLiteral("false");
	}

	return unaryExpr;
}
