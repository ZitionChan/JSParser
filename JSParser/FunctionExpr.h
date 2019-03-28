#pragma once
#include<vector>
#include"Identifier.h"
#include"Expr.h"
#include"BlockStmt.h"
using namespace std;


class FunctionExpr :public Expr {
	Identifier* id;
	vector<Identifier*> params;
	BlockStmt* body;
public:
	FunctionExpr(Identifier* i,NodeType t = FunctionExpr_t):Node(t),id(i){
		setValue("Function Expression");
	}

	void appendParam(Identifier* a) {
		params.push_back(a);
	}

	void appendBody(BlockStmt* b) {
		body = b;
	}

	void display(int layer = 1) {
		cout << setw(layer * 2) << " " << "[FunctionExpression]:" << endl;

		Node::display(layer);

		cout << setw(layer * 2 + 2) << " " << "id:" << endl;
		if (id) {
			id->display(layer + 2);
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}

		cout << setw(layer * 2 + 2) << " " << "params[" << params.size() << "]:" << endl;
		if (params.size()) {
			for (int i = 0; i < params.size(); i++) {
				params[i]->display(layer + 2);
			}
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}

		cout << setw(layer * 2 + 2) << " " << "body:" << endl;
		if (body) {
			body->display(layer + 2);
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}
	}

	void execute() {
		Expr::execute();
		body->execute();
	}
};