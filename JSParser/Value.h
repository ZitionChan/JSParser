#pragma once
#include<string>
#include<iostream>


using namespace std;

enum valueType{none_t,string_t,number_t,bool_t};

class Value {
		string stringVal;
		double numberVal;
		bool boolVal;
	valueType type;
public:
	Value():type(none_t){}

	Value(const char* val) :type(string_t) {
		stringVal = val;
	}

	Value(string val):type(string_t) {
		stringVal = val;
	}

	Value(double val) :numberVal(val), type(number_t) {
	}

	Value(int val) :numberVal(val),type(number_t) {
	}

	Value(bool val) :boolVal(val),type(bool_t) {
	}

	const Value operator+(const Value& v) const;
	const Value operator-(const Value& v) const;
	const Value operator*(const Value& v) const;
	const Value operator/(const Value& v) const;

	const Value operator&&(const Value& v)const;
	const Value operator||(const Value& v)const;

	bool operator<(const Value& v)const;
	bool operator>(const Value& v)const;
	bool operator<=(const Value& v)const;
	bool operator>=(const Value& v)const;
	bool operator==(const Value& v)const;
	bool operator!=(const Value& v)const;

	const Value& operator!();

	friend ostream& operator<<( ostream& os,const Value& v);

	void display() {
		switch (type)
		{
		case string_t:
			cout << stringVal << endl;
			break;
		case number_t:
			cout << numberVal << endl;
			break;
		case bool_t:
			cout << bool_t << endl;
			break;
		default:
			break;
		}
	}

};