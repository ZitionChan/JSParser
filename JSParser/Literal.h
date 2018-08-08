#pragma once

#include"Expr.h"

class Literal :public Expr {
protected:
	double value;
public:
	Literal(double v):value(v){}

	double getValue() {
		return value;
	}

	void display() {
		cout << "Literal:" << endl;
		cout << "value:" << value << endl;
	}
};