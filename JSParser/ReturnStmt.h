#pragma once
#include<iostream>
#include<iomanip>
#include"Stmt.h"
#include"Expr.h"
using namespace std;

class ReturnStmt :public Stmt {
	Expr* argument;
public:
	ReturnStmt(Expr* arg,NodeType t=ReturnStmt_t) :Node(t),argument(arg) {	}
	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[ReturnStatement]:" << endl;

		cout << setw(layer * 2 + 2) << " " << "argument:" << endl;
		argument->display(layer + 2);

	}
};