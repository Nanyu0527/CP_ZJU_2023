letter          [A-Za-z_]
digit           [0-9]
letter_digit    [A-Za-z_0-9] 
line            \n
%{
#include<stdio.h>
#include<string>
#include<iostream>
#include"AST.h"
#include"lab_yacc.hpp"
char SecondChar(char ch);
#define TOKEN(t) (yylval.token = t)
%}

%%


"break"         { return BREAK;    }
"else"          { return ELSE;     }
"if"            { return IF;       }
"return"        { return RETURN;   }
"while"         { return WHILE;    }

"&&"            { return TOKEN(AND); }
"||"            { return TOKEN(OR); }
"<="            { return TOKEN(LE); }
">="            { return TOKEN(GE); }
"=="            { return TOKEN(EQ); }
"!="            { return TOKEN(NE); }
";"             { return SEMICOLON; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
","             { return COMMA; }
":"             { return COLON; }
"="             { return ASSIGN; }
"("             { return LPARENT; }
")"             { return RPARENT; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
"."             { return DOT; }
"&"             { return BITAND; }
"!"             { return NOT; }
"~"             { return BITNOT; }
"-"             { return TOKEN(MINUS); }
"+"             { return TOKEN(PLUS); }
"*"             { return TOKEN(MUL); }
"/"             { return TOKEN(DIV); }
"%"             { return TOKEN(MOD); }
"<"             { return TOKEN(LT); }
">"             { return TOKEN(GT); }
"^"             { return TOKEN(BITXOR); }
"|"             { return TOKEN(BITOR); }
"?"             { return INTERROGATION; }

\/\/.*\n					{;}
						
[\t\v\r\n\f\a\b]			{;}

{digit}+\.{digit}+				{ 
								double dtmp;
								sscanf(yytext, "%lf", &dtmp);
								yylval.dVal = dtmp;
								return REAL; 
							}
{digit}+						{
								int itmp;
								sscanf(yytext, "%d", &itmp);
								yylval.iVal = itmp; 
								return INTEGER; 
							}
\'.\'|\'\\.\'         		{	yylval.sVal = new std::string(yytext, yyleng);
								return CHAR;	}			
\"(\\.|[^"\\])*\"      		{	
								yylval.sVal = new std::string(yytext, yyleng);
								return STRING;
							}
{letter}{letter_digit}*	{
								yylval.sVal = new std::string(yytext, yyleng);
								return IDENTIFER;
							}								
.               			{ if(yytext[0]!=' ') printf("unknown token : %s\n", yytext); }
%%
int yywrap(void)
{
    return 1;
}
char SecondChar(char ch){
	switch(ch){
	case 'a': return '\a';
	case 'b': return '\b';
	case 'f': return '\f';
	case 'n': return '\n';
	case 'r': return '\r';
	case 't': return '\t';
	case 'v': return '\v';
	case '\\': return '\\';
	case '\'': return '\'';
	case '\"': return '\"';
	default:
		if ('0'<=ch && ch<='9')
			return (char)(ch-'0');
		else
			return ch;
	}
}
