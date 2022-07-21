%define parse.error verbose
%locations
%{
    #include "ast.h"
    #include <memory>
    #include<stdarg.h>
    using namespace std;
    unique_ptr<BaseAST> root; /* the top level root node of our final AST */

    extern int yylineno;
    extern int yylex();
    extern void yyerror(const char *s);
%}

%union {
	BaseAST* ast;
	string* token;
	int int_val;
	float float_val;
};

//%union is not used, and %token and %type expect genuine types, not type tags
//%type 定义非终结符的语义值类型
%type <ast> Program CompUnit DeclDef ConstDecl BType ConstDefList ConstDef Arrays ConstInitVal ConstInitValList VarDecl VarDefList VarDef InitVal InitValList FuncDef FuncType VoidType FuncFParamList FuncFParam ExpArrays Block BlockItemList BlockItem Stmt ReturnStmt SelectStmt IterationStmt Exp Cond LVal PrimaryExp Number UnaryExp Call UnaryOp FuncFParams MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp
//% token 定义终结符的语义值类型
%token <int_val> INT           // 指定INT字面量的语义值是type_int，有词法分析得到的数值
%token <float_val> FLOAT       // 指定FLOAT字面量的语义值是type_float，有词法分析得到的数值
%token <token> ID            // 指定ID
%token GTE LTE GT LT EQ NEQ    // 关系运算
%token INTTYPE FLOATTYPE VOID  // 数据类型
%token CONST RETURN IF ELSE WHILE BREAK CONTINUE
%token LP RP LB RB LC RC COMMA SEMICOLON
//用bison对该文件编译时，带参数-d，生成的exp.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码
%token NOT POS NEG ASSIGN MINUS ADD MUL DIV MOD AND OR UMINUS
%token END

%left ASSIGN
%left OR AND
%left EQ NEQ
%left GTE LTE GT LT
%left ADD MINUS
%left MOD MUL DIV
%right NOT POS NEG 

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%start Program

%%
Program:CompUnit {
          root = unique_ptr<BaseAST>($1);
		}
		;

// 编译单元
CompUnit:CompUnit DeclDef {
           auto t = (CompUnitAST*) $1;
           t->declDefList.push_back(unique_ptr<BaseAST>($2));
           $$ = t;
		}
		|DeclDef {
		   auto t = new CompUnitAST();
		   t->declDefList.push_back(unique_ptr<BaseAST>($1));
		   $$ = t;
		}
		;

//声明或者函数定义
DeclDef: ConstDecl
		|VarDecl
		|FuncDef {
			auto t =  new DeclDefAST();
			t->funcDef = unique_ptr<BaseAST>($1);
			$$ = t;
		}
        ;

// 常量声明
ConstDecl:	CONST BType ConstDefList SEMICOLON
			;

// 基本类型
BType:	INTTYPE {
			auto t = new BTypeAST();
			t->isInt = true;
			$$=t;
		}
		|FLOATTYPE {
            auto t = new BTypeAST();
            t->isInt = false;
            $$=t;
        }
		;

// 常量定义列表
ConstDefList:	 ConstDef					
				|ConstDefList COMMA ConstDef 
				;

// 常量定义
ConstDef: ID Arrays ASSIGN ConstInitVal
		  ;

// 下标为常量的数组
Arrays: Arrays LB ConstExp RB
        |
		;

// 常量初始值
ConstInitVal:ConstExp			
			|LC RC				
			|LC ConstInitValList RC
			;

ConstInitValList:ConstInitValList COMMA ConstInitVal
				|ConstInitVal
				;

// 变量声明
VarDecl:	BType VarDefList SEMICOLON	
			;

// 变量定义列表
VarDefList:	 VarDef						
			|VarDef COMMA VarDefList	
			;

// 变量定义
VarDef:	 ID Arrays				
      	|ID Arrays ASSIGN InitVal

// 变量初值
InitVal: Exp			
		|LC RC			
		|LC InitValList RC
		;

