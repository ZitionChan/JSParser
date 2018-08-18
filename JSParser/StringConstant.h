#pragma once
#include<string>
#include"Literal.h"
using namespace std;

class StringConstant:public Literal<string> {

public:
	StringConstant(string v,NodeType t=StringConstant_t) :Node(t),Literal(v) {

	}

};