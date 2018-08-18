#pragma once

#include<string>
#include"Token.h"

using namespace std;

class Word:public Token {
	string lexeme;
public:
	Word(string s,int tag):Token(tag),lexeme(s){}

	string toString() {
		return lexeme;
	}

	static Word *And,*Or , *Eq, *Ne, *Le, *Ge,*Add,*Minus;
};

