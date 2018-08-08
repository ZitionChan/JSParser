#pragma once
#include<unordered_map>	
#include"Token.h"
#include"Lexer.h"
#include"AllNodes.h"


using namespace std;

class Parser {
	Lexer* lex; //�ʷ�������
	Token* look; //Ԥ��token
	Program* top;
	unordered_map<string, Identifier*> globalLE; //ȫ��Lexical environment

	void move();//������һλtoken
	void error(string s); //�׳��쳣
	void match(int t);//���token��tagֵ�Ƿ�ƥ��
	void program(); //����һ���﷨��Ԫ

	//void preProcess();//�����ͺ�������Ԥ����

	void parseDeclaration();
public:
	Parser(Lexer* l);

	void run(); //��ʼ����
	void display();
};