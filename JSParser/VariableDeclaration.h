#pragma once
#include<vector>
#include"Stmt.h"
#include"VariableDeclarator.h"
using namespace std;

class VariableDeclaration :public Stmt {
	vector<VariableDeclarator*> declarations;
public:
	VariableDeclaration(NodeType t=VariableDeclaration_t):Node(t){
		setValue("Variable Declaration");
	}

	void append(VariableDeclarator* vd) {
		declarations.push_back(vd);
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[VariableDeclaration]:" << endl;

		Node::display(layer);

		cout << setw(layer * 2 + 2) << " " << "declarations[" << declarations.size() << "]:" << endl;
		for (int i = 0; i < declarations.size(); i++) {
			declarations[i]->display(layer + 2);
		}
	}

	string getName() {
		return "";
	}

	void execute() {
		Stmt::execute();

		for (vector<VariableDeclarator*>::iterator iter = declarations.begin(); iter != declarations.end(); iter++) {
			(*iter)->execute();
		}
	}
};