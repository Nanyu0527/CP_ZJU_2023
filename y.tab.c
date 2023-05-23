/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "c.y"

    #include "AST.h"
    #include <iostream>
    BlockNode* root; 

#line 77 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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


#line 230 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BREAK = 3,                      /* BREAK  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_FOR = 8,                        /* FOR  */
  YYSYMBOL_AND = 9,                        /* AND  */
  YYSYMBOL_OR = 10,                        /* OR  */
  YYSYMBOL_LE = 11,                        /* LE  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_NE = 14,                        /* NE  */
  YYSYMBOL_SEMICOLON = 15,                 /* SEMICOLON  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_COLON = 19,                     /* COLON  */
  YYSYMBOL_ASSIGN = 20,                    /* ASSIGN  */
  YYSYMBOL_LPARENT = 21,                   /* LPARENT  */
  YYSYMBOL_RPARENT = 22,                   /* RPARENT  */
  YYSYMBOL_LBRACKET = 23,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 24,                  /* RBRACKET  */
  YYSYMBOL_DOT = 25,                       /* DOT  */
  YYSYMBOL_BITAND = 26,                    /* BITAND  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_BITNOT = 28,                    /* BITNOT  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_MUL = 31,                       /* MUL  */
  YYSYMBOL_DIV = 32,                       /* DIV  */
  YYSYMBOL_MOD = 33,                       /* MOD  */
  YYSYMBOL_LT = 34,                        /* LT  */
  YYSYMBOL_GT = 35,                        /* GT  */
  YYSYMBOL_BITXOR = 36,                    /* BITXOR  */
  YYSYMBOL_BITOR = 37,                     /* BITOR  */
  YYSYMBOL_INTERROGATION = 38,             /* INTERROGATION  */
  YYSYMBOL_INTEGER = 39,                   /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 40,                /* IDENTIFIER  */
  YYSYMBOL_REAL = 41,                      /* REAL  */
  YYSYMBOL_CHAR = 42,                      /* CHAR  */
  YYSYMBOL_STRING = 43,                    /* STRING  */
  YYSYMBOL_44_ = 44,                       /* '('  */
  YYSYMBOL_45_ = 45,                       /* ')'  */
  YYSYMBOL_46_ = 46,                       /* '*'  */
  YYSYMBOL_47_ = 47,                       /* '['  */
  YYSYMBOL_48_ = 48,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_stmlist = 51,                   /* stmlist  */
  YYSYMBOL_stm = 52,                       /* stm  */
  YYSYMBOL_block = 53,                     /* block  */
  YYSYMBOL_vardec = 54,                    /* vardec  */
  YYSYMBOL_fundec = 55,                    /* fundec  */
  YYSYMBOL_fun_args = 56,                  /* fun_args  */
  YYSYMBOL_identifier = 57,                /* identifier  */
  YYSYMBOL_constant = 58,                  /* constant  */
  YYSYMBOL_call_args = 59,                 /* call_args  */
  YYSYMBOL_exp = 60                        /* exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   313

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      44,    45,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    48,    48,    52,    53,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    69,    70,    73,    74,    75,
      78,    83,    84,    85,    91,    94,    97,   100,   103,   108,
     111,   115,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BREAK", "ELSE", "IF",
  "RETURN", "WHILE", "FOR", "AND", "OR", "LE", "GE", "EQ", "NE",
  "SEMICOLON", "LBRACE", "RBRACE", "COMMA", "COLON", "ASSIGN", "LPARENT",
  "RPARENT", "LBRACKET", "RBRACKET", "DOT", "BITAND", "NOT", "BITNOT",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "LT", "GT", "BITXOR", "BITOR",
  "INTERROGATION", "INTEGER", "IDENTIFIER", "REAL", "CHAR", "STRING",
  "'('", "')'", "'*'", "'['", "']'", "$accept", "program", "stmlist",
  "stm", "block", "vardec", "fundec", "fun_args", "identifier", "constant",
  "call_args", "exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-54)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     107,    -8,     1,    34,     2,     6,   242,   -54,   -54,   -54,
     -54,   -54,   -35,    21,   107,   -54,    13,   -54,   -14,   -54,
     148,   -54,   242,   -54,   -10,   155,   242,   242,   182,     3,
     -54,   -54,   -54,   242,   242,   242,    -4,   242,   242,   242,
     242,   242,   242,   -54,   242,   242,   242,   242,   242,   242,
     196,   -54,   210,   224,   -54,   242,   265,   238,   -16,   265,
     242,   -35,    15,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,    36,    36,    36,   108,    37,
     242,   -54,   265,   -54,    -7,   -35,    32,    62,    55,   -54,
     -54,   -54,   242,   265,   -35,    36,    28,   -54,   -54,    90,
      36,   265,   -54,   -54,   -54,   -54
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,    24,    26,
      27,    28,     0,     0,     2,     3,     0,     5,    48,    51,
       0,    10,     0,     8,    48,     0,     0,     0,     0,    49,
       1,     4,     6,     0,     0,    29,    17,     0,     0,     0,
       0,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       0,     9,     0,     0,    52,     0,    32,     0,     0,    30,
       0,    21,     0,    38,    39,    40,    41,    42,    43,    34,
      35,    36,    37,    44,    45,     0,     0,     0,     0,    46,
       0,    33,    18,    23,     0,     0,     0,     0,    11,    13,
      14,    50,     0,    31,     0,     0,    17,    19,    16,     0,
       0,    47,    22,    20,    15,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   -27,   -11,   213,   -53,   -54,   -54,     0,   -54,
     -54,    -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    13,    14,    15,    88,    16,    17,    84,    24,    19,
      58,    20
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      18,    25,    80,    31,    28,     8,    33,    21,    83,    34,
      33,    94,    29,    34,    18,    95,    60,    61,    36,    62,
      50,    30,    22,    26,    52,    53,     8,    27,    32,    81,
      35,    56,    57,    59,    35,    63,    64,    65,    66,    67,
      68,   102,    69,    70,    71,    72,    73,    74,    60,    23,
      55,    62,    87,    78,    86,     6,    97,    92,    82,   100,
      99,    85,     0,     0,     0,     1,     0,     2,     3,     4,
       5,     0,     0,     7,     8,     9,    10,    11,    93,    98,
      12,     0,     0,     6,     0,    96,     0,    18,    31,     0,
     101,     0,     0,     1,    85,     2,     3,     4,     5,    18,
       0,     7,     8,     9,    10,    11,     0,   104,    12,     0,
       1,     6,     2,     3,     4,     5,     0,    37,    38,    39,
      40,    41,    42,     0,     0,     0,     0,     0,     6,     7,
       8,     9,    10,    11,     0,     0,    12,    44,    45,    46,
      47,     0,    48,    49,     0,     0,     7,     8,     9,    10,
      11,     0,     0,    12,     0,     0,    91,    37,    38,    39,
      40,    41,    42,    43,    37,    38,    39,    40,    41,    42,
      51,     0,     0,     0,     0,     0,     0,    44,    45,    46,
      47,     0,    48,    49,    44,    45,    46,    47,     0,    48,
      49,    37,    38,    39,    40,    41,    42,     0,     0,     0,
       0,     0,     0,     0,    54,    37,    38,    39,    40,    41,
      42,    44,    45,    46,    47,     0,    48,    49,    75,    37,
      38,    39,    40,    41,    42,    44,    45,    46,    47,     0,
      48,    49,    76,    37,    38,    39,    40,    41,    42,    44,
      45,    46,    47,     0,    48,    49,    77,    37,    38,    39,
      40,    41,    42,    44,    45,    46,    47,     0,    48,    49,
       0,     0,    79,     6,     0,     0,     0,    44,    45,    46,
      47,     0,    48,    49,    37,    38,    39,    40,    41,    42,
       0,     7,     8,     9,    10,    11,     0,     0,    12,    89,
      90,     0,     0,     0,    44,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,   105
};

static const yytype_int8 yycheck[] =
{
       0,     3,    18,    14,     6,    40,    20,    15,    61,    23,
      20,    18,    12,    23,    14,    22,    20,    21,    18,    23,
      22,     0,    21,    21,    26,    27,    40,    21,    15,    45,
      44,    33,    34,    35,    44,    37,    38,    39,    40,    41,
      42,    94,    44,    45,    46,    47,    48,    49,    20,    15,
      47,    23,    16,    55,    39,    21,    24,    20,    60,     4,
      87,    61,    -1,    -1,    -1,     3,    -1,     5,     6,     7,
       8,    -1,    -1,    39,    40,    41,    42,    43,    80,    17,
      46,    -1,    -1,    21,    -1,    85,    -1,    87,    99,    -1,
      92,    -1,    -1,     3,    94,     5,     6,     7,     8,    99,
      -1,    39,    40,    41,    42,    43,    -1,    17,    46,    -1,
       3,    21,     5,     6,     7,     8,    -1,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    21,    39,
      40,    41,    42,    43,    -1,    -1,    46,    29,    30,    31,
      32,    -1,    34,    35,    -1,    -1,    39,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    -1,    48,     9,    10,    11,
      12,    13,    14,    15,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    -1,    34,    35,    29,    30,    31,    32,    -1,    34,
      35,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,     9,    10,    11,    12,    13,
      14,    29,    30,    31,    32,    -1,    34,    35,    22,     9,
      10,    11,    12,    13,    14,    29,    30,    31,    32,    -1,
      34,    35,    22,     9,    10,    11,    12,    13,    14,    29,
      30,    31,    32,    -1,    34,    35,    22,     9,    10,    11,
      12,    13,    14,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    24,    21,    -1,    -1,    -1,    29,    30,    31,
      32,    -1,    34,    35,     9,    10,    11,    12,    13,    14,
      -1,    39,    40,    41,    42,    43,    -1,    -1,    46,    76,
      77,    -1,    -1,    -1,    29,    30,    31,    32,    -1,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,
      -1,    -1,    -1,   100
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,     8,    21,    39,    40,    41,
      42,    43,    46,    50,    51,    52,    54,    55,    57,    58,
      60,    15,    21,    15,    57,    60,    21,    21,    60,    57,
       0,    52,    15,    20,    23,    44,    57,     9,    10,    11,
      12,    13,    14,    15,    29,    30,    31,    32,    34,    35,
      60,    15,    60,    60,    22,    47,    60,    60,    59,    60,
      20,    21,    23,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    22,    22,    22,    60,    24,
      18,    45,    60,    54,    56,    57,    39,    16,    53,    53,
      53,    48,    20,    60,    18,    22,    57,    24,    17,    51,
       4,    60,    54,    53,    17,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    54,    54,    54,
      55,    56,    56,    56,    57,    58,    58,    58,    58,    59,
      59,    59,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     2,     2,     3,
       2,     5,     7,     5,     5,     3,     2,     2,     4,     5,
       6,     0,     3,     1,     1,     1,     1,     1,     1,     0,
       1,     3,     3,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     6,     1,     2,
       5,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmlist  */
