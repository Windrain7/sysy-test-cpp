#ifndef TEST_AST_H
#define TEST_AST_H
#pragma once

#include "cstring"
#include <vector>
#include <memory>
#include <iostream>
#include "define.h"
#define PUT(n) printf("%*s", n, "")

using namespace std;
class Visitor;
class BaseAST;
//class ProgramAST;
class CompUnitAST;
class DeclDefAST;
class ConstDeclAST;
class BTypeAST;
class ConstDefListAST;
class ConstDefAST;
class TermAST;
class ArraysAST;
class ConstInitValAST;
class ConstInitValListAST;
class VarDeclAST;
class VarDefListAST;
class VarDefAST;
class InitValAST;
class InitValListAST;
class FuncDefAST;
class VoidTypeAST;
class FuncFParamListAST;
class FuncFParamAST;
class ExpArraysAST;
class BlockAST;
class BlockItemListAST;
class BlockItemAST;
class StmtAST;
class ReturnStmtAST;
class SelectStmtAST;
class IterationStmtAST;
class ExpAST;
class CondAST;
class LValAST;
class PrimaryExpAST;
class NumberAST;
class UnaryExpAST;
class UnaryOpAST;
class CallAST;
class FuncCParamListAST;
class MulExpAST;
class AddExpAST;
class RelExpAST;
class EqExpAST;
class LAndExpAST;
class LOrExpAST;
class ConstExpAST;

class BaseAST {
public:
    virtual void accept(Visitor &visitor) = 0;
    BaseAST() = default;
    virtual ~BaseAST() = default;
};

class CompUnitAST : public BaseAST {
public:
    vector<unique_ptr<BaseAST>> declDefList;
    void accept(Visitor &visitor) override;

};

class DeclDefAST : public BaseAST {
public:
    unique_ptr<BaseAST> constDecl = nullptr;
    unique_ptr<BaseAST> varDecl = nullptr;
    unique_ptr<BaseAST> funcDef = nullptr;
    void accept(Visitor &visitor) override;
};

class ConstDeclAST : public BaseAST {
public:
    unique_ptr<BaseAST> bType, constDefListAST;
    void accept(Visitor &visitor) override;
};

class ConstDefListAST :public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class ConstDefAST :public BaseAST {
public:
    unique_ptr<BaseAST> term, constInitVal;
    void accept(Visitor &visitor) override;
};

class TermAST:public BaseAST {
public:
    unique_ptr<string> id;
    unique_ptr<BaseAST> arrays;
    void accept(Visitor &visitor) override;
};

class ArraysAST : public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class ConstInitValAST: public BaseAST {
public:
    unique_ptr<BaseAST> constExp, constInitValList;
    void accept(Visitor &visitor) override;
};

class ConstInitValListAST: public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class VarDeclAST : public BaseAST {
public:
    unique_ptr<BaseAST> bType, varDefList;
    void accept(Visitor &visitor) override;
};

class VarDefListAST:public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class VarDefAST:public BaseAST {
public:
    unique_ptr<BaseAST> term, initVal;
    void accept(Visitor &visitor) override;
};

class InitValAST:public BaseAST {
public:
    unique_ptr<BaseAST> exp, initValList;
    void accept(Visitor &visitor) override;
};

class InitValListAST:public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class FuncDefAST : public BaseAST {
public:
    unique_ptr<string> id;
    unique_ptr<BaseAST> funcType = nullptr;
    unique_ptr<BaseAST> funcFParamList = nullptr;
    unique_ptr<BaseAST> blockAst = nullptr;
    void accept(Visitor &visitor) override;
};

class BTypeAST : public BaseAST {
public:
    bool isInt = false;
    void accept(Visitor &visitor) override;
};

class VoidTypeAST : public BaseAST {
public:
    void accept(Visitor &visitor) override;
};

class FuncFParamListAST : public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class FuncFParamAST:public BaseAST {
public:
    unique_ptr<BaseAST> bType = nullptr;
    unique_ptr<string> id;
    bool isArray = false; //用于区分是否是数组参数，此时一维数组和多维数组expArrays都是nullptr
    unique_ptr<BaseAST> expArrays = nullptr;
    void accept(Visitor &visitor) override;
};

