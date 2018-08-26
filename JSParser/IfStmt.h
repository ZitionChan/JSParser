#pragma once
#include<iomanip>
#include<iostream>
#include"Stmt.h"
#include"Expr.h"
#include"Node.h"
using namespace std;


class IfStmt :public Stmt {
protected:
	Expr* test;
	Node* consequent;
	Node* alternate;
public:
	IfStmt(Expr* t, Node* c, Node* a=nullptr,NodeType type=IfStmt_t) :Node(type),test(t), consequent(c), alternate(a) {
		setValue("If Statement");
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[IfStatement]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "test:" << endl;
		test->display(layer + 2);

		cout << setw(layer * 2 + 2) << " " << "consequent:" << endl;
		consequent->display(layer + 2);

		cout << setw(layer * 2 + 2) << " " << "alternate:" << endl;
		if (alternate) {
			alternate->display(layer + 2);
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}
	}

};