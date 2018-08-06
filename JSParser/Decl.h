#pragma once

#include"Stmt.h"
#include"Identifier.h"


class Decl :public Stmt {
protected:
	Identifier* id;
public:
	Decl(Identifier* i):id(i){}
};