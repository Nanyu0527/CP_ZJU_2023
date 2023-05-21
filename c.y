%{
    #include "AST.h"
    #include <iostream>
    BlockNode* root; 
}%

%union {
    Node *node;
    ExpNode *exp;
    StmNode *stm;
    IdentifierNode *indentifier;
    BlockNode *block;
    VarDecNode *vardec;
    std::string *str;
    std::vector<exp*> explist;
    std::vector<vardec*> vardeclist;

}

%token BREAK ELSE IF RETURN WHILE AND OR LE GE EQ NE SEMICOLON LBRACE RBRACE
%token COMMA COLON ASSIGN LPARENT RPARENT LBRACKET RBRACKET
%token DOT BITAND NOT BITNOT PLUS SUB MUL DIV MOD LT GT BITXOR BITOR INTERROGATION

%token<int> INTEGER
%token<char> CHAR 
%token<double> REAL
%token<std::string> STRING IDENTIFER

%type <indentifier*>indentifier
%type <exp> exp 
%type <stm> stm


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
| vardec ';'
| exp ';'{$$ = new ExpStmNode(*$1);}
| RETURN ';'{$$ = new ReturnNULLStmNode();}
| RETURN ex ';'{$$ = new ReturnStmNode();}
| BREAK ';'{$$ = new BreakStmNode();}
| IF '('exp')'block {$$ = IfStmNode($3,$5);}
| IF '(' exp ')'block ELSE block {$$ = new IfElseStmNode($3,$5,$7);}
| WHILE '(' exp ')' block {$$ = new WhileStmNode($3,$5);};

block:
'{'stmlist'}'{$$ = $2;}
| '{' '}'{$$ = new BlockNode();};

vardec:
indentifier indentifier{$$ = new VarDecNode(*$1,*$2);}
| indentifier indentifier '=' exp{$$ = new VarDecNode(*$1,*$2,$4);}
| indentifier indentifier '[' INTEGER ']'{$$ = new VarDecNode(*$1,*$2,$4);};

fundec:
indentifier indentifier '(' fun_args ')'block{
    $$ = new FunDecNode(*$1, *$2, *$4, *$6);
};

fun_args:
 {$$ = new std::vector<VarDecNode*>();}
| fun_args ',' vardec{$1 -> push_back($$3);}
| vardec{
    $$ = new std::vector<VarDecNode*>();
    $$ -> push_back($$1);
};

indentifier:
IDENTIFER {$$ = new IdentifierNode($1);};

INTEGER {
    $$ = new IntNode(*$1);
};
REAL {
    $$ = new DoubleNode(*$1);
};
CHAR {
    $$ = new CharNode(*$1);
};
STRING {
    $$ = new StringNode(*$1);
};


exp:
indentifier '=' exp{$$ = new AssignNode(*$1,*$3);}

| exp PLUS exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp MINUS exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp MUL exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp DIV exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp AND exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp OR exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp LE exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp GE exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp EQ exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp NE exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp LT exp {$$ = new BinOpNode($2,*$1,*$3);}
| exp GT exp {$$ = new BinOpNode($2,*$1,*$3);};
