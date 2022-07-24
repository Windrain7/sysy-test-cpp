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
class BaseAST;
class ProgramAST;
class CompUnitAST;
class DeclDefAST;
class ConstDeclAST;
//class BTypeAST;
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
//class VoidTypeAST;
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
//class UnaryOpAST;
class CallAST;
class FuncCParamListAST;
class MulExpAST;
class AddExpAST;
class RelExpAST;
class EqExpAST;
class LAndExpAST;
class LOrExpAST;
class ConstExpAST;

class Visitor;


class BaseAST {
public:
    virtual void accept(Visitor &visitor) = 0;
    BaseAST() = default;
    virtual ~BaseAST() = default;
};

class CompUnitAST : public BaseAST {
public:
    vector<unique_ptr<DeclDefAST>> declDefList;
    void accept(Visitor &visitor) override;

};

class DeclDefAST : public BaseAST {
public:
    unique_ptr<ConstDeclAST> constDecl = nullptr;
    unique_ptr<VarDeclAST> varDecl = nullptr;
    unique_ptr<FuncDefAST> funcDef = nullptr;
    void accept(Visitor &visitor) override;
};

class ConstDeclAST : public BaseAST {
public:
    TYPE bType;
    unique_ptr<ConstDefListAST> constDefListAST;
    void accept(Visitor &visitor) override;
};

class ConstDefListAST :public BaseAST {
public:
    vector<unique_ptr<ConstDefAST>> list;
    void accept(Visitor &visitor) override;
};

class ConstDefAST :public BaseAST {
public:
    unique_ptr<TermAST> term;
    unique_ptr<ConstInitValAST> constInitVal;
    void accept(Visitor &visitor) override;
};

class TermAST:public BaseAST {
public:
    unique_ptr<string> id;
    unique_ptr<ArraysAST> arrays;
    void accept(Visitor &visitor) override;
};

class ArraysAST : public BaseAST {
public:
    vector<unique_ptr<ConstExpAST>> list;
    void accept(Visitor &visitor) override;
};

class ConstInitValAST: public BaseAST {
public:
    unique_ptr<ConstExpAST> constExp;
    unique_ptr<ConstInitValListAST> constInitValList;
    void accept(Visitor &visitor) override;
};

class ConstInitValListAST: public BaseAST {
public:
    vector<unique_ptr<ConstInitValAST>> list;
    void accept(Visitor &visitor) override;
};

class VarDeclAST : public BaseAST {
public:
    TYPE bType;
    unique_ptr<VarDefListAST> varDefList;
    void accept(Visitor &visitor) override;
};

class VarDefListAST:public BaseAST {
public:
    vector<unique_ptr<VarDefAST>> list;
    void accept(Visitor &visitor) override;
};

class VarDefAST:public BaseAST {
public:
    unique_ptr<TermAST> term;
    unique_ptr<InitValAST> initVal;
    void accept(Visitor &visitor) override;
};

class InitValAST:public BaseAST {
public:
    unique_ptr<ExpAST> exp;
    unique_ptr<InitValListAST> initValList;
    void accept(Visitor &visitor) override;
};

class InitValListAST:public BaseAST {
public:
    vector<unique_ptr<InitValAST>> list;
    void accept(Visitor &visitor) override;
};

class FuncDefAST : public BaseAST {
public:
    unique_ptr<string> id;
    TYPE funcType;
    unique_ptr<FuncFParamListAST> funcFParamList = nullptr;
    unique_ptr<BlockAST> blockAst = nullptr;
    void accept(Visitor &visitor) override;
};

class FuncFParamListAST : public BaseAST {
public:
    vector<unique_ptr<FuncFParamAST>> list;
    void accept(Visitor &visitor) override;
};

class FuncFParamAST:public BaseAST {
public:
    TYPE bType;
    unique_ptr<string> id;
    bool isArray = false; //用于区分是否是数组参数，此时一维数组和多维数组expArrays都是nullptr
    unique_ptr<ExpArraysAST> expArrays = nullptr;
    void accept(Visitor &visitor) override;
};

class ExpArraysAST : public BaseAST {
public:
    // 各维长度为Exp的数组，需要注意如果是作为函数参数则实际还要多出一维
    vector<unique_ptr<ExpAST>> list;
    void accept(Visitor &visitor) override;
};

class BlockAST : public BaseAST {
public:
    unique_ptr<BlockItemListAST> blockItemList = nullptr;
    void accept(Visitor &visitor) override;
};

class BlockItemListAST :public BaseAST {
public:
    vector<unique_ptr<BlockItemAST>> list;
    void accept(Visitor &visitor) override;
};

