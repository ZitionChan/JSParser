#pragma once
#include"Literal.h"

class NumberLiteral :public Literal<double> {
public:
	NumberLiteral(double v,NodeType t=NumberLiteral_t) :Node(t),Literal(v) {
		
	}

	string getName() {
		return to_string(raw);
	}
};