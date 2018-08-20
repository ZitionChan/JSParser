#pragma once
#include<unordered_map>	
#include"Token.h"
#include"Lexer.h"
#include"AllNodes.h"
#include<typeinfo>

using namespace std;

class Parser {
	class LookaheadLexer {
	private:
		Lexer &lex;
		Token *look = nullptr;

	public:
		LookaheadLexer(Lexer &lex) : lex(lex) {}
		Token *peek();
		Token *move();
		void error(string s); //抛出异常
	};

	LookaheadLexer lex;
	Token *peek() { return lex.peek(); }
	Token *peek(std::initializer_list<int>, bool ignoreNewLine = true);
	Token *peek(int t, bool ignoreNewLine = true) { return peek({ t }, ignoreNewLine); }
	Token *match(int t);
	Token *tryMatch(std::initializer_list<int> ts, bool ignoreNewLine = true);
	Token *tryMatch(int t, bool ignoreNewLine = true) { return tryMatch({ t }, ignoreNewLine); }
	Token *move() { return lex.move(); }

	Program *top;
	unordered_map<string, Identifier *> globalLE; //全局Lexical environment

	Node *program(); //解析一个语法单元

	void error(string s) { lex.error(s); }

	StringConstant* parseStringConstant();
	NumberLiteral* parseNumberLiteral(); //解析数字
	Identifier* parseIdentifier();//解析变量名
	VariableDeclaration* parseVariableDeclaration();
	VariableDeclarator *parseVariableDeclarator(); //解析变量声明
	FunctionDecl *parseFunctionDeclaration();      //解析函数声明


	//解析Statement
	Stmt* parseStmt();
	IfStmt* parseIfStatement();//解析if语句
	WhileStmt* parseWhileStmt();
	DoWhileStmt* parseDoWhileStmt();
	BlockStmt* parseBlockStmt(bool canReturn = false);
	ForStmt* parseForStmt();
	ReturnStmt* parseReturnStmt();

	//解析Expression
	Expr* parseExpr(bool shouldParseCall = true);
	Expr* parseArrayExpr();
	Expr* parseNewExpr();
	Expr* parseCallExpr(Expr* callee);
	Expr* parseUpdateExpr(Expr* arg = nullptr);
	Expr* parseSequenceExpr();
	Expr* parseFunctionExpr();
	Expr* parseLogicExpr(); //解析逻辑表达式，递归最顶层，LogicExpr 解析OR
	Expr* join(); //解析LogicExpr 逻辑&&
	Expr* equality(); //解析BinaryExpr ==和!=
	Expr* rel(); //解析BinaryExpr <,>,<=,>=
	Expr* parseBinaryExpr(); //解析BinaryExpr +和-
	Expr* getTerm(); //解析BinaryExpr *和/
	Expr* parseUnaryExpr(); //解析UnaryExpr，包括id,Number,bool

	Expr* parseAssignmentExpr(); //返回AssignmentExpr*或者Identifier*

public:
	Parser(Lexer& l);

	void run(); //开始解析
	void display();
	void singleLine(bool showTree = false);//单行模式
};