class BlockItemAST : public BaseAST {
public:
    unique_ptr<ConstDeclAST> constDecl = nullptr;
    unique_ptr<VarDeclAST> varDecl = nullptr ;
    unique_ptr<StmtAST> stmt = nullptr;
    void accept(Visitor &visitor) override;
};

class StmtAST : public BaseAST {
public:
    STYPE sType;
    unique_ptr<LValAST> lVal = nullptr;
    unique_ptr<ExpAST> exp= nullptr;
    unique_ptr<ReturnStmtAST> returnStmt = nullptr;
    unique_ptr<SelectStmtAST> selectStmt = nullptr;
    unique_ptr<IterationStmtAST> iterationStmt = nullptr;
    unique_ptr<BlockAST> block = nullptr;
    void accept(Visitor &visitor) override;
};

class ReturnStmtAST : public BaseAST {
public:
    unique_ptr<ExpAST> exp = nullptr;
    void accept(Visitor &visitor) override;
};

class SelectStmtAST:public BaseAST {
public:
    unique_ptr<CondAST> cond;
    unique_ptr<StmtAST> ifStmt, elseStmt;
    void accept(Visitor &visitor) override;
};

class IterationStmtAST:public BaseAST {
public:
    unique_ptr<CondAST> cond;
    unique_ptr<StmtAST> stmt;
    void accept(Visitor &visitor) override;
};

class ExpAST :public BaseAST {
public:
    unique_ptr<AddExpAST> addExp = nullptr;
    void accept(Visitor &visitor) override;
};

class AddExpAST : public BaseAST {
public:
    unique_ptr<AddExpAST> addExp;
    unique_ptr<MulExpAST> mulExp;
    AOP op;
    void accept(Visitor &visitor) override;
};

class MulExpAST :public BaseAST {
public:
    unique_ptr<UnaryExpAST> unaryExp;
    unique_ptr<MulExpAST> mulExp;
    MOP op;
    void accept(Visitor &visitor) override;
};

class UnaryExpAST :public BaseAST {
public:
    unique_ptr<PrimaryExpAST> primaryExp;
    unique_ptr<CallAST> call;
    unique_ptr<UnaryExpAST> unaryExp;
    UOP op;
    void accept(Visitor &visitor) override;
};

class PrimaryExpAST:public BaseAST {
public:
    unique_ptr<ExpAST> exp;
    unique_ptr<LValAST>lval;
    unique_ptr<NumberAST> number;
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
    unique_ptr<ExpArraysAST> expArrays;
    void accept(Visitor &visitor) override;
};

class CallAST:public BaseAST {
public:
    unique_ptr<string> id;
    unique_ptr<FuncCParamListAST> funcCParamList;
    void accept(Visitor &visitor) override;
};

class FuncCParamListAST : public BaseAST {
public:
    vector<unique_ptr<ExpAST>> list;
    void accept(Visitor &visitor) override;
};

class CondAST:public BaseAST {
public:
    unique_ptr<LOrExpAST> lOrExp;
    void accept(Visitor &visitor) override;
};

class RelExpAST:public BaseAST {
public:
    unique_ptr<AddExpAST> addExp;
    unique_ptr<RelExpAST> relExp;
    ROP op;
    void accept(Visitor &visitor) override;
};

class EqExpAST:public BaseAST {
public:
    unique_ptr<RelExpAST> relExp;
    unique_ptr<EqExpAST> eqExp;
    EOP op;
    void accept(Visitor &visitor) override;
};

class LAndExpAST : public BaseAST {
public:
    // lAndExp不为空则说明有and符号，or类似
    unique_ptr<EqExpAST> eqExp;
    unique_ptr<LAndExpAST> lAndExp;
    void accept(Visitor &visitor) override;
};

class LOrExpAST:public BaseAST {
public:
    unique_ptr<LOrExpAST> lOrExp;
    unique_ptr<LAndExpAST> lAndExp;
    void accept(Visitor &visitor) override;
};

class ConstExpAST : public BaseAST {
public:
    unique_ptr<AddExpAST> addExp;
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
//    virtual void visit(BTypeAST& ast) = 0;
//    virtual void visit(VoidTypeAST& ast) = 0;
    virtual void visit(ExpAST& ast) = 0;
    virtual void visit(AddExpAST& ast) = 0;
    virtual void visit(MulExpAST& ast) = 0;
    virtual void visit(UnaryExpAST& ast) = 0;
//    virtual void visit(UnaryOpAST& ast) = 0;
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
