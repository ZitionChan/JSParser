#pragma once
#include<vector>
#include"Node.h"

using namespace std;

class Program :public Node {
	vector<Node*> body;
public:
	Program():body(){}

	void append(Node* n) {
		body.push_back(n);
	}

	void display() {
		cout << "Program body[" << body.size() << "]:" << endl;
		for (int i = 0; i < body.size(); i++) {
			cout << "	";
			body[i]->display();
		}
	}
};