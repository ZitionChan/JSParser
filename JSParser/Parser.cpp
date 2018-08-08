#include"Parser.h"
#include"Tag.h"
#include"utils.h"

Parser::Parser(Lexer* l) :lex(l),top(nullptr),globalLE() {
	move();
}

void Parser::move() {
	look = lex->scan();
}

void Parser::error(string s) {
	throw "Error: near line " + toStr(lex->line) + ": " + s;
}

void Parser::match(int t) {
	if (t == look->tag) move();
	else error("can't match:"+toStr((char)t));
}

void Parser::run() {
	if (top) delete top;

	top = new Program();

	while (!lex->eof()) {
		program();
	}
}

void Parser::program() {

	if (look->tag == VAR) {
		move();
		parseDeclaration();
	}

}

void Parser::display() {
	top->display();
}

void Parser::parseDeclaration() {

	VariableDecl*  variableDeclaration=nullptr;//新结点
	Identifier* id=nullptr;//声明的变量

	if (look->tag == ID) {
		string name = look->toString();

		id = new Identifier(name);

		globalLE.insert(pair<string, Identifier*>(name, id));

		move();

		if (look->tag == ';') {
			match(';');
			variableDeclaration = new VariableDecl(id, nullptr);
		}
		else if (look->tag == '=') {
			match('=');
			switch (look->tag)
			{
			case ID: 
			{
				Identifier* tempId = new Identifier(look->toString());
				variableDeclaration = new VariableDecl(id, tempId); 
			}
			move();
			match(';');
				break;
			case NUMBER:
			{
				Literal* ltrl = new Literal(look->getValue());
				variableDeclaration = new VariableDecl(id, ltrl);
			}
			move();
			match(';');
				break;
			case '\"':
			{
				move();
				string stringConstant = look->toString();
				StringConstant* str = new StringConstant(stringConstant);
				variableDeclaration = new VariableDecl(id, str);
				move();
				match('\"');
				match(';');
			}
			break;
			default:
				error("Unexpected token " + look->toString());
				break;
			}

			
		}
		else {
			error("Unexpected token " + look->toString());
		}

		top->append(variableDeclaration);
	}
	else {
		error("Unexpected token " + look->toString());
	}
}