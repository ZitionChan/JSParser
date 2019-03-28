#pragma once
#include<iostream>
#include<iomanip>
#include"NodeType.h"
#include"Value.h"

class Node {
protected:
	Value value;
	bool isExecute; //标识该节点是否被执行，默认为false
public:
	NodeType type;
	Node(NodeType t=Node_t):type(t),isExecute(false) {};
	
	virtual void setValue(Value v) {
		value = v;
	}

	virtual Value getValue() {
		return value;
	}

	virtual void display(int layer=1){
		//cout << setw(layer * 2 + 2) << " " << "isExecute:" << isExecute << endl;
		//cout << "type:" << type << endl;
	}

	virtual void execute() {
		isExecute = true;

		showTitle(); //打印正在执行的语句
	}

	virtual string getName(){ //获取该结点字面量
		return "node";
	}

	virtual void showTitle() {
		string name = getName();
		if(name!= "")
		cout << getName() << endl;
	}

	virtual int totalExpr(){ //统计该节点下的表达式
		return 1;
	}

	virtual int totalExeExpr() { //统计该节点下已执行过的表达式数
		return isExecute ? 1 : 0;
	}

};