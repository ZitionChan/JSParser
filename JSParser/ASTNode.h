#pragma once

#include<unordered_map>
#include<string>
#include"Node.h"
#include"Identifier.h"

using namespace std;

class ASTNode {
	Node* node;
	ASTNode* prev;
	unordered_map<string, Identifier*> * LE;
public:
	ASTNode(Node* n, ASTNode* p) :node(n), prev(p) {

	}

	void put(string n, Identifier* id) {
		LE->insert(pair<string, Identifier*>(n, id));
	}

	

};