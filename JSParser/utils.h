//ʵ�ú���
#pragma once

#include<string>
#include<sstream>

using namespace std;

template<class T>
inline string toStr(T t) {
	stringstream sstream;
	sstream << t;
	return sstream.str();
}

inline bool isDigit(char c) { //�ж��Ƿ�������
	return c >= '0' && c <= '9';
}

inline bool isLetter(char c) {//�ж��Ƿ�����ĸ
	return (c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z');
}

inline bool isLetterOrDigit(char c) {
	return isDigit(c) || isLetter(c);
}

inline int Digit(char c) { //���ַ�ת������
	if (!isDigit(c)) {
		throw "Digit(char c): parameter c is not digit";
	}
	return (int)(c - '0');
}

