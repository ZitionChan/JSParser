//Token��
#pragma once

#include<string>
#include"utils.h"

using namespace std;

class Token {
public:
	int tag;//��ǩ
	
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

};