#line 48 "c.y"
       {
    root = (yyvsp[0].block);
}
#line 1377 "y.tab.c"
    break;

  case 3: /* stmlist: stm  */
#line 52 "c.y"
   {(yyval.block) = new BlockNode();}
#line 1383 "y.tab.c"
    break;

  case 7: /* stm: exp SEMICOLON  */
#line 58 "c.y"
               {(yyval.stm) = new ExpStmNode(*(yyvsp[-1].exp));}
#line 1389 "y.tab.c"
    break;

  case 8: /* stm: RETURN SEMICOLON  */
#line 59 "c.y"
                  {(yyval.stm) = new ReturnNULLStmNode();}
#line 1395 "y.tab.c"
    break;

  case 9: /* stm: RETURN exp SEMICOLON  */
#line 60 "c.y"
                      {(yyval.stm) = new ReturnStmNode();}
#line 1401 "y.tab.c"
    break;

  case 10: /* stm: BREAK SEMICOLON  */
#line 61 "c.y"
                 {(yyval.stm) = new BreakStmNode();}
#line 1407 "y.tab.c"
    break;

  case 11: /* stm: IF LPARENT exp RPARENT block  */
#line 62 "c.y"
                               {(yyval.stm) = IfStmNode(*(yyvsp[-2].exp),*(yyvsp[0].block));}
