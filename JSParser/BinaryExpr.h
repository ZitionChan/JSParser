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

	Value getValue();

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[BinaryExpression]:" << endl;

		Node::display(layer);

		cout << setw(layer * 2 + 2) << " " << "op:" << op->toString() << endl;
		cout << setw(layer * 2 + 2) << " " << "left:" << endl;
		left->display(layer + 2);
		cout << setw(layer * 2 + 2) << " " << "right:"<<endl;
		right->display(layer + 2);
		Expr::display(layer);
	}

	string getName() {
		string name = "";
		name = (left->type == BinaryExpr_t)? left->getValue().toString(): left->getName();
		name += op->toString();
		name += (right->type == BinaryExpr_t) ? right->getValue().toString() : right->getName();

	return name;
	}

	void execute(){
		left->execute();
		right->execute();
		Expr::execute();
	}
};