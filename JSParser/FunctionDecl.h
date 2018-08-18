#pragma once
#include<vector>
#include "Decl.h"
#include"Identifier.h"
#include"BlockStmt.h"

class FunctionDecl :public Decl {
protected:
	vector<Identifier*> params;
	BlockStmt* body;
public:
	FunctionDecl(Identifier* id,NodeType t=FunctionDecl_t):Node(t),Decl(id){}
	
	void appendParam(Identifier* a) {
		params.push_back(a);
	}

	void appendBody(BlockStmt* b) {
		body = b;
	}

	void display(int layer=1) {
		cout << setw(layer * 2) << " " << "[FunctionDeclaration]:" << endl;
		
		cout << setw(layer * 2 + 2) << " " << "id:" << endl;
		id->display(layer+2);
		
		cout << setw(layer * 2 + 2) << " " << "params[" <<params.size()<<"]:"<< endl;
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
			body->display(layer+2);
		}
		else {
			cout << setw(layer * 2 + 4) << " " << "null" << endl;
		}
	}
};
