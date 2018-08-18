#pragma once
#include<vector>
#include"Expr.h"
using namespace std;

class ArrayExpr :public Expr {
	vector<Expr*> elements;
public:
	ArrayExpr(NodeType t=ArrayExpr_t):Node(t){}

	void append(Expr* e) {
		elements.push_back(e);
	}

	void display(int layer = 1) {

		cout << setw(layer * 2) << " " << "[ArrayExpression]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "elements[" << elements.size() << "]:" << endl;
		for (int i = 0; i < elements.size(); i++) {
			elements[i]->display(layer + 2);
		}
	}

};