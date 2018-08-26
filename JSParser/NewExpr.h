#pragma once
#include<vector>
#include"Expr.h"
using namespace std;

class NewExpr :public Expr {
	Expr* callee;
	vector<Expr*> arguments;
public:
	NewExpr(Expr* c,NodeType t = NewExpr_t) :Node(t),callee(c) {
		setValue("New Expression");
	}

	void append(Expr* e) {
		arguments.push_back(e);
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[NewExpression]:" << endl;

		cout << setw(layer * 2 + 2) << " " << "callee:" << endl;;
		callee->display(layer + 2);

		cout << setw(layer * 2 + 2) << " " << "arguments[" << arguments.size() << "]:" << endl;
		for (int i = 0; i < arguments.size(); i++) {
			arguments[i]->display(layer + 2);
		}
	}
};