#line 1413 "y.tab.c"
    break;

  case 12: /* stm: IF LPARENT exp RPARENT block ELSE block  */
#line 63 "c.y"
                                          {(yyval.stm) = new IfElseStmNode(*(yyvsp[-4].exp),*(yyvsp[-2].block),*(yyvsp[0].block));}
#line 1419 "y.tab.c"
    break;

  case 13: /* stm: WHILE LPARENT exp RPARENT block  */
#line 64 "c.y"
                                  {(yyval.stm) = new WhileStmNode(*(yyvsp[-2].exp),*(yyvsp[0].block));}
#line 1425 "y.tab.c"
    break;

  case 14: /* stm: FOR LPARENT exp RPARENT block  */
#line 65 "c.y"
                                {(yyval.stm) = new ForStmNode(*(yyvsp[-2].exp),*(yyvsp[0].block));}
#line 1431 "y.tab.c"
    break;

  case 15: /* block: LBRACE stmlist RBRACE  */
#line 69 "c.y"
                     {(yyval.block) = (yyvsp[-1].block);}
#line 1437 "y.tab.c"
    break;

  case 16: /* block: LBRACE RBRACE  */
#line 70 "c.y"
               {(yyval.block) = new BlockNode();}
#line 1443 "y.tab.c"
    break;

  case 17: /* vardec: identifier identifier  */
