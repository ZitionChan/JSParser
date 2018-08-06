#pragma once
#include<vector>
#include"Stmt.h"
#include"Node.h"

using namespace std;

class BlockStmt :public Stmt {
protected:
	vector<Node*> body;
public:
	BlockStmt() {}
};