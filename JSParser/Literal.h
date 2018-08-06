#pragma once

#include"Expr.h"

class Literal :public Expr {
protected:
	double value;
public:
	Literal(double v):value(v){}

	double value() {
		return value;
	}
};