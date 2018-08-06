#include"Parser.h"
#include"Tag.h"
#include"utils.h"

Parser::Parser(Lexer* l) :lex(l),top(nullptr) {
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
	else error("syntax error");
}

void Parser::program() {
	top = new Program(); 
	
	if (look->tag == VAR) {
		move();
		Identifier* id = nullptr;
		if (look->tag == ID) {
			string name = look->toString();
			id = new Identifier(name);
			
			globalLE->insert(pair<string, Identifier*>(name, id));
			
			VariableDecl*  variableDeclaration = new VariableDecl(id, nullptr);
			
			move();
			if (look->tag == ';') {
				match(';');
				top->append(variableDeclaration);
			}
			else if (look->tag == '=') {
				match('=');
				//parseExpr;
			}
		}
		else {
			error("need an identifier");
		}
	
	}

	top->display();
}

void Parser::parseIdentifier() {
	move();
	Identifier* id = nullptr;
	if (look->tag == ID) {
		string name = look->toString();
		id = new Identifier(name);
		globalLE->insert(pair<string, Identifier*>(name, id));
		VariableDecl*  variableDeclartion = new VariableDecl(id, nullptr);

	}
	else {
		error("need an identifier");

	}
}