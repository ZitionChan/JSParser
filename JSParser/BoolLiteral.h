#pragma once
#include<string>
#include"Literal.h"

using namespace std;

class BoolLiteral :public Literal<string> {
public:
	BoolLiteral(string v,NodeType t=BoolLiteral_t) :Node(t),Literal(v) {
		if (v == "true")setValue(true);
		else if(v == "false") setValue(false);
	}
};