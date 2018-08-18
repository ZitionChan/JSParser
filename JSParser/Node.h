#pragma once
#include<iostream>
#include<iomanip>
#include"NodeType.h"
#include"Value.h"

class Node {
protected:
	Value value;
public:
	NodeType type;
	Node(NodeType t=Node_t):type(t) {};
	
	virtual void setValue(Value v) {
		value = v;
	}

	virtual Value getValue() {
		return value;
	}

	virtual void display(int layer=1){
		cout << "one node" << endl;
		cout << "type:" << type << endl;
	}
};