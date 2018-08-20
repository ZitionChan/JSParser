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
		void error(string s); //�׳��쳣
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
	unordered_map<string, Identifier *> globalLE; //ȫ��Lexical environment

	Node *program(); //����һ���﷨��Ԫ

	void error(string s) { lex.error(s); }

	StringConstant* parseStringConstant();
	NumberLiteral* parseNumberLiteral(); //��������
	Identifier* parseIdentifier();//����������
	VariableDeclaration* parseVariableDeclaration();
	VariableDeclarator *parseVariableDeclarator(); //������������
	FunctionDecl *parseFunctionDeclaration();      //������������


	//����Statement
	Stmt* parseStmt();
	IfStmt* parseIfStatement();//����if���
	WhileStmt* parseWhileStmt();
	DoWhileStmt* parseDoWhileStmt();
	BlockStmt* parseBlockStmt(bool canReturn = false);
	ForStmt* parseForStmt();
	ReturnStmt* parseReturnStmt();

	//����Expression
	Expr* parseExpr(bool shouldParseCall = true);
	Expr* parseArrayExpr();
	Expr* parseNewExpr();
	Expr* parseCallExpr(Expr* callee);
	Expr* parseUpdateExpr(Expr* arg = nullptr);
	Expr* parseSequenceExpr();
	Expr* parseFunctionExpr();
	Expr* parseLogicExpr(); //�����߼����ʽ���ݹ���㣬LogicExpr ����OR
	Expr* join(); //����LogicExpr �߼�&&
	Expr* equality(); //����BinaryExpr ==��!=
	Expr* rel(); //����BinaryExpr <,>,<=,>=
	Expr* parseBinaryExpr(); //����BinaryExpr +��-
	Expr* getTerm(); //����BinaryExpr *��/
	Expr* parseUnaryExpr(); //����UnaryExpr������id,Number,bool

	Expr* parseAssignmentExpr(); //����AssignmentExpr*����Identifier*

public:
	Parser(Lexer& l);

	void run(); //��ʼ����
	void display();
	void singleLine(bool showTree = false);//����ģʽ
};