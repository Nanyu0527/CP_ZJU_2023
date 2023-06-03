/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LAB_YACC_HPP_INCLUDED
# define YY_YY_LAB_YACC_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CHAR = 258,                    /* CHAR  */
    INTEGER = 259,                 /* INTEGER  */
    STRING = 260,                  /* STRING  */
    REAL = 261,                    /* REAL  */
    IDENTIFER = 262,               /* IDENTIFER  */
    IF = 263,                      /* IF  */
    ELSE = 264,                    /* ELSE  */
    BREAK = 265,                   /* BREAK  */
    RETURN = 266,                  /* RETURN  */
    WHILE = 267,                   /* WHILE  */
    AND = 268,                     /* AND  */
    OR = 269,                      /* OR  */
    LT = 270,                      /* LT  */
    GT = 271,                      /* GT  */
    LE = 272,                      /* LE  */
    GE = 273,                      /* GE  */
    EQ = 274,                      /* EQ  */
    NE = 275,                      /* NE  */
    MINUS = 276,                   /* MINUS  */
    PLUS = 277,                    /* PLUS  */
    MUL = 278,                     /* MUL  */
    DIV = 279,                     /* DIV  */
    MOD = 280,                     /* MOD  */
    SEMICOLON = 281,               /* SEMICOLON  */
    LBRACE = 282,                  /* LBRACE  */
    RBRACE = 283,                  /* RBRACE  */
    COMMA = 284,                   /* COMMA  */
    COLON = 285,                   /* COLON  */
    ASSIGN = 286,                  /* ASSIGN  */
    LPARENT = 287,                 /* LPARENT  */
    RPARENT = 288,                 /* RPARENT  */
    LBRACKET = 289,                /* LBRACKET  */
    RBRACKET = 290,                /* RBRACKET  */
    DOT = 291,                     /* DOT  */
    INTERROGATION = 292,           /* INTERROGATION  */
    BITAND = 293,                  /* BITAND  */
    BITNOT = 294,                  /* BITNOT  */
    BITOR = 295,                   /* BITOR  */
    BITXOR = 296,                  /* BITXOR  */
    NOT = 297                      /* NOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "c.y"

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

#line 122 "lab_yacc.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LAB_YACC_HPP_INCLUDED  */
