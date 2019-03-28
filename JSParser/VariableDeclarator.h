#pragma once

#include"Decl.h"
#include"Expr.h"

class VariableDeclarator:public Decl {
protected:
	Expr* init;
public:

	VariableDeclarator(Identifier* id,Expr* in,NodeType t=VariableDeclarator_t) :Node(t),Decl(id),init(in) {
		/*if (in) {
			type = in->type;
			id->setValue(in->getValue());
			setValue(id->getValue());
		}*/
	}

	void display(int layer=1) {
		cout << setw(layer * 2) << " " << "[VariableDeclarator]:" << endl;

		Node::display(layer);

		cout << setw(layer * 2+2) << " " << "id:"<<endl;
		id->display(layer+2);
		cout << setw(layer * 2+2) << " " << "init:" << endl;
		if (init) {
			init->display(layer+2);
		}
		else {
			cout << setw(layer * 2 + 2) << " " << "null" << endl;
		}
	}

	string getName() {
		return "var " + id->getName() + " = " + init->getName();

	}

	void execute() {
		Decl::execute();
		if (init) {
			type = init->type;
			id->setValue(init->getValue());
			setValue(id->getValue());
		}
	}
};