#line 73 "c.y"
                     {(yyval.stm) = new VarDecNode(*(yyvsp[-1].identifier),*(yyvsp[0].identifier));}
#line 1449 "y.tab.c"
    break;

  case 18: /* vardec: identifier identifier ASSIGN exp  */
#line 74 "c.y"
                                  {(yyval.stm) = new VarDecNode(*(yyvsp[-3].identifier),*(yyvsp[-2].identifier),(yyvsp[0].exp));}
#line 1455 "y.tab.c"
    break;

  case 19: /* vardec: identifier identifier LBRACKET INTEGER RBRACKET  */
#line 75 "c.y"
                                                     {(yyval.stm) = new VarDecNode(*(yyvsp[-4].identifier),*(yyvsp[-3].identifier),(yyvsp[-1].iVal));}
#line 1461 "y.tab.c"
    break;

  case 20: /* fundec: identifier identifier LPARENT fun_args RPARENT block  */
#line 78 "c.y"
                                                    {
    (yyval.stm) = new FunDecNode(*(yyvsp[-5].identifier), *(yyvsp[-4].identifier), *(yyvsp[-2].vardeclist), *(yyvsp[0].block));
}
#line 1469 "y.tab.c"
    break;

  case 21: /* fun_args: %empty  */
#line 83 "c.y"
 {(yyval.vardeclist) = new std::vector<VarDecNode*>();}
#line 1475 "y.tab.c"
    break;

  case 22: /* fun_args: fun_args COMMA vardec  */
#line 84 "c.y"
                       {(yyvsp[-2].vardeclist) -> push_back((yyval.vardeclist)3);}
#line 1481 "y.tab.c"
    break;

  case 23: /* fun_args: vardec  */
#line 85 "c.y"
        {
    (yyval.vardeclist) = new std::vector<VarDecNode*>();
    (yyval.vardeclist) -> push_back((yyval.vardeclist)1);
}
#line 1490 "y.tab.c"
    break;

  case 24: /* identifier: IDENTIFIER  */
#line 91 "c.y"
           {(yyval.identifier) = new IdentifierNode(*(yyvsp[0].iVal));}
#line 1496 "y.tab.c"
    break;

  case 25: /* constant: INTEGER  */
#line 94 "c.y"
         {
    (yyval.exp) = new IntNode(*(yyvsp[0].iVal));
}
#line 1504 "y.tab.c"
    break;

  case 26: /* constant: REAL  */
#line 97 "c.y"
       {
    (yyval.exp) = new DoubleNode(*(yyvsp[0].dVal));
}
#line 1512 "y.tab.c"
    break;

  case 27: /* constant: CHAR  */
#line 100 "c.y"
      {
    (yyval.exp) = new CharNode(*(yyvsp[0].cVal));
}
#line 1520 "y.tab.c"
    break;

  case 28: /* constant: STRING  */
#line 103 "c.y"
        {
    (yyval.exp) = new StringNode(*(yyvsp[0].sVal));
}
#line 1528 "y.tab.c"
    break;

  case 29: /* call_args: %empty  */
#line 108 "c.y"
    {
        (yyval.explist) = new std::vector<ExpressionNode*>();
    }
#line 1536 "y.tab.c"
    break;

  case 30: /* call_args: exp  */
#line 111 "c.y"
          {
        (yyval.explist) = new std::vector<ExpressionNode*>();
        (yyval.explist)->push_back((yyvsp[0].exp));
    }
#line 1545 "y.tab.c"
    break;

  case 31: /* call_args: call_args COMMA exp  */
#line 115 "c.y"
                          {
        (yyvsp[-2].explist)->push_back((yyvsp[0].exp));
    }
