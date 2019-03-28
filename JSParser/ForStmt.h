#pragma once
#include<iostream>
#include<iomanip>
#include"Stmt.h"
#include"Expr.h"

using namespace std;

class ForStmt :public Stmt {
	Expr* test;
	Expr* update;
	Node* init;
	Node* body;
public:
	ForStmt(Node* b,Node* i,Expr* t, Expr* u,NodeType type=ForStmt_t):Node(type),test(t),update(u),init(i),body(b){
		setValue("For Statement");
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[For Statement]:" << endl;

		Node::display(layer);


		cout << setw(layer * 2 + 2) << " " << "init:" << endl;
		if (init) {
			init->display(layer + 2);
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}

		cout << setw(layer * 2 + 2) << " " << "test:" << endl;
		if (test) {
			test->display(layer + 2);
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}

		cout << setw(layer * 2 + 2) << " " << "update:" << endl;
		if (update) {
			update->display(layer + 2);
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}

		cout << setw(layer * 2 + 2) << " " << "body:" << endl;
		body->display(layer + 2);
	}

	void execute() {
		Stmt::execute();

		if(init) init->execute();

		test->execute();
		
		while(test->getValue() == true) {
			body->execute();
			if(update) update->execute();
		}
	}

	string getName() {
		return "for statement";
	}

	int totalExpr() {
		int total = 0;
		total += init ? init->totalExpr(): 0;
		total += test->totalExpr();
		total += body->totalExpr();
		total += update ? update->totalExpr() : 0;
		return total;
	}

	int totalExeExpr() {
		int total = 0;
		total += init ? init->totalExeExpr() : 0;
		total += test->totalExeExpr();
		total += body->totalExeExpr();
		total += update ? update->totalExeExpr() : 0;
		return total;
	}
};