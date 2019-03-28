#pragma once
#include<iostream>
#include<iomanip>
#include"NodeType.h"
#include"Value.h"

class Node {
protected:
	Value value;
	bool isExecute; //��ʶ�ýڵ��Ƿ�ִ�У�Ĭ��Ϊfalse
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

		showTitle(); //��ӡ����ִ�е����
	}

	virtual string getName(){ //��ȡ�ý��������
		return "node";
	}

	virtual void showTitle() {
		string name = getName();
		if(name!= "")
		cout << getName() << endl;
	}

	virtual int totalExpr(){ //ͳ�Ƹýڵ��µı��ʽ
		return 1;
	}

	virtual int totalExeExpr() { //ͳ�Ƹýڵ�����ִ�й��ı��ʽ��
		return isExecute ? 1 : 0;
	}

};