#pragma once

#include"Decl.h"
#include"Expr.h"

class VariableDecl:public Decl {
protected:
	Expr* init;
public:

	VariableDecl(Identifier* id,Expr* in) :Decl(id),init(in) {
		
	}

};