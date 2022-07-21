#include <iostream>
#include <memory>
#include "ast.h"

using namespace std;
class Node {
public:
    unique_ptr<string> s;
};
int main() {
    for (int i = 0; i < 10000; i++) {
        Node* n = new Node();
        string* s = new string("1234");
        if (n->s != nullptr) cout << 1 <<endl;
    }
}
//int main() {
//    BaseAST* returnAST = new ReturnStmtAST();
//    auto stmt = new StmtAST();
//    stmt->returnStmt = unique_ptr<ReturnStmtAST>(returnAST);
//    stmt->sType = RETURN;
//    BlockItemListAST* blockItemList = new BlockItemListAST();
//    blockItemList->list.push_back(unique_ptr<BaseAST>(stmt));
//    BlockAST* blockAst = new BlockAST();
//    blockAst->blockItemList = unique_ptr<BaseAST>(blockItemList);
//    FuncDefAST* funcDefAst = new FuncDefAST();
//    funcDefAst->blockAst = unique_ptr<BaseAST>(blockAst);
//    FuncTypeAST* funcTypeAst = new FuncTypeAST();
//    funcTypeAst->voidType = unique_ptr<BaseAST>(new VoidTypeAST());
//    funcDefAst->funcType = unique_ptr<BaseAST>(funcTypeAst);
//    funcDefAst->funcFParamList = nullptr;
//    funcDefAst->id = std::make_unique<string>("main");
//    DeclDefAST* declDefAst = new DeclDefAST();
//    declDefAst->funcDef = unique_ptr<BaseAST>(funcDefAst);
//    CompUnitAST* compUnitAst = new CompUnitAST();
//    compUnitAst->declDefList.push_back(unique_ptr<BaseAST>(declDefAst));
//    compUnitAst->accept(printer);
//}
