#pragma once
#include"Expr.h"
#include"Token.h"

class BinaryExpr : public Expr {
protected:
	Token * op;
	Expr* left;
	Expr* right;
public:

	BinaryExpr(Token* opp ,Expr* l,Expr* r):op(opp),left(l),right(r){}

};