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
	Lexer* lex; //词法分析器
	Token* look; //预读token
	Program* top;
	unordered_map<string, Identifier*>* globalLE; //全局Lexical environment

	void move();//读入下一位token
	void error(string s); //抛出异常
	void match(int t);//检查token的tag值是否匹配

	//void preProcess();//变量和函数声明预处理

	void parseIdentifier();
public:
	Parser(Lexer* l);
	void program(); //根节点
};