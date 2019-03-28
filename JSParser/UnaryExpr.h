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
		//Value tempValue = getValue();
		/*Value tempValue = arg->getValue();
		switch (opp->tag)
		{
		case '!':
			tempValue = !tempValue;
			break;
		case ADD:
			++tempValue; 
			arg->setValue(tempValue); 
			break;
		case MINUS:
			--tempValue;
			arg->setValue(tempValue);
			break;
		default:
			break;
		}*/
		//this->setValue(tempValue);
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[UnaryExpression]:" << endl;

		Node::display(layer);


		cout << setw(layer * 2 + 2) << " " << "op:" << op->toString() << endl;
		cout << setw(layer * 2 + 2) << " " << "argument:"<< endl;
		argument->display(layer + 2);
		cout << setw(layer * 2 + 2) << " " << "prefix:";
		if (prefix) cout << "true" << endl;
		else cout << "false" << endl;
	}

	Value getValue() {
		Value tempValue = argument->getValue();
		switch (op->tag)
		{
		case '!':
			tempValue = !tempValue;
			break;
		case ADD:
			++tempValue;
			argument->setValue(tempValue);
			break;
		case MINUS:
			--tempValue;
			argument->setValue(tempValue);
			break;
		default:
			break;
		}
		return tempValue;
	}

	string getName() {
		string name = "";

		if (prefix) {
			name = op->toString() + argument->getName();
		}
		else {
			name = argument->getName() + op->toString();
		}

		return name;
	}

	void execute() {
		Expr::execute();
		Value tempValue = getValue();
		this->setValue(tempValue);
	}
};