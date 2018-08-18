#pragma once

#include<iomanip>
#include"Stmt.h"
#include"Node.h"
#include"Expr.h"

using namespace std;

class DoWhileStmt :public Stmt {
	Expr* test;
	Node* body;
public:
	DoWhileStmt(Expr* t, Node* b,NodeType type=DoWhileStmt_t) :Node(type),test(t), body(b) {

	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[DoWhileStatement]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "test:" << endl;
		test->display(layer + 2);

		cout << setw(layer * 2 + 2) << " " << "body:" << endl;
		body->display(layer + 2);

	}
};
