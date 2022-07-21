#include <iostream>
#include "ast.h"
extern unique_ptr<BaseAST> root;
extern int yyparse();
extern FILE *yyin;


int main(int argc, char **argv) {
    std::cout << "------open------" <<std::endl;
    yyin = fopen(argv[1], "r");
    std::cout << "------parse------" <<std::endl;
    yyparse();
    std::cout << "------print------" <<std::endl;
    Printer printer;
    root->accept(printer);
    std::cout << "------end------" <<std::endl;
    return 0;
}
