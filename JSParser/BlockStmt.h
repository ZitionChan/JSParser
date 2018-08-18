#pragma once
#include<vector>
#include"Stmt.h"
#include"Node.h"

using namespace std;

class BlockStmt :public Stmt {
protected:
	vector<Node*> body;
public:
	BlockStmt(NodeType t=BlockStmt_t):Node(t) {}
	void append(Node* n) {
		body.push_back(n);
	}
	
	void display(int layer=1) {
		cout << setw(layer * 2 ) << " " << "[BlockStatment]:" << endl;
		cout << setw(layer * 2 + 2) << " " << "body[" << body.size() << "]:" << endl;
		for (int i = 0; i < body.size(); i++) {
			body[i]->display(layer+2);
		}
	}
};