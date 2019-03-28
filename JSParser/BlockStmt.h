#pragma once
#include<vector>
#include"Stmt.h"
#include"Node.h"

using namespace std;

class BlockStmt :public Stmt {
protected:
	vector<Node*> body;
public:
	BlockStmt(NodeType t=BlockStmt_t):Node(t) {
		setValue("Block Statement");
	}
	void append(Node* n) {
		body.push_back(n);
	}
	
	void display(int layer=1) {
		cout << setw(layer * 2 ) << " " << "[BlockStatment]:" << endl;

		Node::display(layer);

		cout << setw(layer * 2 + 2) << " " << "body[" << body.size() << "]:" << endl;
		for (int i = 0; i < body.size(); i++) {
			body[i]->display(layer+2);
		}
	}

	void execute() {
		Stmt::execute();

		for (vector<Node*>::iterator iter = body.begin(); iter != body.end(); iter++) {
			(*iter)->execute();
		}
	}

	string getName() {
		return "";
	}

	int totalExpr() {
		int total = 0;

		for (vector<Node*>::iterator iter = body.begin(); iter != body.end(); iter++) {
			total += (*iter)->totalExpr();
		}

		return total;
	}

	int totalExeExpr() {
			int total = 0;

			for (vector<Node*>::iterator iter = body.begin(); iter != body.end(); iter++) {
				total += (*iter)->totalExeExpr();
			}

			return total;
		}
};