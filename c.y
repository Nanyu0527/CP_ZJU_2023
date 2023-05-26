%{
    #include "AST.h"
    #include <iostream>
    BlockNode* root; 
%}

%union {
    Node *node;
    ExpNode *exp;
    StmNode *stm;
    IdentifierNode *identifier;
    BlockNode *block;
    VarDecNode *vardec;
    std::string *str;
    // std::vector<stm*> *stmlist;
    std::vector<exp*> *explist;
    std::vector<vardec*> *vardeclist;

}

%token BREAK ELSE IF RETURN WHILE FOR AND OR LE GE EQ NE SEMICOLON LBRACE RBRACE
%token COMMA COLON ASSIGN LPARENT RPARENT LBRACKET RBRACKET
%token DOT BITAND NOT BITNOT PLUS MINUS MUL DIV MOD LT GT BITXOR BITOR INTERROGATION

// %token<int> INTEGER
// %token<char> CHAR 
// %token<double> REAL
// %token<std::string> STRING IDENTIFER


%token<iVal> INTEGER IDENTIFIER
// %token<sVal> IDENTIFIER 
%token<dVal> REAL
%token<cVal> CHAR
%token<sVal> STRING


%type <identifier> identifier
%type <exp> exp constant
%type <stm> stm vardec fundec
%type <explist> call_args
// %type <stmlist> stmlist
%type <vardeclist> fun_args
%type <block> program block stmlist

%%
program:
stmlist{
    root = $1;
};
stmlist:
stm{$$ = new BlockNode();}
|stmlist stm;

stm:
fundec 
| vardec SEMICOLON
| exp SEMICOLON{$$ = new ExpStmNode(*$1);}
| RETURN SEMICOLON{$$ = new ReturnNULLStmNode();}
| RETURN exp SEMICOLON{$$ = new ReturnStmNode();}
| BREAK SEMICOLON{$$ = new BreakStmNode();}
| IF LPARENT exp RPARENT block {$$ = IfStmNode(*$3,*$5);}
| IF LPARENT exp RPARENT block ELSE block {$$ = new IfElseStmNode(*$3,*$5,*$7);}
| WHILE LPARENT exp RPARENT block {$$ = new WhileStmNode(*$3,*$5);}
| FOR LPARENT exp RPARENT block {$$ = new ForStmNode(*$3,*$5);};


block:
LBRACE stmlist RBRACE{$$ = $2;}
| LBRACE RBRACE{$$ = new BlockNode();};

vardec:
identifier identifier{$$ = new VarDecNode(*$1,*$2);}
| identifier identifier ASSIGN exp{$$ = new VarDecNode(*$1,*$2,$4);}
| identifier identifier  LBRACKET  INTEGER  RBRACKET {$$ = new VarDecNode(*$1,*$2,$4);};

fundec:
identifier identifier LPARENT fun_args RPARENT block{
    $$ = new FunDecNode(*$1, *$2, *$4, *$6);
};

fun_args:
 {$$ = new std::vector<VarDecNode*>();}
| fun_args COMMA vardec{$1 -> push_back($$3);}
| vardec{
    $$ = new std::vector<VarDecNode*>();
    $$ -> push_back($$1);
};

identifier:
IDENTIFIER {$$ = new IdentifierNode(*$1);};

constant:
 INTEGER {
    $$ = new IntNode(*$1);
}
| REAL {
    $$ = new DoubleNode(*$1);
}
|CHAR {
    $$ = new CharNode(*$1);
}
|STRING {
    $$ = new StringNode(*$1);
};

call_args:
    {
        $$ = new std::vector<ExpressionNode*>();
    }
    | exp {
        $$ = new std::vector<ExpressionNode*>();
        $$->push_back($1);
    }
    | call_args COMMA exp {
        $1->push_back($3);
    };

exp:
identifier ASSIGN exp{$$ = new AssignNode(*$1,*$3);}
| identifier '(' call_args ')' {$$ = new FunCallNode(*$1,*$3);}
| exp PLUS exp {$$ = new BinOpNode(1,*$1,*$3);}
| exp MINUS exp {$$ = new BinOpNode(2,*$1,*$3);}
| exp MUL exp {$$ = new BinOpNode(3,*$1,*$3);}
| exp DIV exp {$$ = new BinOpNode(4,*$1,*$3);}
| exp AND exp {$$ = new BinOpNode(5,*$1,*$3);}
| exp OR exp {$$ = new BinOpNode(6,*$1,*$3);}
| exp LE exp {$$ = new BinOpNode(7,*$1,*$3);}
| exp GE exp {$$ = new BinOpNode(8,*$1,*$3);}
| exp EQ exp {$$ = new BinOpNode(9,*$1,*$3);}
| exp NE exp {$$ = new BinOpNode(10,*$1,*$3);}
| exp LT exp {$$ = new BinOpNode(11,*$1,*$3);}
| exp GT exp {$$ = new BinOpNode(12,*$1,*$3);}
| identifier  LBRACKET  exp  RBRACKET  {$$ = new ArrayEleNode(*$1,*$3);}
| identifier  LBRACKET  exp  RBRACKET  ASSIGN exp {$$ = new ArrayAssNode(*$1,*$3,*$6);}
| identifier { $$ = $1 ;}
| MUL identifier {$$ = getAddrNode(*$2);}
| MUL identifier LBRACKET exp RBRACKET {$$ = getArrayAddrNode(*$2,*$4);}
| constant
| LPARENT exp RPARENT{$$ = $2}

%%
void yyerror(char *str){
    fprintf(stderr,"error:%s\n",str);
}    

int yywrap(){
    return 1;
}
int main(){
    yyparse();
}