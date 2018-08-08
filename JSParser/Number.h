//Number����
#pragma once

#include<string>
#include"Token.h"
#include"Tag.h"
#include"utils.h"

using namespace std;

class Number:public Token {
	double value;//ʵ��ֵ
public:
	Number(double v):Token(NUMBER),value(v) {
	}

	double getValue() {
		return value;
	}

	string toString() {
		return toStr(value);
	}

};
