#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include"utils.h"
#include"Lexer.h"
#include"Tag.h"
#include"Parser.h"
#include"Value.h"


using namespace std;


enum mode {
	READFILE, SHOWTREE
};


void LexerTest(Lexer &lexer) {
	while (!lexer.eof()) {
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
	Parser parser(lexer);
	try {
		parser.run();
	}
	catch (string err) {
		cout << err << endl;
	}
	parser.display();
}


void readFile(string path) {
	//cin >> path;
	ifstream ifile(path);

	if (ifile) {
		Lexer lexer(&ifile);

		Parser parser(lexer);

		try {
			parser.run();
		}
		catch (string err) {
			cout << err << endl;
		}
		parser.display();

	}
	else {
		cout << "cann't open the file: " << path << endl;
	}

	ifile.close();
}

//交互模式
void interact(bool showTree = false) {
	// fstream testfile("./test.txt");
	// Lexer lexer(&testfile);

	Lexer lexer(&cin);
	Parser parser(lexer);
	while (!lexer.eof()) {
		cout << ">>>";
		try {
			parser.singleLine(showTree);
		}
		catch (string err) {
			cerr << err << endl;
		}



	}
	cout << endl;
}


int main(int argc, char* argv[]) {
	//ifstream file("test.txt");
	//Lexer lexer(&file);
	//LexerTest(lexer);
	cout << "Welcome To JSParser!" << endl;

	if (argc == 1) {
		interact();
		//readFile("test.txt");
	}
	else {

		if (string(argv[1]) == "-f") {
			if (argc == 2) {
				cout << "Need a file path" << endl;
			}
			else {
				string path = argv[2];
				readFile(path);
			}
		}
		else if (string(argv[1]) == "-t") {
			interact(true);
		}
		else if (string(argv[1]) == "-h") {
			cout << "直接运行JSParser进入交互界面\n"
				<< "-h			打开帮助\n"
				<< "-t			显示语法树\n"
				<< "-f filepath	解析文本文件中的语句并显示语法树" << endl;

		}
		else {
			cout << "command not found" << endl;
		}
	}

	return 0;

}
