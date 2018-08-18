#include"LogicExpr.h"
#include"Tag.h"

LogicExpr::LogicExpr(Token* op, Expr* left, Expr* right, NodeType t) :Node(t), BinaryExpr(op, left, right) {
	switch (op->tag)
	{
	case AND:
		setValue(left->getValue() && right->getValue());
		break;
	case OR:
		setValue(left->getValue() || right->getValue());
		break;
	default:
		break;
	}
}