class ExpArraysAST : public BaseAST {
public:
    // 各维长度为Exp的数组，需要注意如果是作为函数参数则实际还要多出一维
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class BlockAST : public BaseAST {
public:
    unique_ptr<BaseAST> blockItemList = nullptr;
    void accept(Visitor &visitor) override;
};

class BlockItemListAST :public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class BlockItemAST : public BaseAST {
public:
    unique_ptr<BaseAST> constDecl = nullptr;
    unique_ptr<BaseAST> varDecl = nullptr ;
    unique_ptr<BaseAST> stmt = nullptr;
    void accept(Visitor &visitor) override;
};

class StmtAST : public BaseAST {
public:
    STYPE sType;
    unique_ptr<BaseAST> lVal = nullptr;
    unique_ptr<BaseAST> exp= nullptr;
    unique_ptr<BaseAST> returnStmt = nullptr;
    unique_ptr<BaseAST> selectStmt = nullptr;
    unique_ptr<BaseAST> iterationStmt = nullptr;
    unique_ptr<BaseAST> block = nullptr;
    void accept(Visitor &visitor) override;
};

class ReturnStmtAST : public BaseAST {
public:
    unique_ptr<BaseAST> exp = nullptr;
    void accept(Visitor &visitor) override;
};

class SelectStmtAST:public BaseAST {
public:
    unique_ptr<BaseAST> cond, ifStmt, elseStmt;
    void accept(Visitor &visitor) override;
};

class IterationStmtAST:public BaseAST {
public:
    unique_ptr<BaseAST> cond, stmt;
    void accept(Visitor &visitor) override;
};

class ExpAST :public BaseAST {
public:
    unique_ptr<BaseAST> addExp = nullptr;
    void accept(Visitor &visitor) override;
};

class AddExpAST : public BaseAST {
public:
    unique_ptr<BaseAST> addExp, mulExp;
    AOP op;
    void accept(Visitor &visitor) override;
};

class MulExpAST :public BaseAST {
public:
    unique_ptr<BaseAST> unaryExp;
    unique_ptr<BaseAST> mulExp;
    MOP op;
    void accept(Visitor &visitor) override;
};

class UnaryExpAST :public BaseAST {
public:
    unique_ptr<BaseAST> primaryExp;
    unique_ptr<BaseAST> call;
    unique_ptr<BaseAST> unaryOp, unaryExp;
    void accept(Visitor &visitor) override;
};

class UnaryOpAST:public BaseAST {
public:
    UOP op;
    void accept(Visitor &visitor) override;
};



class PrimaryExpAST:public BaseAST {
public:
    unique_ptr<BaseAST> exp, lval, number;
    void accept(Visitor &visitor) override;
};

class NumberAST:public BaseAST {
public:
    bool isInt;
    union {
        int intval;
        float floatval;
    };
    void accept(Visitor &visitor) override;
};

class LValAST:public BaseAST {
public:
    unique_ptr<string> id;
    unique_ptr<BaseAST> expArrays;
    void accept(Visitor &visitor) override;
};

class CallAST:public BaseAST {
public:
    unique_ptr<string> id;
    unique_ptr<BaseAST> funcCParamList;
    void accept(Visitor &visitor) override;
};

class FuncCParamListAST : public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class CondAST:public BaseAST {
public:
    unique_ptr<BaseAST> lOrExp;
    void accept(Visitor &visitor) override;
};

class RelExpAST:public BaseAST {
public:
    unique_ptr<BaseAST> addExp, relExp;
    ROP op;
    void accept(Visitor &visitor) override;
};

class EqExpAST:public BaseAST {
public:
    unique_ptr<BaseAST> relExp, eqExp;
    EOP op;
    void accept(Visitor &visitor) override;
};

class LAndExpAST : public BaseAST {
public:
    // lAndExp不为空则说明有and符号，or类似
    unique_ptr<BaseAST> eqExp, lAndExp;
    void accept(Visitor &visitor) override;
};

class LOrExpAST:public BaseAST {
public:
    unique_ptr<BaseAST> lOrExp, lAndExp;
    void accept(Visitor &visitor) override;
};

class ConstExpAST : public BaseAST {
public:
    unique_ptr<BaseAST> addExp;
    void accept(Visitor &visitor) override;
};

class Visitor {
public:
    virtual void visit(CompUnitAST& ast) = 0;
    virtual void visit(DeclDefAST& ast) = 0;
    virtual void visit(ConstDeclAST& ast) = 0;
    virtual void visit(ConstDefListAST& ast) = 0;
    virtual void visit(ConstDefAST& ast) = 0;
    virtual void visit(TermAST& ast) = 0;
    virtual void visit(ArraysAST& ast) = 0;
    virtual void visit(ConstInitValAST& ast) = 0;
    virtual void visit(ConstInitValListAST& ast) = 0;
    virtual void visit(VarDeclAST& ast) = 0;
    virtual void visit(VarDefListAST& ast) = 0;
    virtual void visit(VarDefAST& ast) = 0;
    virtual void visit(InitValAST& ast) = 0;
    virtual void visit(InitValListAST& ast) = 0;
    virtual void visit(FuncDefAST& ast) = 0;
    virtual void visit(FuncFParamListAST& ast) = 0;
    virtual void visit(FuncFParamAST& ast) = 0;
    virtual void visit(ExpArraysAST& ast) = 0;
    virtual void visit(BlockAST& ast) = 0;
    virtual void visit(BlockItemListAST& ast) = 0;
    virtual void visit(BlockItemAST& ast) = 0;
    virtual void visit(StmtAST& ast) = 0;
    virtual void visit(ReturnStmtAST& ast) = 0;
    virtual void visit(SelectStmtAST& ast) = 0;
    virtual void visit(IterationStmtAST& ast) = 0;
    virtual void visit(BTypeAST& ast) = 0;
    virtual void visit(VoidTypeAST& ast) = 0;
    virtual void visit(ExpAST& ast) = 0;
    virtual void visit(AddExpAST& ast) = 0;
    virtual void visit(MulExpAST& ast) = 0;
    virtual void visit(UnaryExpAST& ast) = 0;
    virtual void visit(UnaryOpAST& ast) = 0;
    virtual void visit(PrimaryExpAST& ast) = 0;
    virtual void visit(CondAST& ast) = 0;
    virtual void visit(LValAST& ast) = 0;
    virtual void visit(NumberAST& ast) = 0;
    virtual void visit(CallAST& ast) = 0;
    virtual void visit(FuncCParamListAST& ast) = 0;
    virtual void visit(RelExpAST& ast) = 0;
    virtual void visit(EqExpAST& ast) = 0;
    virtual void visit(LAndExpAST& ast) = 0;
    virtual void visit(LOrExpAST& ast) = 0;
    virtual void visit(ConstExpAST& ast) = 0;
};

#endif //TEST_AST_H
