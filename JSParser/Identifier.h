#pragma once
#include<string>
#include"Expr.h"

using namespace std;

class Identifier :public Expr {
protected:
	string name;
public:
	Identifier(string n):name(n){}

	string getName() {
		return name;
	}

	void display() {
		cout << "identifier:" << endl;
		cout << "	name:" << name << endl;
	}
};