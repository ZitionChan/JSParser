#pragma once

#include<fstream>
#include<unordered_map>
#include"Token.h"
#include"Word.h"
#include"utils.h"

using namespace std;

class Lexer {
	char peek;//������ַ�
	bool isStringConstant;
	unordered_map<string, Token*> words;
	istream* reader;
	void reserve(Word* w);//��ӱ�����
	void readch(); //��ȡһ���ַ�
	bool readch(char c); //Ԥ����һ���ַ�
	void initReserve(); //��ʼ��������
	void ignoreSpace();
	string readStringConstant();
public:
	static int line; //��ǰ����
	Lexer(istream* is);
	bool eof(); //�ж��Ƿ����
	Token* scan(); //��ȡһ��token
	char getPeek() {
		return peek;
	}
	void run();
};