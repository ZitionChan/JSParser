#pragma once

#include"Decl.h"
#include"Expr.h"

class VariableDecl:public Decl {
protected:
	Expr* init;
public:

	VariableDecl(Identifier* id,Expr* in) :Decl(id),init(in) {
		
	}

	void display() {
		cout << "VariableDeclarator:" << endl;
		cout << "	id:"<<endl; 
		id->display();
		cout << "	init:" << endl;
		if (init) {
			init->display();
		}
		else {
			cout << "		null" << endl;
		}
	}

};