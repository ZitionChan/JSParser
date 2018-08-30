#include"Lexer.h"
#include"Number.h"
#include"Tag.h"
#include<iostream>
#include <vector>

using namespace std;

int Lexer::line = 1;

Lexer::Lexer(istream* is) :peek(' '), reader(is), isStringConstant(false) {
	initReserve();//���ر�����
}

//���뱣����
void Lexer::reserve(Word* w) {
	words.insert({ w->toString(), w });
}

//��ȡһ���ַ�
void Lexer::readch() {
	if (!reader->get(peek))
		peek = EOF;
}

bool Lexer::readch(char c) {
	readch();
	if (peek != c) return false;
	peek = ' ';
	return true;
}

//Ԥ�ر�����
void Lexer::initReserve() {
	vector<pair<string, Tag>> reserves = {
		{"abstract", ABSTRACT},
		{"argument", ARGUMENTS},
		{"boolean", BOOLEAN},
		{"break", BREAK},
		{"byte", BYTE},
		{"case", CASE},
		{"catch", CATCH},
		{"char", CHAR},
		{"class", CLASS},
		{"const", CONST},
		{"continue", CONTINUE},
		{"debugger", DEBUGGER},
		{"default", DEFAULT},
		{"delete", DELETE},
		{"do", DO},
		{"double", DOUBLE},
		{"else", ELSE},
		{"enum", ENUM},
		{"eval", EVAL},
		{"export", EXPORT},
		{"extends", EXTENDS},
		{"false", FALSE},
		{"final", FINAL},
		{"finally", FINALLY},
		{"float", FLOAT},
		{"for", FOR},
		{"function", FUNCTION},
		{"goto", GOTO},
		{"if", IF},
		{"implements", IMPLEMENTS},
		{"import", IMPORT},
		{"in", IN},
		{"instanceof", INSTANCEOF},
		{"int", INT},
		{"interface", INTERFACE},
		{"let", LET},
		{"long", LONG},
		{"native", NATIVE},
		{"new", NEW},
		{"null", Null},
		{"package", PACKAGE},
		{"private", PRIVATE},
		{"protected", PROTECTED},
		{"public", PUBLIC},
		{"return", RETURN},
		{"short", SHORT},
		{"static", STATIC},
		{"super", SUPER},
		{"switch", SWITCH},
		{"synchronized", SYNCHRONIZED},
		{"this", THIS},
		{"throw", THROW},
		{"throws", THROWS},
		{"transient", TRANSIENT},
		{"true", TRUE},
		{"try", TRY},
		{"typeof", TYPEOF},
		{"var", VAR},
		{"void", VOID},
		{"volatile", VOLATILE},
		{"while", WHILE},
		{"with", WITH},
		{"yield", YIELD},
		{"Array", ARRAY},
		{"Date", DATE},
		{"hasOwnProperty", HASOWNPROPERTY},
		{"infinity", Infinity},
		{"isFinite", ISFINITE},
		{"isNaN", ISNAN},
		{"isPrototypeOf", ISPROTOTYPEOF},
		{"length", LENGTH},
		{"Math", MATH},
		{"NaN", Nan},
		{"name", NAME},
		{"Number", NUMBER},
		{"Object", OBJECT},
		{"prototype", PROTOTYPE},
		{"String", STRING},
		{"toString", TOSTRING},
		{"undefined", UNDEFINED},
		{"valueOf", VALUEOF},
	};

	for (auto& r : reserves) {
		reserve(new Word(r.first, r.second));
	}
}

void Lexer::ignoreSpace() {
	for (; !eof(); readch()) {
		if (peek == ' ' || peek == '\t') continue;
		else break;
	}
}


Token* Lexer::scan() {

	if (isStringConstant && peek != '\'' && peek != '\"') {
		string stringconstant = readStringConstant();
		return new Word(stringconstant, STRING);
	}

	do {
		//���Կո�
		ignoreSpace();
		//����ע��
		if (peek == '/') {
			if (readch('*')) {
				for (; !eof();) {
					readch();
					if (peek == '*'&&readch('/')) break;
				}
			}
			else {
				return new Token('/');
			}
		}

		if (eof()) return nullptr;

	} while (peek == ' ' || peek == '\t');

	switch (peek)
	{
	case '\r':
		readch('\n');
		[[fallthrough]];
	case '\n':
		peek = ' ';
		line++;
		return new Token('\n');
	case '&':
		if (readch('&')) return Word::And;
		else return new Token('&');
	case '|':
		if (readch('|')) return Word::Or;
		else return new Token('|');
	case '=':
		if (readch('=')) return Word::Eq;
		else return new Token('=');
	case '!':
		if (readch('=')) return Word::Ne;
		else return new Token('!');
	case '<':
		if (readch('=')) return Word::Le;
		else return new Token('<');
	case '>':
		if (readch('=')) return Word::Ge;
		else return new Token('>');
	case '+':
		if (readch('+')) return Word::Add;
		else return new Token('+');
	case '-':
		if (readch('-')) return Word::Minus;
		else return new Token('-');
	case '\'':
		isStringConstant = !isStringConstant;
		readch();
		return new Token('\'');
	case '\"':
		isStringConstant = !isStringConstant;
		readch();
		return new Token('\"');
	default:
		break;
	}
	//���������
	if (isDigit(peek)) {
		int v = 0;
		do {
			v = 10 * v + Digit(peek);
			readch();
		} while (isDigit(peek));
		if (peek != '.') {
			return new Number(v);
		}
		//�����С��
		double x = v;
		double d = 10;
		for (;;) {
			readch();
			if (!isDigit(peek)) break;
			x = x + Digit(peek) / d;
			d = d * 10;
		}

		return new Number(x);
	}

	if (isLetter(peek)) {
		string buff;
		do {
			buff += peek;
			readch();
		} while (isLetterOrDigit(peek));

		if (words.find(buff) != words.end()) {//�Ѿ���words��
			return words[buff];
		}
		Word* w = new Word(buff, ID);
		words.insert(pair<string, Word*>(buff, w));
		return w;
	}

	Token* tok = new Token(peek);
	peek = ' ';
	return tok;
}

string Lexer::readStringConstant() {
	stringstream ss;
	while (peek != '\"' && peek != '\'') {
		ss << peek;
		readch();
	}

	return ss.str();
}

bool Lexer::eof() {
	return reader->eof();
}

void Lexer::run() {
	while (!eof()) {
		Token* token = scan();
		if (token) {
			switch (token->tag) {
			case NUMBER:
				cout << "( NUMBER ," << token->toString() << " )" << endl; break;
			case ID:
				cout << "( ID ," << token->toString() << " )" << endl; break;
			case STRING:
				cout << "(STRING, \'" << token->toString() << "\' )" << endl; break;
			default:
				if (token->tag >= 256 && token->tag <= 336) {
					cout << "( KEYWORD ," << token->toString() << " )" << endl;
				}
				else if (token->tag == '\n') {
					return;
				}
				else {
					cout << "( TOKEN ," << token->toString() << " )" << endl;
				}
				break;
			}
		}
	}
}