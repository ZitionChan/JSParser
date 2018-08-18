#pragma once
#include"BinaryExpr.h"

class LogicExpr :public BinaryExpr {
public:
	LogicExpr(Token* op, Expr* left, Expr* right, NodeType t = LogicExpr_t);

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[LogicExpression]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "op:" << op->toString() << endl;
		cout << setw(layer * 2 + 2) << " " << "left:" << endl;
		left->display(layer + 2);
		cout << setw(layer * 2 + 2) << " " << "right:" << endl;
		right->display(layer + 2);
		Expr::display(layer);
	}
};