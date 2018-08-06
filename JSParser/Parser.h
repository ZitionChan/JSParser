#pragma once
#include<unordered_map>	
#include"Token.h"
#include"Lexer.h"
#include"Node.h"
#include"Identifier.h"
#include"Program.h"
#include"VariableDecl.h"

using namespace std;

class Parser {
	Lexer* lex; //�ʷ�������
	Token* look; //Ԥ��token
	Program* top;
	unordered_map<string, Identifier*>* globalLE; //ȫ��Lexical environment

	void move();//������һλtoken
	void error(string s); //�׳��쳣
	void match(int t);//���token��tagֵ�Ƿ�ƥ��

	//void preProcess();//�����ͺ�������Ԥ����

	void parseIdentifier();
public:
	Parser(Lexer* l);
	void program(); //���ڵ�
};