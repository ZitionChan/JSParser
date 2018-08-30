#pragma once

#include<fstream>
#include<unordered_map>
#include"Token.h"
#include"Word.h"
#include"utils.h"

using namespace std;

class Lexer {
	char peek;//读入的字符
	bool isStringConstant;
	unordered_map<string, Token*> words;
	istream* reader;
	void reserve(Word* w);//添加保留字
	void readch(); //读取一个字符
	bool readch(char c); //预读下一个字符
	void initReserve(); //初始化保留字
	void ignoreSpace();
	string readStringConstant();
public:
	static int line; //当前行数
	Lexer(istream* is);
	bool eof(); //判断是否结束
	Token* scan(); //读取一个token
	char getPeek() {
		return peek;
	}
	void run();
};