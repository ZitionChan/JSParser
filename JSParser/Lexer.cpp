#include"Lexer.h"
#include"Number.h"
#include"Tag.h"


int Lexer::line = 1;

Lexer::Lexer(ifstream* is):peek(' '),reader(is) {
	initReserve();//加载保留字
}

//加入保留字
void Lexer::reserve(Word* w) {
	words.insert(pair<string,Word*>(w->toString(), w));
}

//读取一个字符
void Lexer::readch() {
	reader->get(peek);
}

bool Lexer::readch(char c) {
	readch();
	if (peek != c) return false;
	peek = ' ';
	return true;
}


//预载保留字
void Lexer::initReserve() {
	reserve(new Word("abstract", ABSTRACT));
	reserve(new Word("argument", ARGUMENTS));
	reserve(new Word("boolean", BOOLEAN));
	reserve(new Word("break", BREAK));
	reserve(new Word("byte", BYTE));
	reserve(new Word("case", CASE));
	reserve(new Word("catch", CATCH));
	reserve(new Word("char", CHAR));
	reserve(new Word("class", CLASS));
	reserve(new Word("const", CONST));
	reserve(new Word("continue", CONTINUE));
	reserve(new Word("debugger", DEBUGGER));
	reserve(new Word("default", DEFAULT));
	reserve(new Word("delete", DELETE));
	reserve(new Word("do", DO));
	reserve(new Word("double", DOUBLE));
	reserve(new Word("else", ELSE));
	reserve(new Word("enum", ENUM));
	reserve(new Word("eval", EVAL));
	reserve(new Word("export", EXPORT));
	reserve(new Word("extends", EXTENDS));
	reserve(new Word("false", FALSE));
	reserve(new Word("final", FINAL));
	reserve(new Word("finally", FINALLY));
	reserve(new Word("float", FLOAT));
	reserve(new Word("for", FOR));
	reserve(new Word("function", FUNCTION));
	reserve(new Word("goto", GOTO));
	reserve(new Word("if", IF));
	reserve(new Word("implements", IMPLEMENTS));
	reserve(new Word("import", IMPORT));
	reserve(new Word("in", IN));
	reserve(new Word("instanceof", INSTANCEOF));
	reserve(new Word("int", INT));
	reserve(new Word("interface", INTERFACE));
	reserve(new Word("let", LET));
	reserve(new Word("long", LONG));
	reserve(new Word("native", NATIVE));
	reserve(new Word("new", NEW));
	reserve(new Word("null", Null));
	reserve(new Word("package", PACKAGE));
	reserve(new Word("private", PRIVATE));
	reserve(new Word("protected", PROTECTED));
	reserve(new Word("public", PUBLIC));
	reserve(new Word("return", RETURN));
	reserve(new Word("short", SHORT));
	reserve(new Word("static", STATIC));
	reserve(new Word("super", SUPER));
	reserve(new Word("switch", SWITCH));
	reserve(new Word("synchronized", SYNCHRONIZED));
	reserve(new Word("this", THIS));
	reserve(new Word("throw", THROW));
	reserve(new Word("throws", THROWS));
	reserve(new Word("transient", TRANSIENT));
	reserve(new Word("true", TRUE));
	reserve(new Word("try", TRY));
	reserve(new Word("typeof", TYPEOF));
	reserve(new Word("var", VAR));
	reserve(new Word("void", VOID));
	reserve(new Word("volatile", VOLATILE));
	reserve(new Word("while", WHILE));
	reserve(new Word("with", WITH));
	reserve(new Word("yield", YIELD));
	reserve(new Word("Array", ARRAY));
	reserve(new Word("Date", DATE));
	reserve(new Word("hasOwnProperty", HASOWNPROPERTY));
	reserve(new Word("infinity", INFINITY));
	reserve(new Word("isFinite", ISFINITE));
	reserve(new Word("isNaN", ISNAN));
	reserve(new Word("isPrototypeOf", ISPROTOTYPEOF));
	reserve(new Word("length", LENGTH));
	reserve(new Word("Math", MATH));
	reserve(new Word("NaN", Nan));
	reserve(new Word("name", NAME));
	reserve(new Word("Number", NUMBER));
	reserve(new Word("Object", OBJECT));
	reserve(new Word("prototype", PROTOTYPE));
	reserve(new Word("String", STRING));
	reserve(new Word("toString", TOSTRING));
	reserve(new Word("undefined", UNDEFINED));
	reserve(new Word("valueOf", VALUEOF));
}


void Lexer::ignoreSpace() {
	for (;; readch()) {
		if (peek == ' ' || peek == '\t') continue;
		else if (peek == '\n') line = line + 1;
		else break;
	}
}

void Lexer::ignoreComment() {
	if (peek == '/') {
		if (readch('*')) {
			for (;;) {
				readch();
				if (peek == '*'&&readch('/')) break;
			}
		}
	}
}
Token* Lexer::scan() {
	do {
		//忽略空格
		ignoreSpace();
		//忽略注释
		ignoreComment();
	} while (peek == ' '||peek == '\t'||peek == '\n');

	switch (peek)
	{
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
	case '\'':
		isStringConstant = !isStringConstant;
		peek = ' ';
		return new Token('\'');
	case '\"':
		isStringConstant = !isStringConstant;
		peek = ' ';
		return new Token('\"');
	default:
		break;
	}
	//如果是数字
	if (isDigit(peek)) {
		int v = 0;
		do {
			v = 10 * v + Digit(peek);
			readch();
		} while (isDigit(peek));
		if (peek != '.') {
			return new Number(v);
		}
		//如果是小数
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

		if (words.find(buff) != words.end()) {//已经在words中
			return words[buff];
		}
		Word* w = new Word(buff, ID);
		words.insert(pair<string, Word*>(buff, w));
		return w;
	}

	Token* tok = new Token(peek);
	peek = ' '
		;
	return tok;
}

