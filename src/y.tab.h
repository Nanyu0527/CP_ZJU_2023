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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    BREAK = 258,                   /* BREAK  */
    ELSE = 259,                    /* ELSE  */
    IF = 260,                      /* IF  */
    RETURN = 261,                  /* RETURN  */
    WHILE = 262,                   /* WHILE  */
    FOR = 263,                     /* FOR  */
    AND = 264,                     /* AND  */
    OR = 265,                      /* OR  */
    LE = 266,                      /* LE  */
    GE = 267,                      /* GE  */
    EQ = 268,                      /* EQ  */
    NE = 269,                      /* NE  */
    SEMICOLON = 270,               /* SEMICOLON  */
    LBRACE = 271,                  /* LBRACE  */
    RBRACE = 272,                  /* RBRACE  */
    COMMA = 273,                   /* COMMA  */
    COLON = 274,                   /* COLON  */
    ASSIGN = 275,                  /* ASSIGN  */
    LPARENT = 276,                 /* LPARENT  */
    RPARENT = 277,                 /* RPARENT  */
    LBRACKET = 278,                /* LBRACKET  */
    RBRACKET = 279,                /* RBRACKET  */
    DOT = 280,                     /* DOT  */
    BITAND = 281,                  /* BITAND  */
    NOT = 282,                     /* NOT  */
    BITNOT = 283,                  /* BITNOT  */
    PLUS = 284,                    /* PLUS  */
    MINUS = 285,                   /* MINUS  */
    MUL = 286,                     /* MUL  */
    DIV = 287,                     /* DIV  */
    MOD = 288,                     /* MOD  */
    LT = 289,                      /* LT  */
    GT = 290,                      /* GT  */
    BITXOR = 291,                  /* BITXOR  */
    BITOR = 292,                   /* BITOR  */
    INTERROGATION = 293,           /* INTERROGATION  */
    INTEGER = 294,                 /* INTEGER  */
    IDENTIFIER = 295,              /* IDENTIFIER  */
    REAL = 296,                    /* REAL  */
    CHAR = 297,                    /* CHAR  */
    STRING = 298                   /* STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define BREAK 258
#define ELSE 259
#define IF 260
#define RETURN 261
#define WHILE 262
#define FOR 263
#define AND 264
#define OR 265
#define LE 266
#define GE 267
#define EQ 268
#define NE 269
#define SEMICOLON 270
#define LBRACE 271
#define RBRACE 272
#define COMMA 273
#define COLON 274
#define ASSIGN 275
#define LPARENT 276
#define RPARENT 277
#define LBRACKET 278
#define RBRACKET 279
#define DOT 280
#define BITAND 281
#define NOT 282
#define BITNOT 283
#define PLUS 284
#define MINUS 285
#define MUL 286
#define DIV 287
#define MOD 288
#define LT 289
#define GT 290
#define BITXOR 291
#define BITOR 292
#define INTERROGATION 293
#define INTEGER 294
#define IDENTIFIER 295
#define REAL 296
#define CHAR 297
#define STRING 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 7 "c.y"

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


#line 167 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
