#pragma once
#include<vector>
#include"Expr.h"
using namespace std;

class CallExpr :public Expr {
	Expr* callee;
	vector<Expr*> arguments;
public:
	CallExpr(Expr* c,NodeType t=CallExpr_t):Node(t),callee(c){
		setValue("Call Expression");
	}
	
	void append(Expr* e) {
		arguments.push_back(e);
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[CallExpression]:" << endl;

		Node::display(layer);
		
		cout << setw(layer * 2 + 2) << " " << "callee:" << endl;;
		callee->display(layer + 2);

		cout << setw(layer * 2 + 2) << " " << "arguments[" << arguments.size() << "]:" << endl;
		for (int i = 0; i < arguments.size(); i++) {
			arguments[i]->display(layer + 2);
		}
	}
};