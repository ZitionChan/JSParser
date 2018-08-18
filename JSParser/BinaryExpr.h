#pragma once
#include"Expr.h"
#include"Token.h"

class BinaryExpr : public Expr {
protected:
	Token * op;
	Expr* left;
	Expr* right;
public:

	BinaryExpr(Token* opp, Expr* l, Expr* r, NodeType t = BinaryExpr_t);

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[BinaryExpression]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "op:" << op->toString() << endl;
		cout << setw(layer * 2 + 2) << " " << "left:" << endl;
		left->display(layer + 2);
		cout << setw(layer * 2 + 2) << " " << "right:"<<endl;
		right->display(layer + 2);
		Expr::display(layer);
	}
};