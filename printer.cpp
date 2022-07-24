#include "printer.h"

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
        ast.varDecl->accept(*this);
    } else if (ast.constDecl != nullptr) {
        ast.constDecl->accept(*this);
    } else {
        ast.funcDef->accept(*this);
    }
}

void Printer::visit(ConstDeclAST &ast) {
    PUT(depth);
    cout << "ConstDeclAST:" << endl;
    depth += 2;
    PUT(depth);
    if (ast.bType == TYPE_INT) cout << "BType:int" << endl;
    else cout << "BType:float" << endl;
    ast.constDefListAST->accept(*this);
    depth -= 2;
}

void Printer::visit(ConstDefListAST &ast) {
    PUT(depth);
    cout << "ConstDefListAST:" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(ConstDefAST &ast) {
    PUT(depth);
    cout << "ConstDefAST:" << endl;
    depth += 2;
    ast.term->accept(*this);
    ast.constInitVal->accept(*this);
    depth -= 2;
}

void Printer::visit(TermAST &ast) {
    PUT(depth);
    cout << "TermAST:" << endl;
    depth += 2;
    PUT(depth);
    cout << "id:" << (*ast.id) << endl;
    if (ast.arrays != nullptr) ast.arrays->accept(*this);
    depth -= 2;
}

void Printer::visit(ArraysAST &ast) {
    PUT(depth);
    cout << "ArraysAST:" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(ConstInitValAST &ast) {
    PUT(depth);
    cout << "ConstInitValAST:";
    depth += 2;
    if (ast.constExp != nullptr) {
        cout << endl;
        ast.constExp->accept(*this);
    } else if (ast.constInitValList != nullptr) {
        cout << endl;
        ast.constInitValList->accept(*this);
    } else {
        cout << "{}" << endl;
    }
    depth -= 2;
}

void Printer::visit(ConstInitValListAST &ast) {
    PUT(depth);
    cout << "ConstInitValListAST：" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(VarDeclAST &ast) {
    PUT(depth);
    cout << "VarDeclAST：" << endl;
    depth += 2;
    PUT(depth);
    if (ast.bType == TYPE_INT) cout << "BType:int" << endl;
    else if (ast.bType == TYPE_FLOAT) cout << "BType:float" << endl;
    ast.varDefList->accept(*this);
    depth -= 2;
}

void Printer::visit(VarDefListAST &ast) {
    PUT(depth);
    cout << "VarDefListAST：" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(VarDefAST &ast) {
    PUT(depth);
    cout << "VarDefAST：" << endl;
    depth += 2;
    ast.term->accept(*this);
    if (ast.initVal != nullptr) ast.initVal->accept(*this);
    depth -= 2;
}

void Printer::visit(InitValAST &ast) {
    PUT(depth);
    cout << "InitValAST：";
    depth += 2;
    if (ast.exp != nullptr) {
        cout << endl;
        ast.exp->accept(*this);
    } else if (ast.initValList != nullptr) {
        cout << endl;
        ast.initValList->accept(*this);
    } else {
        cout << "{}" << endl;
    }
    depth -= 2;
}

void Printer::visit(InitValListAST &ast) {
    PUT(depth);
    cout << "InitValListAST：" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(FuncDefAST &ast) {
    PUT(depth);
    cout << "FuncDefAST:" << endl;
    depth += 2;
    PUT(depth);
    if (ast.funcType == TYPE_VOID) cout << "funcType:void" << endl;
    else if (ast.funcType == TYPE_INT) cout << "funcType:int" << endl;
    else cout << "funcType:float" << endl;
    PUT(depth); cout << "id:" << *ast.id << endl;
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

//void Printer::visit(BTypeAST &ast) {
//    PUT(depth);
//    cout << "BTypeAST:";
//    if (ast.isInt) cout << "int" << endl;
//    else cout << "float" << endl;
//}
//
//void Printer::visit(VoidTypeAST &ast) {
//    PUT(depth);
//    cout << "VoidTypeAST:void" << endl;
//}

void Printer::visit(FuncFParamListAST &ast) {
    PUT(depth);
    cout << "FuncFParamListAST:" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(FuncFParamAST &ast) {
    PUT(depth);
    cout << "FuncFParamAST:" << endl;
    depth += 2;
    PUT(depth);
    if (ast.bType == TYPE_INT) cout << "BType:int" << endl;
    else cout << "BType:float" << endl;
    PUT(depth); cout << "id:" << *ast.id << endl;
    if (ast.isArray) {
        PUT(depth);
        cout << "Array:first dimension" << endl;

    }
    if (ast.expArrays != nullptr) {
        ast.expArrays->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(ExpArraysAST &ast) {
    PUT(depth);
    cout << "ExpArraysAST:" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(BlockAST &ast) {
    PUT(depth);
    cout << "BlockAST:" << endl;
    depth += 2;
    if (ast.blockItemList != nullptr) ast.blockItemList->accept(*this);
    depth -= 2;
}

void Printer::visit(BlockItemListAST &ast) {
    PUT(depth);
    cout << "BlockItemListAST:" << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(BlockItemAST &ast) {
    if (ast.varDecl != nullptr) {
        ast.varDecl->accept(*this);
    } else if (ast.constDecl != nullptr) {
        ast.constDecl->accept(*this);
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
            ast.lVal->accept(*this);
            ast.exp->accept(*this);
            depth -= 2;
            break;
        case EXP:
            cout << endl;
            depth += 2;
            ast.exp->accept(*this);
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
            cout << endl;
            depth += 2;
            ast.selectStmt->accept(*this);
            depth -= 2;
            break;
        case ITER:
            cout << endl;
            depth += 2;
            ast.iterationStmt->accept(*this);
            depth -= 2;
            break;
    }

}

void Printer::visit(ReturnStmtAST &ast) {
    PUT(depth);
    cout << "return:";
    if (ast.exp == nullptr) cout << "void" << endl;
    else {
        cout << endl;
        depth += 2;
        ast.exp->accept(*this);
        depth -= 2;
    }
}

void Printer::visit(SelectStmtAST &ast) {
    PUT(depth);
    cout << "SelectStmtAST:" << endl;
    depth += 2;
    ast.cond->accept(*this);
    ast.ifStmt->accept(*this);
    if (ast.elseStmt != nullptr) ast.elseStmt->accept(*this);
    depth -= 2;
}

void Printer::visit(IterationStmtAST &ast) {
    PUT(depth);
    cout << "IterationStmtAST:" << endl;
    depth += 2;
    ast.cond->accept(*this);
    ast.stmt->accept(*this);
    depth -= 2;
}

void Printer::visit(ExpAST &ast) {
    PUT(depth);
    cout << "ExpAST:" << endl;
    depth += 2;
    ast.addExp->accept(*this);
    depth -= 2;
}

void Printer::visit(CondAST &ast) {
    PUT(depth);
    cout << "CondAST:" << endl;
    depth += 2;
    ast.lOrExp->accept(*this);
    depth -= 2;
}

void Printer::visit(AddExpAST &ast) {
    PUT(depth);
    cout << "AddExpAST:" <<endl;
    depth += 2;
    if (ast.addExp != nullptr) {
        ast.addExp->accept(*this);
        PUT(depth);
        cout << "AOP:";
        if (ast.op == AOP_ADD) cout << "+" << endl;
        else cout << "-" << endl;
    }
    ast.mulExp->accept(*this);
    depth -= 2;
}

void Printer::visit(MulExpAST &ast) {
    PUT(depth);
    cout << "MulExpAST:" << endl;
    depth += 2;
    if (ast.mulExp != nullptr) {
        ast.mulExp->accept(*this);
        PUT(depth);
        cout << "MOP:";
        if (ast.op == MOP_MUL) cout << "*" << endl;
        else if(ast.op == MOP_DIV) cout << "/" << endl;
        else cout << "%" << endl;
    }
    ast.unaryExp->accept(*this);
    depth -= 2;
}

void Printer::visit(UnaryExpAST &ast) {
    PUT(depth);
    cout << "UnaryExpAST:" << endl;
    depth += 2;
    if (ast.primaryExp != nullptr) {
        ast.primaryExp->accept(*this);
    } else if (ast.call != nullptr) {
        ast.call->accept(*this);
    } else {
        PUT(depth);
        cout << "UnaryOp:";
        if (ast.op == UOP_ADD) cout << "+" <<endl;
        if (ast.op == UOP_MINUS) cout << "-" <<endl;
        if (ast.op == UOP_NOT) cout << "!" <<endl;
//        ast.unaryOp->accept(*this);
        ast.unaryExp->accept(*this);
    }
    depth -= 2;
}

//void Printer::visit(UnaryOpAST &ast) {
//    PUT(depth);
//    cout << "UnaryOp:";
//    if (ast.op == UOP_ADD) cout << "+" << endl;
//    else if (ast.op == UOP_MINUS) cout << "-" << endl;
//    else cout << "!" <<endl;
//}

void Printer::visit(PrimaryExpAST &ast) {
    PUT(depth);
    cout << "PrimaryExpAST:" << endl;
    depth += 2;
    if (ast.exp != nullptr) {
        ast.exp->accept(*this);
    } else if (ast.lval != nullptr) {
        ast.lval->accept(*this);
    } else {
        ast.number->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(CallAST &ast) {
    PUT(depth);
    cout << "CallAST:" << endl;
    depth += 2;
    PUT(depth);
    cout << "id:" << (*ast.id) << endl;
    if (ast.funcCParamList != nullptr) ast.funcCParamList->accept(*this);
    depth -= 2;
}

void Printer::visit(FuncCParamListAST &ast) {
    PUT(depth);
    cout << "FuncCParamListAST:" << ast.list.size() << endl;
    depth += 2;
    for (auto &i : ast.list) {
        i->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(LValAST &ast) {
    PUT(depth);
    cout << "LValAST:" << endl;
    depth += 2;
    PUT(depth);cout << "id:" << (*ast.id) << endl;
    if (ast.expArrays != nullptr) ast.expArrays->accept(*this);
    depth -= 2;
}

void Printer::visit(NumberAST &ast) {
    PUT(depth);
    cout << "number:";
    if (ast.isInt) cout <<  ast.intval << endl;
    else cout <<  ast.floatval << endl;
}

void Printer::visit(RelExpAST &ast) {
    PUT(depth);
    cout << "RelExpAST:" << endl;
    depth += 2;
    if (ast.relExp != nullptr) {
        ast.relExp->accept(*this);
        PUT(depth);
        cout << "RelOP:";
        if (ast.op == ROP_GTE) cout << ">=" << endl;
        else if (ast.op == ROP_LTE) cout << "<=" << endl;
        else if (ast.op == ROP_GT) cout << ">" << endl;
        else if (ast.op == ROP_LT) cout << "<" << endl;
    }
    ast.addExp->accept(*this);
    depth -= 2;
}

void Printer::visit(EqExpAST &ast) {
    PUT(depth);
    cout << "EqExpAST:" << endl;
    depth += 2;
    if (ast.eqExp != nullptr) {
        ast.eqExp->accept(*this);
        PUT(depth);
        cout << "EqOP:";
        if (ast.op == EOP_EQ) cout << "==" << endl;
        else cout << "!=" <<endl;
    }
    ast.relExp->accept(*this);
    depth -= 2;
}

void Printer::visit(LAndExpAST &ast) {
    PUT(depth);
    cout << "LAndExpAST:" << endl;
    depth += 2;
    if (ast.lAndExp != nullptr) {
        ast.lAndExp->accept(*this);
        PUT(depth);
        cout << "AND_OP:&&";
    }
    ast.eqExp->accept(*this);
    depth -= 2;
}

void Printer::visit(LOrExpAST &ast) {
    PUT(depth);
    cout << "LOrExpAST:" << endl;
    depth += 2;
    if (ast.lOrExp != nullptr) {
        ast.lOrExp->accept(*this);
        PUT(depth);
        cout << "OR_OP:||";
    }
    ast.lAndExp->accept(*this);
    depth -= 2;
}

void Printer::visit(ConstExpAST &ast) {
    PUT(depth);
    cout << "ConstExpAST:" << endl;
    depth += 2;
    ast.addExp->accept(*this);
    depth -= 2;
}

