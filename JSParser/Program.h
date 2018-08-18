#pragma once
#include<vector>
#include"Node.h"

using namespace std;

class Program :public Expr {
	vector<Node*> body;
public:
	Program(NodeType t=Program_t):Node(t),body(){
		setValue(typeToStr(t));
	}

	void append(Node* n) {
		body.push_back(n);
	}


	void display(int layer=0) {
		cout << setw(layer * 2 ) << " " << "[Program]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "body[" << body.size() << "]:" << endl;
		for (int i = 0; i < body.size(); i++) {
			body[i]->display(layer+2);
		}
	}
};