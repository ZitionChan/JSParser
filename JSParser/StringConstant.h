#pragma once
#include<string>
#include"Expr.h"
using namespace std;

class StringConstant:public Expr {
protected:
	string value;
public:
	StringConstant(string v) :value(v) {

	}

	void display() {
		cout << "StringConstant:" << endl;
		cout << "value:" << endl;
		cout << value << endl;
	}
};