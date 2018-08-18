#include<iostream>
#include<iomanip>
#include"utils.h"

using namespace std;

void printType(NodeType t,int layer) {
	cout << setw(layer * 2 + 4)<< "type: ";
	switch (t) {
	case Node_t:
		cout << "Node" << endl;
		break;
	case Expr_t:
		cout << "Expr" << endl;
		break;
	case Stmt_t:
		cout << "Stmt" << endl; break;
	case ArrayExpr_t:

		cout << "ArrayExpr" << endl; break;
	case AssignmentExpr_t:
		cout << "AssignmentExpr" << endl; break;
	case BinaryExpr_t:
		cout << "BinaryExpr" << endl; break;
	case BlockStmt_t:
		cout << "BlockStmt" << endl; break;
	case BoolLiteral_t:
		cout << "BoolLiteral" << endl; break;
	case CallExpr_t:
		cout << "CallExpr" << endl; break;
	case Decl_t:
		cout << "Decl" << endl; break;
	case DoWhileStmt_t:
		cout << "DoWhileStmt" << endl; break;
	case ForStmt_t:
		cout << "ForStmt" << endl; break;
	case FunctionDecl_t:
		cout << "FunctionDecl" << endl; break;
	case FunctionExpr_t:
		cout << "FunctionExpr" << endl; break;
	case Identifier_t:
		cout << "Identifier" << endl; break;
	case IfStmt_t:
		cout << "IfStmt" << endl; break;
	case Literal_t:
		cout << "Literal" << endl; break;
	case LogicExpr_t:
		cout << "LogicExpr" << endl; break;
	case NewExpr_t:
		cout << "NewExpr" << endl; break;
	case NumberLiteral_t:
		cout << "NumberLiteral" << endl; break;
	case Program_t:
		cout << "Program" << endl; break;
	case ReturnStmt_t:
		cout << "ReturnStmt" << endl; break;
	case SequenceExpr_t:
		cout << "SequenceExpr" << endl; break;
	case StringConstant_t:
		cout << "StringConstant" << endl; break;
	case UnaryExpr_t:
		cout << "UnaryExpr" << endl; break;
	case UpdateExpr_t:
		cout << "UpdateExpr" << endl; break;
	case VariableDeclaration_t:
		cout << "VariableDeclaration" << endl; break;
	case VariableDeclarator_t:
		cout << "VariableDeclarator" << endl; break;
	case WhileStmt_t:
		cout << "WhileStmt" << endl; break;
	default:
		cout << "Unknown Type" << endl;
		break;

	}
}

string typeToStr(NodeType t ) {
	switch (t) {
	case Node_t:
		 return "Node" ;
		 
	case Expr_t:
		 return "Expr" ;
		 
	case Stmt_t:
		 return "Stmt" ;  
	case ArrayExpr_t:

		 return "ArrayExpr" ;  
	case AssignmentExpr_t:
		 return "AssignmentExpr" ;  
	case BinaryExpr_t:
		 return "BinaryExpr" ;  
	case BlockStmt_t:
		 return "BlockStmt" ;  
	case BoolLiteral_t:
		 return "BoolLiteral" ;  
	case CallExpr_t:
		 return "CallExpr" ;  
	case Decl_t:
		 return "Decl" ;  
	case DoWhileStmt_t:
		 return "DoWhileStmt" ;  
	case ForStmt_t:
		 return "ForStmt" ;  
	case FunctionDecl_t:
		 return "FunctionDecl" ;  
	case FunctionExpr_t:
		 return "FunctionExpr" ;  
	case Identifier_t:
		 return "Identifier" ;  
	case IfStmt_t:
		 return "IfStmt" ;  
	case Literal_t:
		 return "Literal" ;  
	case LogicExpr_t:
		 return "LogicExpr" ;  
	case NewExpr_t:
		 return "NewExpr" ;  
	case NumberLiteral_t:
		 return "NumberLiteral" ;  
	case Program_t:
		 return "Program" ;  
	case ReturnStmt_t:
		 return "ReturnStmt" ;  
	case SequenceExpr_t:
		 return "SequenceExpr" ;  
	case StringConstant_t:
		 return "StringConstant" ;  
	case UnaryExpr_t:
		 return "UnaryExpr" ;  
	case UpdateExpr_t:
		 return "UpdateExpr" ;  
	case VariableDeclaration_t:
		 return "VariableDeclaration" ;  
	case VariableDeclarator_t:
		 return "VariableDeclarator" ;  
	case WhileStmt_t:
		 return "WhileStmt" ;  
	default:
		 return "Unknown Type" ;

	}
}