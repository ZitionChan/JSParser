#pragma once

#include"Expr.h"

template<class T>
class Literal :public Expr {
protected:
	T raw;
public:
	Literal(T v,NodeType t=Literal_t):Expr(v),Node(t),raw(v){
	}

	T getRaw() {
		return raw;
	}

	void display(int layer=1) {
		cout <<setw(layer*2)<<" "<< "[Literal]:" << endl;
		cout << setw(layer * 2+2) << " "<< "raw:" << raw << endl;
		cout << setw(layer * 2 + 2) <<" "<<"value:"<< value << endl;
	}
};