#pragma once
#include<string>
#include"Expr.h"

using namespace std;

class Identifier :public Expr {
protected:
	string name;
public:
	Identifier(string n,NodeType t=Identifier_t):Node(t),name(n){}

	string getName() {
		return name;
	}

	void display(int layer=1) {
		cout << setw(layer * 2 ) << " " << "[Identifier]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "name:" << name << endl;
		Expr::display(layer);
	}

	void execute(){}
};