// 变量列表
InitValList:InitValList COMMA InitVal
		|InitVal
		;

// 函数定义
FuncDef: BType ID LP FuncFParamList RP Block {
			auto t = new FuncDefAST();
			t->funcType = unique_ptr<BaseAST>($1);
			t->id = unique_ptr<string>($2);
			t->funcFParamList = unique_ptr<BaseAST>($4);
			t->blockAst = unique_ptr<BaseAST>($6);
            $$ = t;
		}
       	|BType ID LP RP Block {
			auto t = new FuncDefAST();
			t->funcType = unique_ptr<BaseAST>($1);
			t->id = unique_ptr<string>($2);
			t->blockAst = unique_ptr<BaseAST>($5);
			$$ = t;
		}
        |VoidType ID LP FuncFParamList RP Block {
			auto t = new FuncDefAST();
			t->funcType = unique_ptr<BaseAST>($1);
			t->id = unique_ptr<string>($2);
			t->funcFParamList = unique_ptr<BaseAST>($4);
			t->blockAst = unique_ptr<BaseAST>($6);
            $$ = t;
		}
       	|VoidType ID LP RP Block {
			auto t = new FuncDefAST();
			t->funcType = unique_ptr<BaseAST>($1);
			t->id = unique_ptr<string>($2);
			t->blockAst = unique_ptr<BaseAST>($5);
			$$ = t;
		}
		;

VoidType: VOID {
			$$ = new VoidTypeAST();
		}
		;

// 函数形参列表
FuncFParamList: FuncFParam {
				auto t = new FuncFParamListAST();
				t->list.push_back(unique_ptr<BaseAST>($1));
				$$ = t;
			}	
			|FuncFParamList COMMA FuncFParam {
				auto t = (FuncFParamListAST*) $1;
				t->list.push_back(unique_ptr<BaseAST>($3));
				$$ = t;
			}	
			;

// 函数形参
FuncFParam:	 BType ID		
			|BType ID LB RB ExpArrays	
			;

// 下标为Exp的数组
ExpArrays: 
      	|ExpArrays LB Exp RB  
      	;

// 语句块
Block:	 LC RC {
			$$ = new BlockAST();
		}
		|LC BlockItemList RC {
			auto t = new BlockAST();
			t->blockItemList = unique_ptr<BaseAST>($2);
			$$ = t;
		}	
		;

// 语句块项列表
BlockItemList:BlockItem	{
				auto t = new BlockItemListAST();
				t->list.push_back(unique_ptr<BaseAST>($1));
				$$ = t;
			}
			|BlockItemList BlockItem {
				auto t = (BlockItemListAST*) $1;
				t->list.push_back(unique_ptr<BaseAST>($2));
				$$ = t;
			}		
			;

// 语句块项
BlockItem:	 ConstDecl {
				auto t = new BlockItemAST();
				t->constDecl = unique_ptr<BaseAST>($1);
				$$ = t;
			}
			|VarDecl {
				auto t = new BlockItemAST();
				t->varDecl = unique_ptr<BaseAST>($1);
				$$ = t;
			}
			|Stmt {
				auto t = new BlockItemAST();
				t->stmt = unique_ptr<BaseAST>($1);
				$$ = t;
			}	
			;

