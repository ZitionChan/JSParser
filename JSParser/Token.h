//Token¿‡
#pragma once

#include<string>
#include"utils.h"

using namespace std;

class Token {
public:
	int tag;//±Í«©
	
	Token(int t) {
		tag = t;
	}

	Token(char c) {
		tag = (int)c;
	}

	virtual string toString() {
		char c = (char)tag;
		return toStr(c);
	}

	virtual double getValue() {
		throw "Class Token don't have getValue()";
	}

};




