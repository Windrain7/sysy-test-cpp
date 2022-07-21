%define parse.error verbose
%locations
%{
    #include "ast.h"
    #include "define.h"
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
%type <ast> Program CompUnit DeclDef ConstDecl BType ConstDefList ConstDef Term Arrays ConstInitVal ConstInitValList VarDecl VarDefList VarDef InitVal InitValList FuncDef VoidType FuncFParamList FuncFParam ExpArrays Block BlockItemList BlockItem Stmt ReturnStmt SelectStmt IterationStmt Exp Cond LVal PrimaryExp Number UnaryExp Call UnaryOp FuncCParamListAST MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp
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
DeclDef: ConstDecl {
			auto t =  new DeclDefAST();
			t->constDecl = unique_ptr<BaseAST>($1);
			$$ = t;
		}
		|VarDecl {
			auto t =  new DeclDefAST();
			t->varDecl = unique_ptr<BaseAST>($1);
			$$ = t;
		}
		|FuncDef {
			auto t =  new DeclDefAST();
			t->funcDef = unique_ptr<BaseAST>($1);
			$$ = t;
		}
        ;

// 常量声明
ConstDecl:	CONST BType ConstDefList SEMICOLON {
				auto t =  new ConstDeclAST();
				t->bType = unique_ptr<BaseAST>($2);
				t->constDefListAST = unique_ptr<BaseAST>($3);
				$$ = t;
			}
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
ConstDefList:ConstDef {
				auto t = new ConstDefListAST();
				t->list.push_back(unique_ptr<BaseAST>($1));
				$$ = t;
			}				
			|ConstDefList COMMA ConstDef {
				auto t = (ConstDefListAST*)$1;
           		t->list.push_back(unique_ptr<BaseAST>($3));
           		$$ = t;
			}
			;

// 常量定义
ConstDef:	Term ASSIGN ConstInitVal {
				auto t = new ConstDefAST();
				t->term = unique_ptr<BaseAST>($1);
				t->constInitVal = unique_ptr<BaseAST>($3);
				$$ = t;
			}
		  	;

// 元素
Term:ID {
		auto t = new TermAST();
		t->id = unique_ptr<string>($1);
		$$ = t;
	}
    |ID Arrays {
		auto t = new TermAST();
		t->id = unique_ptr<string>($1);
		t->arrays = unique_ptr<BaseAST>($2);
		$$ = t;
	}

// 下标为常量的数组
Arrays: LB ConstExp RB {
			auto t = new ArraysAST();
			t->list.push_back(unique_ptr<BaseAST>($2));
			$$ = t;
		}
        |Arrays LB ConstExp RB {
			auto t = (ArraysAST*) $1;
			t->list.push_back(unique_ptr<BaseAST>($3));
			$$ = t;
		}
		;

// 常量初始值
ConstInitVal:ConstExp {
				auto t = new ConstInitValAST();
				t->constExp = unique_ptr<BaseAST>($1);
				$$ = t;
			}			
			|LC RC {
				$$ = new ConstInitValAST();
			}				
			|LC ConstInitValList RC {
				auto t = new ConstInitValAST();
				t->constExp = unique_ptr<BaseAST>($2);
				$$ = t;
			}
			;

// 常量初始值列表
ConstInitValList:ConstInitValList COMMA ConstInitVal {
					auto t = (ConstInitValListAST*) $1;
					t->list.push_back(unique_ptr<BaseAST>($3));
					$$ = t;
				}
				|ConstInitVal {
					auto t = new ConstInitValListAST();
					t->list.push_back(unique_ptr<BaseAST>($1));
					$$ = t;
				}
				;

// 变量声明
VarDecl:	BType VarDefList SEMICOLON {
				auto t = (VarDeclAST*) $1;
				t->bType = unique_ptr<BaseAST>($1);
				t->varDefList = unique_ptr<BaseAST>($2);
				$$ = t;
			}
			;

// 变量定义列表
VarDefList:	 VarDef	{
				auto t = new VarDefListAST();
				t->list.push_back(unique_ptr<BaseAST>($1));
				$$ = t;
			}					
			|VarDefList COMMA VarDef {
				auto t = (VarDefListAST*) $1;
				t->list.push_back(unique_ptr<BaseAST>($3));
				$$ = t;
			}
			;

// 变量定义
VarDef:	 Term {
			auto t = new VarDefAST();
			t->term = unique_ptr<BaseAST>($1);
			$$ = t;
		}				
      	|Term ASSIGN InitVal {
			auto t = new VarDefAST();
			t->term = unique_ptr<BaseAST>($1);
			t->initVal = unique_ptr<BaseAST>($3);
			$$ = t;
		}

// 变量初值
InitVal: Exp {
			auto t = new InitValAST();
			t->exp = unique_ptr<BaseAST>($1);
			$$ = t;
		}		
		|LC RC	{
			$$ = new InitValAST();
		}	
		|LC InitValList RC {
			auto t = new InitValAST();
			t->initValList = unique_ptr<BaseAST>($2);
			$$ = t;
		}	
		;

// 变量列表
InitValList:InitValList COMMA InitVal {
			auto t = (InitValListAST*) $1;
			t->list.push_back(unique_ptr<BaseAST>($3));
			$$ = t;
		}
		|InitVal {
			auto t = new InitValListAST();
			t->list.push_back(unique_ptr<BaseAST>($1));
			$$ = t;
		}
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
FuncFParam:	 BType ID {
				auto t = new FuncFParamAST();
				t->bType = unique_ptr<BaseAST>($1);
				t->id = unique_ptr<string>($2);
				t->isArray = false;
				$$ = t;
			}
			|BType ID LB RB	{
				auto t = new FuncFParamAST();
				t->bType = unique_ptr<BaseAST>($1);
				t->id = unique_ptr<string>($2);
				t->isArray = true;
				$$ = t;
			}
			|BType ID LB RB ExpArrays {
				auto t = new FuncFParamAST();
				t->bType = unique_ptr<BaseAST>($1);
				t->id = unique_ptr<string>($2);
				t->isArray = true;
				t->expArrays = unique_ptr<BaseAST>($5);
				$$ = t;
			}	
			;

// 各维长度为Exp的数组，需要注意如果是作为函数参数则实际要多出一维
// 现在规定ExpArrays不为空，FuncFParam与Lval做出相应修改
ExpArrays:LB Exp RB {
			auto t = new ExpArraysAST();
			t->list.push_back(unique_ptr<BaseAST>($2));
			$$ = t;
		}
      	|ExpArrays LB Exp RB {
			auto t = (ExpArraysAST*) $1;
			t->list.push_back(unique_ptr<BaseAST>($3));
			$$ = t;
		}
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
SelectStmt:	IF LP Cond RP Stmt %prec LOWER_THEN_ELSE {
				auto t = new SelectStmtAST();
				t->cond = unique_ptr<BaseAST>($3);
				t->ifStmt = unique_ptr<BaseAST>($5);
				$$ = t;
			}
			|IF LP Cond RP Stmt ELSE Stmt {
				auto t = new SelectStmtAST();
				t->cond = unique_ptr<BaseAST>($3);
				t->ifStmt = unique_ptr<BaseAST>($5);
				t->elseStmt = unique_ptr<BaseAST>($7);
				$$ = t;
			}   
			;

//循环语句
IterationStmt:  WHILE LP Cond RP Stmt {
					auto t = new IterationStmtAST();
					t->cond = unique_ptr<BaseAST>($3);
					t->stmt = unique_ptr<BaseAST>($5);
					$$ = t;
				}
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
Exp:	AddExp {
			auto t = new ExpAST();
			t->addExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}
		;

// 条件表达式
Cond:	LOrExp {
			auto t = new CondAST();
			t->lOrExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}
		;

// 左值表达式
LVal:	ID {
			auto t = new LValAST();
			t->id = unique_ptr<string>($1);
			$$ = t;
		}
		|ID ExpArrays {
			auto t = new LValAST();
			t->id = unique_ptr<string>($1);
			t->expArrays = unique_ptr<BaseAST>($2);
			$$ = t;
		}
		;

// 基本表达式
PrimaryExp:	 LP Exp RP {
				auto t = new PrimaryExpAST();
				t->exp = unique_ptr<BaseAST>($2);
				$$ = t;
			}
			|LVal {
				auto t = new PrimaryExpAST();
				t->lval = unique_ptr<BaseAST>($1);
				$$ = t;
			}	
			|Number	{
				auto t = new PrimaryExpAST();
				t->number = unique_ptr<BaseAST>($1);
				$$ = t;
			}		
			;

// 数值
Number:	 INT {
			auto t = new NumberAST();
			t->isInt = true;
			t->intval = $1;
			$$ = t;
		}		
   		|FLOAT {
			auto t = new NumberAST();
			t->isInt = false;
			t->intval = $1;
			$$ = t;
		}		
   		;

// 一元表达式
UnaryExp:	 PrimaryExp	{
				auto t = new UnaryExpAST();
				t->primaryExp = unique_ptr<BaseAST>($1);
				$$ = t;
			}					
			|Call {
				auto t = new UnaryExpAST();
				t->call = unique_ptr<BaseAST>($1);
				$$ = t;
			}
			|UnaryOp UnaryExp {
				auto t = new UnaryExpAST();
				t->unaryOp = unique_ptr<BaseAST>($1);
				t->unaryExp = unique_ptr<BaseAST>($2);
				$$ = t;
			}		
			;

//函数调用
Call:ID LP RP {
		auto t = new CallAST();
		t->id = unique_ptr<string>($1);
		$$ = t;
	}
	 |ID LP FuncCParamListAST RP {
		auto t = new CallAST();
		t->id = unique_ptr<string>($1);
		t->funcCParamList = unique_ptr<BaseAST>($3);
		$$ = t;
	 }
	 ;	

// 单目运算符,这里可能与优先级相关，不删除该非终结符
UnaryOp: ADD {
			auto t = new UnaryOpAST();
			t->op = UOP_ADD;
			$$ = t;
		}	
    	|MINUS {
			auto t = new UnaryOpAST();
			t->op = UOP_MINUS;
			$$ = t;
		}
    	|NOT {
			auto t = new UnaryOpAST();
			t->op = UOP_NOT;
			$$ = t;
		}	
		;

// 函数实参表
FuncCParamListAST: Exp {
				auto t = new FuncCParamListAST();
				t->list.push_back(unique_ptr<BaseAST>($1));
				$$ = t;
			}
			|FuncCParamListAST COMMA Exp {
				auto t = (FuncCParamListAST*) $1;
				t->list.push_back(unique_ptr<BaseAST>($3));
				$$ = t;
			}
			;
				
//乘除模表达式
MulExp:	 UnaryExp {
			auto t = new MulExpAST();
			t->unaryExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}		
		|MulExp MUL UnaryExp {
			auto t = new MulExpAST();
			t->mulExp = unique_ptr<BaseAST>($1);
			t->op = MOP_MUL;
			t->unaryExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}	
		|MulExp DIV UnaryExp {
			auto t = new MulExpAST();
			t->mulExp = unique_ptr<BaseAST>($1);
			t->op = MOP_DIV;
			t->unaryExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}	
		|MulExp MOD UnaryExp {
			auto t = new MulExpAST();
			t->mulExp = unique_ptr<BaseAST>($1);
			t->op = MOP_MOD;
			t->unaryExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}	
		;

// 加减表达式
AddExp:	 MulExp	{
			auto t = new AddExpAST();
			t->mulExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}			
		|AddExp ADD MulExp {
			auto t = new AddExpAST();
			t->addExp = unique_ptr<BaseAST>($1);
			t->op = AOP_ADD;
			t->mulExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}
		|AddExp MINUS MulExp {
			auto t = new AddExpAST();
			t->addExp = unique_ptr<BaseAST>($1);
			t->op = AOP_MINUS;
			t->mulExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}
		;

// 关系表达式
RelExp:	 AddExp	{
			auto t = new RelExpAST();
			t->addExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}				
		|RelExp GTE AddExp{
			auto t = new RelExpAST();
			t->relExp = unique_ptr<BaseAST>($1);
			t->op = ROP_GTE;
			t->addExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}  //分析关系运算符号自身值保存在$2中
		|RelExp LTE AddExp{
			auto t = new RelExpAST();
			t->relExp = unique_ptr<BaseAST>($1);
			t->op = ROP_LTE;
			t->addExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}  //分析关系运算符号自身值保存在$2中
		|RelExp GT AddExp {
			auto t = new RelExpAST();
			t->relExp = unique_ptr<BaseAST>($1);
			t->op = ROP_GT;
			t->addExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}  //分析关系运算符号自身值保存在$2中
		|RelExp LT AddExp {
			auto t = new RelExpAST();
			t->relExp = unique_ptr<BaseAST>($1);
			t->op = ROP_LT;
			t->addExp = unique_ptr<BaseAST>($3);
			$$ = t;
		}  //分析关系运算符号自身值保存在$2中
		;

// 相等性表达式
EqExp:	 RelExp	{
			auto t = new EqExpAST();
			t->relExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}				
		|EqExp EQ RelExp{
			auto t = new EqExpAST();
			t->eqExp = unique_ptr<BaseAST>($1);
			t->op = EOP_EQ;
			t->relExp = unique_ptr<BaseAST>($3);
			$$ = t;
		} 	
		|EqExp NEQ RelExp{
			auto t = new EqExpAST();
			t->eqExp = unique_ptr<BaseAST>($1);
			t->op = EOP_NEQ;
			t->relExp = unique_ptr<BaseAST>($3);
			$$ = t;
		} 	
		;

// 逻辑与表达式
LAndExp: EqExp {
			auto t = new LAndExpAST();
			t->eqExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}		
		|LAndExp AND EqExp {
			auto t = new LAndExpAST();
			t->lAndExp = unique_ptr<BaseAST>($1);
			t->eqExp = unique_ptr<BaseAST>($3);
			$$ = t;
		} 	
		;

// 逻辑或表达式
LOrExp:	 LAndExp {
			auto t = new LOrExpAST();
			t->lAndExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}				
		|LOrExp OR LAndExp {
			auto t = new LOrExpAST();
			t->lOrExp = unique_ptr<BaseAST>($1);
			t->lAndExp = unique_ptr<BaseAST>($3);
			$$ = t;
		} 	
		;

// 常量表达式
ConstExp:AddExp	{
			auto t = new ConstExpAST();
			t->addExp = unique_ptr<BaseAST>($1);
			$$ = t;
		}			
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

