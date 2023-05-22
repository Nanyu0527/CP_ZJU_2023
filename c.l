%{
#include<stdio.h>
#include <string>
#include <iostream>
char SecondChar(char ch);
%}
%%
%option yylineno
/*keywords*/
"break"         { return BREAK;    }
"else"          { return ELSE;     }
"if"            { return IF;       }
"return"        { return RETURN;   }
"while"         { return WHILE;    }
"for"           { return FOR;      }
/*operations*/
"&&"            { return AND; }
"||"            { return OR; }
"<="            { return LE; }
">="            { return GE; }
"=="            { return EQ; }
"!="            { return NE; }
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
"-"             { return SUB; }
"+"             { return PLUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"%"             { return MOD; }
"<"             { return LT; }
">"             { return GT; }
"^"             { return BITXOR; }
"|"             { return BITOR; }
"?"             { return INTERROGATION; }
/*comment*/
\/\/.*\n					{;}
/*\t \n...*/							
[\t\v\r\n\f\a\b]			{;}
/*int double char string identifer*/
[0-9]+\.[0-9]+				{ 
								double dtmp;
								sscanf(yytext, "%lf", &dtmp);
								yylval.dVal = dtmp;
								return REAL; 
							}
[0-9]+						{
								int itmp;
								sscanf(yytext, "%d", &itmp);
								yylval.iVal = itmp; 
								return INTEGER; 
							}
\'.\'         				{ 
								yylval.cVal = yytext[1];
								return CHAR;
							}
\'\\.\'   					{
								yyval.cVal = SecondChar(yytext[2]);
								return CHAR;
							}					
\"(\\.|[^"\\])*\"      		{	
								yylval.sVal = new std::string(yytext, yyleng);
								return STRING;
							}
[a-zA-Z_]([a-zA-Z_0-9])*	{
								yylval.sVal = new std::string(yytext, yyleng);
								return IDENTIFER;
							}								
.							{printf("UNKNOWN TOKEN : %s ,AT LINENUMBER:%d\n",yytext,linenumber);}
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