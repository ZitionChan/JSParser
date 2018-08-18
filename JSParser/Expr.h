#pragma once
#include"Value.h"
#include"Node.h"
#include"NodeType.h"
class Expr :virtual public Node {

public:
	Expr(Value v="undefined",NodeType t=Expr_t):Node(t){
		setValue(v);
	}

	void display(int layer=1) {
		cout << setw(layer * 2 +2) << " " << "value:" << value << endl;
	}
};
