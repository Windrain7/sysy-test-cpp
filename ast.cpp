#include "ast.h"

void CompUnitAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void DeclDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstDeclAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstDefListAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void TermAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ArraysAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstInitValAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstInitValListAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void VarDeclAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void VarDefListAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void VarDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void InitValAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void InitValListAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncFParamListAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}


void FuncFParamAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}


void BlockAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void BlockItemListAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void BlockItemAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void StmtAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ReturnStmtAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void SelectStmtAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void IterationStmtAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

//void BTypeAST::accept(Visitor &visitor) {
//    visitor.visit(*this);
//}
//
//void VoidTypeAST::accept(Visitor &visitor) {
//    visitor.visit(*this);
//}

void ExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
//    this->addExp->accept(visitor);
}

void AddExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void MulExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void UnaryExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

//void UnaryOpAST::accept(Visitor &visitor) {
//    visitor.visit(*this);
//}

void PrimaryExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void NumberAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void CallAST::accept(Visitor &visitor) {
    visitor.visit(*this);

}

void FuncCParamListAST::accept(Visitor &visitor) {
    visitor.visit(*this);

}

void ExpArraysAST::accept(Visitor &visitor) {
    visitor.visit(*this);

}

void LValAST::accept(Visitor &visitor) {
    visitor.visit(*this);

}

void CondAST::accept(Visitor &visitor) {
    visitor.visit(*this);
//    this->lOrExp->accept(visitor);
}

void RelExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);

}

void EqExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void LAndExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void LOrExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

