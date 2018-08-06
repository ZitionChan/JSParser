#pragma once
#include"Expr.h"
#include"Token.h"


class UnaryExpr :public Expr {
protected:
	Token * op;
	Expr* argument;
	bool prefix;
public:
	UnaryExpr(Token* opp,Expr* arg,bool pref = true):op(opp),argument(arg),prefix(pref){}
};