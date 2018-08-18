#pragma once

#include"BinaryExpr.h"

class AssignmentExpr :public BinaryExpr {
public:
	AssignmentExpr(Token* op, Expr* left, Expr* right,NodeType t=AssignmentExpr_t) :Node(t),BinaryExpr(op, left, right) {
		type = right->type;
		left->setValue(right->getValue());
		setValue(left->getValue());
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[AssignmentExpression]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "op:" << op->toString() << endl;
		cout << setw(layer * 2 + 2) << " " << "left:" << endl;
		left->display(layer + 2);
		cout << setw(layer * 2 + 2) << " " << "right:" << endl;
		right->display(layer + 2);
	}
};