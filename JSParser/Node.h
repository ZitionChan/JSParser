#pragma once
#include<iostream>

class Node {
protected:
	//int lexline;
public:
	Node() {};
	virtual void display(){
		cout << "one node" << endl;
	}
};