#pragma once
#include<vector>
#include"Expr.h"

using namespace std;

class SequenceExpr :public Expr {
	vector<Expr*> expressions;
public:
	SequenceExpr(NodeType t=SequenceExpr_t):Node(t){
		setValue("Sequence Expression");
	}

	void append(Expr* e) {
		expressions.push_back(e);
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[SequenceExpression]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "expressions[" << expressions.size() << "]:" << endl;
		for (int i = 0; i < expressions.size(); i++) {
			expressions[i]->display(layer + 2);
		}
	}
};