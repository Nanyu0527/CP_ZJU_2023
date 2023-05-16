
%{
#incldue<stdio.h>
#include"y.tab.h"




%}

NUM  [1-9]+[0-9]*|0
ALPHA [a-zA-Z_]
WORD {ALPHA}+[1-9a-zA-Z_]*
void remove_comments()
void increase();
int col;
%%
"if" { yylval.token = IF  return IF;}
"else" {yylval.token = ELSE return ELSE}
"while" {yylval.token = WHILE return WHILE;}
"break" {yylval.token = BREAK return BREAK;}
"continue" {yylval.token = CONTINUE return CONTINUE;}
"return" {yylval.token = RETURN return RETURN;}

"//"(.)* {}
"/*" {remove_comments(); }

{NUM} {yylval.string = new std::string(yytext,yyleng); return NUM;}

[0-9]+\.[0-9]+    { yylval.string = new std::string(yytext,yyleng); return FLOAT; }
[0-9]+\.[0-9]+e[+-]?[0-9]+   { yylval.string = new std::string(yytext,yyleng); return FLOAT; }

"+" {increase();yylval.token = PLUS;return PLUS;}
"-" {increase();yylval.token = MINUS;return MINUS;}
"*" {increase();yylval.token = MUL;return MUL;}
"/" {increase();yylval.token = DIV;return DIV;}
"=" {increase();yylval.token = ASSIGN;return ASSIGN;}
"&&" {increase();yylval.token = AND;return AND;}
"||" {increase();yylval.token = OR;return OR;}
"<=" {increase();yylval.token = LEQ;return LEQ;}
">=" {increase();yylval.token = GEQ;return GEQ;}
"==" {increase();yylval.token = EQU;return EQU;}
"!=" {increase();yylval.token = NEQ;return NEQ;}
";" {increase();yylval.token = ';';return ';';}
"," {increase();yylval.token = ',';return ',';}
":" {increase();yylval.token = ':';return ':';}
"(" {increase();yylval.token = '(';return '(';}
")" {increase();yylval.token = ')';return ')';}
"{" {increase();yylval.token = '{';return '{';}
"}" {increase();yylval.token = '}';return '}';}
"[" {increase();yylval.token = '[';return '[';}
"]" {increase();yylval.token = ']';return ']';}
"." {increase();yylval.token = '.';return '.';}
"&" {increase();yylval.token = '&';return '&';}
"!" {increase();yylval.token = '!';return '!';}
"~" {increase();yylval.token = '~';return '~';}
"%" {increase();yylval.token = '%';return '%';}
"<" {increase();yylval.token = LT;return LT;}
">" {increase();yylval.token = GT;return GT;}
"^" {increase();yylval.token = '^';return '^';}
"|" {increase();yylval.token = '|';return '|';}
"?" {increase();yylval.token = '?';return '?';}

[\t\v\n\f] {increase();}
. {printf("unknown token : %s\n ",yytext);}

%%

void remove_comments(){
    char c,cp=0;
    while(std::cin>>c){
        if(c == '/'&&cp == '*') break;
        cp = c;
    }
    col = 0;
    if(!(c == '/'&&cp == '*')){
        std::cout<<"comment error"<<std::endl;
    }
}
void increase(){
    int count = 0;
    for(int i=0;yytext[i]!='\0';i++){
        if(yytext[i] == '\t') col+=4;
        else if(yytext[i] == '\n') col=0;
        else col++;
    }
}