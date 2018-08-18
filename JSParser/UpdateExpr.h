#pragma once
#include"UnaryExpr.h"
#include"Token.h"

class UpdateExpr :public UnaryExpr {

public:
	UpdateExpr(Token* op, Expr* argument, bool prefix,NodeType t=UpdateExpr_t) :Node(t),UnaryExpr(op, argument, prefix) {

	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[UpdateExpression]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "op:" << op->toString() << endl;
		cout << setw(layer * 2 + 2) << " " << "argument:" << endl;
		argument->display(layer + 2);
		cout << setw(layer * 2 + 2) << " " << "prefix:";
		if (prefix) cout << "true" << endl;
		else cout << "false" << endl;
	}
};