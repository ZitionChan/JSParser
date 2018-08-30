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

//Parser测试
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

//从文件读取
void readFile(string path) {

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

void tokenOnly() {
	Lexer lexer(&cin);

	while (!lexer.eof()) {
		cout << ">>>";
		lexer.run();
	}

}

int main(int argc, char* argv[]) {

	cout << "Welcome To JSParser!" << endl;

	if (argc == 1) {
		interact();
	}
	else {

		if (string(argv[1]) == "file") {
			if (argc == 2) {
				cout << "Need a file path" << endl;
			}
			else {
				string path = argv[2];
				readFile(path);
			}
		}
		else if (string(argv[1]) == "cli") {
			interact();
		}
		else if (string(argv[1]) == "tree") {
			interact(true);
		}
		else if (string(argv[1]) == "token") {
			tokenOnly();
		}
		else if (string(argv[1]) == "-h"|| string(argv[1])=="help") {
			cout << endl;
			cout << "Usage: JSParser <command> \n\n"
				<< "where <command> is one of:\n"
				<< "	cli ,file, tree, token, help\n\n"
				<< "cli  :  command line mode\n" 
				<< "file :  read from script file [Usage: JSParser file filepath]\n"
				<< "tree :  command line mode with printing the syntax tree\n"
				<< "token:  only lexer works\n"
				<< "help :  open help\n\n"
				<< "ctrl+c exit the program"
				<< endl;

		}
		else {
			cout << "command not found" << endl;
		}
	}

	//system("pause");
	return 0;

}
