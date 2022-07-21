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
class BTypeAST;
class ConstDefListAST;
class ConstDefAST;
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
    unique_ptr<BaseAST> id;
    unique_ptr<BaseAST> expArrays = nullptr;
    void accept(Visitor &visitor) override;
};

class ExpArraysAST : public BaseAST {
public:
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

class ExpAST :public BaseAST {
public:
    unique_ptr<BaseAST> addExp = nullptr;
    void accept(Visitor &visitor) override;
};

class AddExpAST : public BaseAST {
public:
    unique_ptr<BaseAST> addExp;
    unique_ptr<BaseAST> mulExp;
    void accept(Visitor &visitor) override;
};

class MulExpAST :public BaseAST {
public:
    unique_ptr<BaseAST> unaryExp;
    unique_ptr<BaseAST> mulExp;
    void accept(Visitor &visitor) override;
};

class UnaryExpAST :public BaseAST {
public:
    unique_ptr<BaseAST> primaryExp;
    unique_ptr<BaseAST> call;
    unique_ptr<BaseAST> unaryExp;
    UOP uop;
    void accept(Visitor &visitor) override;
};

class PrimaryExpAST:public BaseAST {
public:
    unique_ptr<BaseAST> exp, lval;
    bool isInt;
    int intval;
    float floatval;
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
    unique_ptr<BaseAST> funcCParamList;
    void accept(Visitor &visitor) override;
};
class FuncCParamListAST : public BaseAST {
public:
    vector<unique_ptr<BaseAST>> list;
    void accept(Visitor &visitor) override;
};

class Visitor {
public:
    virtual void visit(CompUnitAST& ast) = 0;
    virtual void visit(DeclDefAST& ast) = 0;
    virtual void visit(FuncDefAST& ast) = 0;
    virtual void visit(FuncFParamListAST& ast) = 0;
    virtual void visit(BlockAST& ast) = 0;
    virtual void visit(BlockItemListAST& ast) = 0;
    virtual void visit(BlockItemAST& ast) = 0;
    virtual void visit(StmtAST& ast) = 0;
    virtual void visit(ReturnStmtAST& ast) = 0;
    virtual void visit(BTypeAST& ast) = 0;
    virtual void visit(VoidTypeAST& ast) = 0;
    virtual void visit(ExpAST& ast) = 0;
    virtual void visit(AddExpAST& ast) = 0;
    virtual void visit(MulExpAST& ast) = 0;
    virtual void visit(UnaryExpAST& ast) = 0;
    virtual void visit(PrimaryExpAST& ast) = 0;
    virtual void visit(CallAST& ast) = 0;
    virtual void visit(FuncCParamListAST& ast) = 0;
};

class Printer: public Visitor {
public:
    int depth = 0;
    void visit(CompUnitAST &ast) override;
    void visit(DeclDefAST &ast) override;
    void visit(FuncDefAST &ast) override;
    void visit(FuncFParamListAST &ast) override;
    void visit(BlockAST &ast) override;
    void visit(BlockItemListAST &ast) override;
    void visit(BlockItemAST &ast) override;
    void visit(StmtAST &ast) override;
    void visit(ReturnStmtAST &ast) override;
    void visit(BTypeAST &ast) override;
    void visit(VoidTypeAST &ast) override;

    void visit(ExpAST &ast) override;

    void visit(AddExpAST &ast) override;

    void visit(MulExpAST &ast) override;

    void visit(UnaryExpAST &ast) override;

    void visit(PrimaryExpAST &ast) override;

    void visit(CallAST &ast) override;

    void visit(FuncCParamListAST &ast) override;
};
#endif //TEST_AST_H
