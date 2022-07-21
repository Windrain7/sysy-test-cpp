#include "ast.h"

void CompUnitAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void DeclDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}


void BlockAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void BlockItemListAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncFParamListAST::accept(Visitor &visitor) {

}

void FuncFParamAST::accept(Visitor &visitor) {

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


void BTypeAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void VoidTypeAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ExpAST::accept(Visitor &visitor) {

}

void AddExpAST::accept(Visitor &visitor) {

}

void MulExpAST::accept(Visitor &visitor) {

}

void UnaryExpAST::accept(Visitor &visitor) {

}

void PrimaryExpAST::accept(Visitor &visitor) {

}

void CallAST::accept(Visitor &visitor) {

}

void FuncCParamListAST::accept(Visitor &visitor) {

}

void ExpArraysAST::accept(Visitor &visitor) {

}

void LValAST::accept(Visitor &visitor) {

}


void Printer::visit(CompUnitAST &ast) {
    PUT(depth);
    cout << "CompUnitAST:" << endl;
    depth += 2;
    for (auto &i : ast.declDefList) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(DeclDefAST &ast) {
    if (ast.varDecl != nullptr) {
//        ast->varDecl->accept(visitor);
    } else if (ast.constDecl != nullptr) {
//        ast->constDecl->accept(visitor);
    } else {
        ast.funcDef->accept(*this);
    }
}

void Printer::visit(FuncDefAST &ast) {
    PUT(depth);
    cout << "FuncDefAST:" << endl;
    depth += 2;
    PUT(depth); cout << "ID:" << *ast.id << endl;
    ast.funcType->accept(*this);
    if (ast.funcFParamList != nullptr) ast.funcFParamList->accept(*this);
    ast.blockAst->accept(*this);
    depth -= 2;
}

//void Printer::visit(FuncTypeAST &ast) {
//    PUT(depth);
//    cout << "FuncTypeAST:" << endl;
//    depth += 2;
//    if (ast.voidType != nullptr) ast.voidType->accept(*this);
//    else ast.bType->accept(*this);
//    depth -= 2;
//}

void Printer::visit(BTypeAST &ast) {
    PUT(depth);
    cout << "BTypeAST:";
    if (ast.isInt) cout << "int" << endl;
    else cout << "float" << endl;
}

void Printer::visit(VoidTypeAST &ast) {
    PUT(depth);
    cout << "VoidTypeAST:void" << endl;
}

void Printer::visit(BlockAST &ast) {
    PUT(depth);
    cout << "BlockAST:" << endl;
    depth += 2;
    if (ast.blockItemList != nullptr) ast.blockItemList->accept(*this);
    depth -= 2;
}

void Printer::visit(BlockItemListAST &ast) {
    for (auto &i : ast.list) {
        i->accept(*this);
    }
}

void Printer::visit(FuncFParamListAST &ast) {

}

void Printer::visit(BlockItemAST &ast) {
    if (ast.varDecl != nullptr) {
//        ast->varDecl->accept(visitor);
    } else if (ast.constDecl != nullptr) {
//        ast->constDecl->accept(visitor);
    } else {
        ast.stmt->accept(*this);
    }
}

void Printer::visit(StmtAST &ast) {
    PUT(depth);
    cout << "StmtAST:";
    switch (ast.sType) {
        case SEMI:
            cout << "semicolon" << endl;
            break;
        case ASS:
            cout << endl;
            depth += 2;
//            ast.lVal->accept(visitor);
//            ast.exp->accept(visitor);
            depth -= 2;
        case EXP:
            cout << endl;
            depth += 2;
//            ast.exp->accept(visitor);
            depth -= 2;
            break;
        case CONT:
            cout << "continue" << endl;
            break;
        case BRE:
            cout << "break" << endl;
            break;
        case RET:
            cout << endl;
            depth += 2;
            ast.returnStmt->accept(*this);
            depth -= 2;
            break;
        case BLK:
            cout << endl;
            depth += 2;
            ast.block->accept(*this);
            depth -= 2;
            break;
        case SEL:
            depth += 2;
//            ast.selectStmt->accept(*this);
            depth -= 2;
            break;
        case ITER:
            depth += 2;
//            ast.iterationStmt->accept(*this);
            depth -= 2;
            break;
    }

}

void Printer::visit(ReturnStmtAST &ast) {
    PUT(depth);
    cout << "return:";
    if (ast.exp == nullptr) cout << "void" << endl;
    else {
        depth += 2;
//        ast.exp->accept(*this);
        depth -= 2;
    }
}

void Printer::visit(ExpAST &ast) {

}

void Printer::visit(AddExpAST &ast) {

}

void Printer::visit(MulExpAST &ast) {

}

void Printer::visit(UnaryExpAST &ast) {

}

void Printer::visit(PrimaryExpAST &ast) {

}

void Printer::visit(CallAST &ast) {

}

void Printer::visit(FuncCParamListAST &ast) {

}