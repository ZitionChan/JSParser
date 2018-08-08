#include<iostream>
#include<fstream>
#include"utils.h"
#include"Lexer.h"
#include"Tag.h"
#include"Parser.h"

string path = "test.txt";

ifstream ifile(path);

void LexerTest(Lexer &lexer) {
	while (!lexer.eof()){
		Token* token = lexer.scan();
		if (token) {
			switch (token->tag) {
			case NUMBER:
				cout << "( NUMBER ," << token->toString() << " )" << endl; break;
			case ID:
				cout << "( ID ," << token->toString() << " )" << endl; break;
			case IF:
			case VAR:
				cout << "( KEYWORD ," << token->toString() << " )" << endl; break;
			case STRING:
				cout << "(STRING, \'" << token->toString() << "\' )" << endl; break;
			default:
				cout << "( TOKEN ," << token->toString() << " )" << endl; break;
			}
		}
	}
}

void ParserTest(Lexer &lexer) {
	Parser parser(&lexer);
	try {
		parser.run();
	}
	catch (string err) {
		cout << err << endl;
	}
	parser.display();
}

int main() {
	Lexer lexer(&ifile);
	
	ParserTest(lexer);
	//LexerTest(lexer);

	system("pause");
	return 0;

}

