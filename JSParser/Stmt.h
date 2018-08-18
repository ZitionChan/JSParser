#pragma once
#include"Node.h"


class Stmt :virtual public Node {
public:
	Stmt(NodeType t=Stmt_t):Node(t){
		setValue("[Statement]");
	}
};