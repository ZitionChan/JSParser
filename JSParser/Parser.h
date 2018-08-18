#pragma once
#include<unordered_map>	
#include"Token.h"
#include"Lexer.h"
#include"AllNodes.h"
#include<typeinfo>

using namespace std;

class Parser {
	Lexer* lex; //�ʷ�������
	Token* look; //Ԥ��token
	Program* top;
	unordered_map<string, Identifier*> globalLE; //ȫ��Lexical environment

	void move();//������һλtoken
	void error(string s); //�׳��쳣
	void match(int t);//���token��tagֵ�Ƿ�ƥ��
	Node* program(); //����һ���﷨��Ԫ


	StringConstant* parseStringConstant();
	NumberLiteral* parseNumberLiteral(); //��������
	Identifier* parseIdentifier();//����������
	VariableDeclaration* parseVariableDeclaration();
	VariableDeclarator* parseVariableDeclarator(); //������������
	FunctionDecl* parseFunctionDeclaration(); //������������


	//����Statement
	Stmt* parseStmt(); 
	IfStmt* parseIfStatement();//����if���
	WhileStmt* parseWhileStmt();
	DoWhileStmt* parseDoWhileStmt();
	BlockStmt* parseBlockStmt(bool canReturn=false);
	ForStmt* parseForStmt();
	ReturnStmt* parseReturnStmt();

	//����Expression 
	Expr* parseExpr(bool shouldParseCall=true);
	Expr* parseArrayExpr();
	Expr* parseNewExpr();
	Expr* parseCallExpr(Expr* callee);
	Expr* parseUpdateExpr(Expr* arg=nullptr);
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
	Parser(Lexer* l);

	void run(); //��ʼ����
	void display();
	void singleLine(bool showTree =false);//����ģʽ
};