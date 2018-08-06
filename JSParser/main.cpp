#include<iostream>
#include<fstream>
#include"utils.h"
#include"Lexer.h"
#include"Tag.h"
#include"Parser.h"

string path = "test.txt";

ifstream ifile(path);
int main() {
	Lexer lexer(&ifile);
	Parser parser(&lexer);

	parser.program();
	/*do {
		Token* token= lexer.scan();
		switch (token->tag) {
		case NUMBER:
			cout << "( NUM ," << token->toString() << " )" << endl; break;
		case ID:
			cout << "( Identifier ," << token->toString() << " )" << endl; break;
		case IF:
			cout << "( KEY ," << token->toString() << " )" << endl; break;
		default:
			cout << "( TOKEN ," << token->toString() << " )" << endl; break;
		}

	} while (lexer.getPeek() != '\n'); */
	system("pause");
	return 0;

}