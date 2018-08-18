#pragma once
#include"Expr.h"
#include"Token.h"


class UnaryExpr :public Expr {
protected:
	Token * op;
	Expr* argument;
	bool prefix;
public:
	UnaryExpr(Token* opp,Expr* arg,bool pref = true,NodeType t=UnaryExpr_t):Node(t),op(opp),argument(arg),prefix(pref){
		type = arg->type;
		Value tempValue = arg->getValue();
		switch (opp->tag)
		{
		case '!':
			tempValue = !tempValue;
			break;
		default:
			break;
		}
		this->setValue(tempValue);
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[UnaryExpression]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "op:" << op->toString() << endl;
		cout << setw(layer * 2 + 2) << " " << "argument:"<< endl;
		argument->display(layer + 2);
		cout << setw(layer * 2 + 2) << " " << "prefix:";
		if (prefix) cout << "true" << endl;
		else cout << "false" << endl;
	}
};