// 语句，根据type判断是何种类型的Stmt
Stmt:	 SEMICOLON	{
			auto t = new StmtAST();
			t->sType = SEMI;
			$$ = t;
		}				
		|LVal ASSIGN Exp SEMICOLON {
			auto t = new StmtAST();
			t->sType = ASS;
			t->lVal = unique_ptr<BaseAST>($1);
			t->exp = unique_ptr<BaseAST>($3);
			$$ = t;

		}
		|Exp SEMICOLON {
			auto t = new StmtAST();
			t->sType = EXP;
			t->exp = unique_ptr<BaseAST>($1);
			$$ = t;
		}				
    	|CONTINUE SEMICOLON	{
			auto t = new StmtAST();
			t->sType = CONT;
			$$ = t;
		}	
    	|BREAK SEMICOLON {
			auto t = new StmtAST();
			t->sType = BRE;
			$$ = t;
		}	
    	|Block {
			auto t = new StmtAST();
			t->sType = BLK;
			t->block = unique_ptr<BaseAST>($1);
			$$ = t;
		}
        |ReturnStmt {
			auto t = new StmtAST();
			t->sType = RET;
			t->returnStmt = unique_ptr<BaseAST>($1);
			$$ = t;
		}
        |SelectStmt {
			auto t = new StmtAST();
			t->sType = SEL;
			t->selectStmt = unique_ptr<BaseAST>($1);
			$$ = t;
		}
        |IterationStmt {
			auto t = new StmtAST();
			t->sType = ITER;
			t->iterationStmt = unique_ptr<BaseAST>($1);
			$$ = t;
		}
		;

//选择语句
SelectStmt:	|IF LP Cond RP Stmt %prec LOWER_THEN_ELSE
			|IF LP Cond RP Stmt ELSE Stmt   
			;

//循环语句
IterationStmt:  WHILE LP Cond RP Stmt
                ;
//返回语句
ReturnStmt:	RETURN Exp SEMICOLON {
				auto t = new ReturnStmtAST();
				t->exp = unique_ptr<BaseAST>($2);
				$$ = t;
			}
            |RETURN SEMICOLON {
				$$ = new ReturnStmtAST();
			}
            ;
// 表达式
Exp:	AddExp	
		;

// 条件表达式
Cond:	LOrExp	
		;

// 左值表达式
LVal:	ID ExpArrays	
		;

// 基本表达式
PrimaryExp:	 LP Exp RP	
			|LVal		
			|Number		
			;

// 数值
Number:	 INT		
   		|FLOAT
   		;

// 一元表达式
UnaryExp:	 PrimaryExp				
			|Call
			|UnaryOp UnaryExp		
			;

//函数调用
Call:ID LP RP
	 |ID LP FuncFParams RP
	 ;	

// 单目运算符
UnaryOp: ADD	
    	|MINUS	
    	|NOT	
		;

// 函数实参表
FuncFParams: Exp	
			|FuncFParams COMMA Exp 
			;
				
//乘除模表达式
MulExp:	 UnaryExp			
		|MulExp MUL UnaryExp
		|MulExp DIV UnaryExp
		|MulExp MOD UnaryExp
		;

// 加减表达式
AddExp:	 MulExp				
		|AddExp ADD MulExp	
		|AddExp MINUS MulExp
		;

// 关系表达式
RelExp:	 AddExp				
		|RelExp GTE AddExp  //分析关系运算符号自身值保存在$2中
		|RelExp LTE AddExp  //分析关系运算符号自身值保存在$2中
		|RelExp GT AddExp  //分析关系运算符号自身值保存在$2中
		|RelExp LT AddExp  //分析关系运算符号自身值保存在$2中
		;

// 相等性表达式
EqExp:	 RelExp				
		|EqExp EQ RelExp	
		|EqExp NEQ RelExp	
		;

// 逻辑与表达式
LAndExp: EqExp				
		|LAndExp AND EqExp	
		;

// 逻辑或表达式
LOrExp:	 LAndExp		
		|LOrExp OR LAndExp
		;

// 常量表达式
ConstExp:AddExp	
		;

%%

/* int main(int argc, char *argv[]) {
	yyin = fopen(argv[1],"r");
	if (!yyin) return 0;

	// char ch;
	// while ((ch = getc(yyin)) != EOF) putchar(ch);

	yylineno = 1;
	strcpy(filename,strrchr(argv[1],'/')+1);
	yyparse();
	return 0;
} */

void yyerror(const char* fmt) {
    printf("line:%d\tcolumn:%d\n", yylloc.first_line,yylloc.first_column);
    printf("ERROR: %s\n", fmt);
}