#line 1553 "y.tab.c"
    break;

  case 32: /* exp: identifier ASSIGN exp  */
#line 120 "c.y"
                     {(yyval.exp) = new AssignNode(*(yyvsp[-2].identifier),*(yyvsp[0].exp));}
#line 1559 "y.tab.c"
    break;

  case 33: /* exp: identifier '(' call_args ')'  */
#line 121 "c.y"
                               {(yyval.exp) = new FunCallNode(*(yyvsp[-3].identifier),*(yyvsp[-1].explist));}
#line 1565 "y.tab.c"
    break;

  case 34: /* exp: exp PLUS exp  */
#line 122 "c.y"
               {(yyval.exp) = new BinOpNode(1,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1571 "y.tab.c"
    break;

  case 35: /* exp: exp MINUS exp  */
#line 123 "c.y"
                {(yyval.exp) = new BinOpNode(2,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1577 "y.tab.c"
    break;

  case 36: /* exp: exp MUL exp  */
#line 124 "c.y"
              {(yyval.exp) = new BinOpNode(3,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1583 "y.tab.c"
    break;

  case 37: /* exp: exp DIV exp  */
#line 125 "c.y"
              {(yyval.exp) = new BinOpNode(4,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1589 "y.tab.c"
    break;

  case 38: /* exp: exp AND exp  */
#line 126 "c.y"
              {(yyval.exp) = new BinOpNode(5,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1595 "y.tab.c"
    break;

  case 39: /* exp: exp OR exp  */
#line 127 "c.y"
             {(yyval.exp) = new BinOpNode(6,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1601 "y.tab.c"
    break;

  case 40: /* exp: exp LE exp  */
#line 128 "c.y"
             {(yyval.exp) = new BinOpNode(7,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1607 "y.tab.c"
    break;

  case 41: /* exp: exp GE exp  */
#line 129 "c.y"
             {(yyval.exp) = new BinOpNode(8,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1613 "y.tab.c"
    break;

  case 42: /* exp: exp EQ exp  */
#line 130 "c.y"
             {(yyval.exp) = new BinOpNode(9,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1619 "y.tab.c"
    break;

  case 43: /* exp: exp NE exp  */
#line 131 "c.y"
             {(yyval.exp) = new BinOpNode(10,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1625 "y.tab.c"
    break;

  case 44: /* exp: exp LT exp  */
#line 132 "c.y"
             {(yyval.exp) = new BinOpNode(11,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1631 "y.tab.c"
    break;

  case 45: /* exp: exp GT exp  */
#line 133 "c.y"
             {(yyval.exp) = new BinOpNode(12,*(yyvsp[-2].exp),*(yyvsp[0].exp));}
#line 1637 "y.tab.c"
    break;

  case 46: /* exp: identifier LBRACKET exp RBRACKET  */
#line 134 "c.y"
                                       {(yyval.exp) = new ArrayEleNode(*(yyvsp[-3].identifier),*(yyvsp[-1].exp));}
#line 1643 "y.tab.c"
    break;

  case 47: /* exp: identifier LBRACKET exp RBRACKET ASSIGN exp  */
#line 135 "c.y"
                                                  {(yyval.exp) = new ArrayAssNode(*(yyvsp[-5].identifier),*(yyvsp[-3].exp),*(yyvsp[0].exp));}
#line 1649 "y.tab.c"
    break;

  case 48: /* exp: identifier  */
#line 136 "c.y"
             { (yyval.exp) = (yyvsp[0].identifier) ;}
#line 1655 "y.tab.c"
    break;

  case 49: /* exp: '*' identifier  */
#line 137 "c.y"
                 {(yyval.exp) = getAddrNode(*(yyvsp[0].identifier));}
#line 1661 "y.tab.c"
    break;

  case 50: /* exp: '*' identifier '[' exp ']'  */
#line 138 "c.y"
                             {(yyval.exp) = getArrayAddrNode(*(yyvsp[-3].identifier),*(yyvsp[-1].exp));}
#line 1667 "y.tab.c"
    break;

  case 52: /* exp: LPARENT exp RPARENT  */
#line 140 "c.y"
                     {(yyval.exp) = (yyvsp[-1].exp)}
#line 1673 "y.tab.c"
    break;


#line 1677 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 142 "c.y"

void yyerror(char *str){
    fprintf(stderr,"error:%s\n",str);
}    

int yywrap(){
    return 1;
}
int main(){
    yyparse();
}
