#include"BinaryExpr.h"
#include"Tag.h"

BinaryExpr::BinaryExpr(Token* opp, Expr* l, Expr* r, NodeType t ) :Node(t), op(opp), left(l), right(r) {
	Value result;
	switch (opp->tag)
	{
	case '+':
		result = l->getValue() + r->getValue();
		break;
	case '-':
		result = l->getValue() - r->getValue();
		break;
	case '*':
		result = l->getValue() * r->getValue();
		break;
	case '/':
		result = l->getValue() / r->getValue();
		break;
	case '<':
		result = l->getValue() < r->getValue();
		break;
	case LE:
		result = l->getValue() <= r->getValue();
		break;
	case '>':
		result = l->getValue() > r->getValue();
		break;
	case GE:
		result = l->getValue() >= r->getValue();
		break;
	case EQ:
		result = l->getValue() == r->getValue();
		break;
	case NE:
		result = l->getValue() != r->getValue();
		break;
		default:
			break;
	}
	this->setValue(result);
}