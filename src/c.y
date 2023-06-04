%{	#include "AST.h"
	#include<string>
	#include<iostream>
    #include<stdio.h>
	#include<vector>
    #include <cstdio>
    #include <cstdlib>
	BlockNode* root; 
    extern int yylex();
    void yyerror(const char *s) { 
        std::printf("Error: %s", s);
        std::exit(0);
    }
%}
%union {
	int iVal;
    std::string *sVal;
    double dVal;
    char cVal;
	Node *node;
	IdentifierNode *identifier;
	BlockNode *block;
	ExpNode *exp;
    StmNode *stm;
    int token;
	VarDecNode *vardec;
    vector<ExpNode*> *explist;
    vector<VarDecNode*> *vardeclist;
}
%token<sVal> CHAR;
%token<iVal> INTEGER;
%token<sVal> STRING;
%token<dVal> REAL;
%token<sVal> IDENTIFER;

%token IF ELSE BREAK RETURN WHILE
%token<token> AND OR LT GT LE GE EQ NE MINUS PLUS MUL DIV MOD
%token SEMICOLON LBRACE RBRACE COMMA COLON ASSIGN LPARENT RPARENT LBRACKET RBRACKET DOT INTERROGATION
%token BITAND BITNOT BITOR BITXOR
%token NOT

%left OR
%left AND
%left LT GT LE GE EQ NE
%left PLUS MINUS
%left MUL DIV
%right INTERROGATION
%left LPARENT RPARENT LBRACKET RBRACKET

%type <identifier> identifier
%type <exp> const_value exp
%type <stm> stm var_decl func_decl
%type <vardeclist> func_decl_args
%type <explist> call_args
%type <block> program stmlist block

%start program

%%
program:
stmlist{ root = $1;}
;
stmlist:
stm{ $$ = new BlockNode();$$->stmList.push_back($<stm>1);}
|stmlist stm{$$->stmList.push_back($<stm>2);}
;
stm:
var_decl SEMICOLON
|func_decl
|exp SEMICOLON{$$ = new ExpStmNode($1);}
|RETURN SEMICOLON{$$ = new ReturnNullStmNode();}
|RETURN exp SEMICOLON{$$ = new ReturnStmNode($2);}
|BREAK SEMICOLON{$$ = new BreakStmNode();}
|IF LPARENT exp RPARENT block{$$ = new IfStmNode($3,$5);}
|IF LPARENT exp RPARENT block ELSE block{$$ = new IfElseStmNode($3,$5,$7);}
|WHILE LPARENT exp RPARENT block{$$ = new WhileStmNode($3,$5);}
;
block:
LBRACE stmlist RBRACE { $$ = $2;}
|LBRACE RBRACE { $$ = new BlockNode(); }
;
var_decl:
identifier identifier{$$ = new VarDecNode($1,$2);}
|identifier identifier ASSIGN exp{$$ = new VarDecNode{$1,$2,$4}; }
|identifier identifier LBRACKET INTEGER RBRACKET {$$ =new VarDecNode{$1,$2,$4};}
;
func_decl:
identifier identifier LPARENT func_decl_args RPARENT block {$$ = new FunDecNode(&*$1, &*$2, *$4, &*$6);}
;
func_decl_args:
{ $$ = new std::vector<VarDecNode*>();}
|var_decl{$$ = new std::vector<VarDecNode*>();$$->push_back($<vardec>1);}
|func_decl_args COMMA var_decl {$1->push_back($<vardec>3);}
;
identifier:
IDENTIFER{$$ = new IdentifierNode($1);}
;
const_value:
INTEGER{$$ = new IntNode($1);}
|CHAR {$$ = new CharNode(*$1);}
|STRING {$$ = new StringNode(*$1);}
|REAL {$$ = new DoubleNode($1);}
;
call_args:
{$$ = new std::vector<ExpNode*>();}
|exp{$$ = new std::vector<ExpNode*>();$$->push_back($1);}
|call_args COMMA exp {$1->push_back($3);}
;
exp:
identifier ASSIGN exp{$$ = new AssignNode($<identifier>1, $3);}
|identifier LPARENT call_args RPARENT {$$ = new FunCallNode($1, *$3);}
|identifier {$<identifier>$ = $1;}
|BITAND identifier {$$ = new getAddrNode($2);}
|BITAND identifier LBRACKET exp RBRACKET {$$ = new getArrayAddrNode($2, $4);}
|exp MUL exp {$$ = new BinOpNode($2, $1, $3);}
|exp DIV exp {$$ = new BinOpNode($2, $1, $3);}
|exp PLUS exp {$$ = new BinOpNode($2, $1, $3);}
|exp MINUS exp {$$ = new BinOpNode($2, $1, $3);}
|exp AND exp {$$ = new BinOpNode($2, $1, $3);}
|exp OR exp {$$ = new BinOpNode($2, $1, $3);}
|exp LT exp {$$ = new BinOpNode($2,$1, $3);}
|exp GT exp {$$ = new BinOpNode($2, $1, $3);}
|exp EQ exp {$$ = new BinOpNode($2, $1, $3);}
|exp NE exp {$$ = new BinOpNode($2, $1,$3);}
|exp LE exp {$$ = new BinOpNode($2, $1, $3);}
|exp GE exp {$$ = new BinOpNode($2, $1, $3);}
|LPARENT exp RPARENT {$$ = $2;}
|identifier LBRACKET exp RBRACKET { $$ = new ArrayEleNode($1, $3);}
|identifier LBRACKET exp RBRACKET ASSIGN exp { $$ = new ArrayAssNode($1, $3, $6);}
|const_value
;
%%
// void yyerror(char *str){
//     fprintf(stderr,"error:%s\n",str);
// }    

// int yywrap(){
//     return 1;
// }
// int main(){
//     yyparse();
// }