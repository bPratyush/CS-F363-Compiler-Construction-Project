/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_BEGIN = 258,
     TK_END = 259,
     TK_PROGRAM = 260,
     TK_VARDECL = 261,
     TK_INT = 262,
     TK_CHAR = 263,
     TK_COLON = 264,
     TK_SEP = 265,
     TK_IF = 266,
     TK_ELSE = 267,
     TK_WHILE = 268,
     TK_FOR = 269,
     TK_DO = 270,
     TK_TO = 271,
     TK_INC = 272,
     TK_DEC = 273,
     TK_PRINT = 274,
     TK_SCAN = 275,
     TK_MAIN = 276,
     IDENTIFIER = 277,
     INTEGER_CONST = 278,
     CHAR_CONST = 279,
     STRING_LITERAL = 280,
     LPAREN = 281,
     RPAREN = 282,
     COMMA = 283,
     PLUS = 284,
     MINUS = 285,
     MULT = 286,
     DIV = 287,
     MOD = 288,
     EQ = 289,
     GT = 290,
     LT = 291,
     GE = 292,
     LE = 293,
     NE = 294,
     ASSIGN = 295,
     PLUS_ASSIGN = 296,
     MINUS_ASSIGN = 297,
     MULT_ASSIGN = 298,
     DIV_ASSIGN = 299,
     MOD_ASSIGN = 300,
     TK_BLOCKBEGIN = 301,
     IFX = 302,
     UNARY = 303
   };
#endif
/* Tokens.  */
#define TK_BEGIN 258
#define TK_END 259
#define TK_PROGRAM 260
#define TK_VARDECL 261
#define TK_INT 262
#define TK_CHAR 263
#define TK_COLON 264
#define TK_SEP 265
#define TK_IF 266
#define TK_ELSE 267
#define TK_WHILE 268
#define TK_FOR 269
#define TK_DO 270
#define TK_TO 271
#define TK_INC 272
#define TK_DEC 273
#define TK_PRINT 274
#define TK_SCAN 275
#define TK_MAIN 276
#define IDENTIFIER 277
#define INTEGER_CONST 278
#define CHAR_CONST 279
#define STRING_LITERAL 280
#define LPAREN 281
#define RPAREN 282
#define COMMA 283
#define PLUS 284
#define MINUS 285
#define MULT 286
#define DIV 287
#define MOD 288
#define EQ 289
#define GT 290
#define LT 291
#define GE 292
#define LE 293
#define NE 294
#define ASSIGN 295
#define PLUS_ASSIGN 296
#define MINUS_ASSIGN 297
#define MULT_ASSIGN 298
#define DIV_ASSIGN 299
#define MOD_ASSIGN 300
#define TK_BLOCKBEGIN 301
#define IFX 302
#define UNARY 303




/* Copy the first part of user declarations.  */
#line 1 "parserast.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserast.h"
#include "symbol_table.h"

// Function declarations
extern int yylex();
extern FILE *yyin;
extern int yylineno;
void yyerror(const char *s);

// Root of the AST
ASTNode* astRoot = NULL;
int flag=0;
// Global variables from lexer we might use
extern char* symbolTable[256];
extern int symbolCount;
int syntax_errors = 0;  // Counter to track syntax errors

int print_lexeme_token_pairs = 0; // Changed to default to AST building


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 49 "parserast.y"
{
    char* str;
    int num;
    struct ASTNode* ast;
    struct {
        char* typeStr;
        struct ASTNode* ast;
    } typed;
}
/* Line 193 of yacc.c.  */
#line 226 "parserast.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 239 "parserast.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   324

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNRULES -- Number of states.  */
#define YYNSTATES  292

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    10,    12,    14,    17,    19,    26,    33,
      39,    41,    44,    46,    53,    55,    57,    59,    61,    64,
      66,    68,    70,    72,    74,    76,    78,    82,    86,    90,
      94,    98,   102,   105,   107,   114,   115,   118,   120,   124,
     132,   134,   138,   142,   147,   154,   161,   170,   172,   174,
     176,   184,   190,   197,   202,   215,   226,   234,   236,   238,
     242,   246,   250,   254,   258,   262,   264,   268,   270,   272,
     274,   276,   278,   280,   283,   284,   287,   290,   293,   294,
     297,   300,   303,   306,   309,   310,   314,   318,   321,   322,
     326,   330,   334,   336,   339,   342,   345,   346,   348,   350,
     352,   356,   357,   360,   363,   365,   367,   369,   373,   375,
     377,   379,   381,   383,   385,   388,   389,   392,   395,   398,
     399,   402,   405,   408,   411,   414,   415,   419,   423,   426,
     427,   431,   435,   439,   441,   444,   447,   450,   453,   456,
     457,   459,   461,   463,   465,   467
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,     3,     5,     9,    51,     4,     5,    -1,
       1,    -1,    53,    -1,    53,    52,    -1,    57,    -1,     3,
      21,     9,    57,     4,    21,    -1,     3,     6,     9,    54,
       4,     6,    -1,     3,     6,     9,     4,     6,    -1,    55,
      -1,    54,    55,    -1,     1,    -1,    26,    22,    28,    56,
      27,    10,    -1,     7,    -1,     8,    -1,    22,    -1,    58,
      -1,    58,    57,    -1,    60,    -1,    61,    -1,    64,    -1,
      66,    -1,    67,    -1,    69,    -1,    59,    -1,    22,    37,
      23,    -1,    22,    34,    23,    -1,    22,    35,    23,    -1,
      22,    38,    23,    -1,    22,    36,    23,    -1,    22,    39,
      23,    -1,    87,    10,    -1,    10,    -1,    19,    26,    25,
      62,    27,    10,    -1,    -1,    28,    63,    -1,    87,    -1,
      63,    28,    87,    -1,    20,    26,    25,    28,    65,    27,
      10,    -1,    22,    -1,    65,    28,    22,    -1,    46,    57,
       4,    -1,    11,    68,    66,    10,    -1,    11,    68,    66,
      12,    66,    10,    -1,    11,    26,    68,    27,    66,    10,
      -1,    11,    26,    68,    27,    66,    12,    66,    10,    -1,
      23,    -1,    22,    -1,    59,    -1,    13,    26,    87,    27,
      15,    66,    10,    -1,    13,    87,    15,    66,    10,    -1,
      13,    26,    87,    27,    66,    10,    -1,    13,    87,    66,
      10,    -1,    14,    26,    22,    40,    87,    16,    70,    86,
      27,    15,    66,    10,    -1,    14,    22,    40,    87,    16,
      70,    86,    15,    66,    10,    -1,    15,    58,    13,    26,
      87,    27,    10,    -1,    72,    -1,    71,    -1,    22,    37,
      23,    -1,    22,    34,    23,    -1,    22,    35,    23,    -1,
      22,    38,    23,    -1,    22,    36,    23,    -1,    22,    39,
      23,    -1,    74,    -1,    22,    73,    72,    -1,    40,    -1,
      41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,
      76,    75,    -1,    -1,    34,    76,    -1,    39,    76,    -1,
      78,    77,    -1,    -1,    36,    78,    -1,    35,    78,    -1,
      38,    78,    -1,    37,    78,    -1,    80,    79,    -1,    -1,
      29,    80,    79,    -1,    30,    80,    79,    -1,    82,    81,
      -1,    -1,    31,    82,    81,    -1,    32,    82,    81,    -1,
      33,    82,    81,    -1,    83,    -1,    29,    82,    -1,    30,
      82,    -1,    85,    84,    -1,    -1,    22,    -1,    23,    -1,
      24,    -1,    26,    87,    27,    -1,    -1,    17,    70,    -1,
      18,    70,    -1,    88,    -1,    59,    -1,    90,    -1,    22,
      89,    88,    -1,    40,    -1,    41,    -1,    42,    -1,    43,
      -1,    44,    -1,    45,    -1,    92,    91,    -1,    -1,    34,
      92,    -1,    39,    92,    -1,    94,    93,    -1,    -1,    36,
      94,    -1,    35,    94,    -1,    38,    94,    -1,    37,    94,
      -1,    96,    95,    -1,    -1,    29,    96,    95,    -1,    30,
      96,    95,    -1,    98,    97,    -1,    -1,    31,    98,    97,
      -1,    32,    98,    97,    -1,    33,    98,    97,    -1,    99,
      -1,    29,    98,    -1,    30,    98,    -1,    17,    98,    -1,
      18,    98,    -1,   101,   100,    -1,    -1,    17,    -1,    18,
      -1,    22,    -1,    23,    -1,    24,    -1,    26,    87,    27,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    86,    86,   102,   114,   118,   140,   144,   151,   157,
     164,   168,   177,   189,   198,   202,   206,   215,   221,   242,
     246,   250,   254,   258,   262,   266,   273,   279,   285,   291,
     297,   303,   312,   316,   323,   340,   343,   350,   354,   366,
     383,   388,   402,   409,   413,   417,   421,   428,   432,   436,
     443,   447,   452,   456,   460,   473,   483,   490,   495,   500,
     506,   512,   518,   524,   530,   538,   542,   551,   555,   559,
     563,   567,   571,   578,   592,   595,   599,   606,   620,   623,
     627,   631,   635,   642,   656,   659,   669,   683,   697,   700,
     711,   722,   736,   740,   744,   751,   765,   771,   775,   779,
     783,   791,   794,   798,   805,   810,   816,   820,   829,   833,
     837,   841,   845,   849,   856,   870,   873,   877,   884,   898,
     901,   905,   909,   913,   920,   934,   937,   947,   961,   975,
     978,   989,  1000,  1014,  1018,  1022,  1026,  1030,  1037,  1051,
    1054,  1058,  1065,  1069,  1073,  1077
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_BEGIN", "TK_END", "TK_PROGRAM",
  "TK_VARDECL", "TK_INT", "TK_CHAR", "TK_COLON", "TK_SEP", "TK_IF",
  "TK_ELSE", "TK_WHILE", "TK_FOR", "TK_DO", "TK_TO", "TK_INC", "TK_DEC",
  "TK_PRINT", "TK_SCAN", "TK_MAIN", "IDENTIFIER", "INTEGER_CONST",
  "CHAR_CONST", "STRING_LITERAL", "LPAREN", "RPAREN", "COMMA", "PLUS",
  "MINUS", "MULT", "DIV", "MOD", "EQ", "GT", "LT", "GE", "LE", "NE",
  "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN", "MULT_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "TK_BLOCKBEGIN", "IFX", "UNARY", "$accept", "program",
  "program_body", "main_section", "var_decl_section", "var_decl_list",
  "var_decl", "type", "statement_list", "statement",
  "conditional_statement", "expression_statement", "print_statement",
  "optional_print_args", "print_arg_list", "scan_statement", "id_list",
  "compound_statement", "selection_statement", "ifexpr",
  "iteration_statement", "for_expression", "for_conditional_statement",
  "for_assignment_expression", "for_assignment_operator",
  "for_equality_expression", "for_equality_expression_tail",
  "for_relational_expression", "for_relational_expression_tail",
  "for_additive_expression", "for_additive_expression_tail",
  "for_multiplicative_expression", "for_multiplicative_expression_tail",
  "for_unary_expression", "for_postfix_expression",
  "for_postfix_expression_tail", "for_primary_expression", "optional_inc",
  "expression", "assignment_expression", "assignment_operator",
  "equality_expression", "equality_expression_tail",
  "relational_expression", "relational_expression_tail",
  "additive_expression", "additive_expression_tail",
  "multiplicative_expression", "multiplicative_expression_tail",
  "unary_expression", "postfix_expression", "postfix_expression_tail",
  "primary_expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    53,    53,
      54,    54,    54,    55,    56,    56,    56,    57,    57,    58,
      58,    58,    58,    58,    58,    58,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    62,    62,    63,    63,    64,
      65,    65,    66,    67,    67,    67,    67,    68,    68,    68,
      69,    69,    69,    69,    69,    69,    69,    70,    70,    71,
      71,    71,    71,    71,    71,    72,    72,    73,    73,    73,
      73,    73,    73,    74,    75,    75,    75,    76,    77,    77,
      77,    77,    77,    78,    79,    79,    79,    80,    81,    81,
      81,    81,    82,    82,    82,    83,    84,    85,    85,    85,
      85,    86,    86,    86,    87,    87,    88,    88,    89,    89,
      89,    89,    89,    89,    90,    91,    91,    91,    92,    93,
      93,    93,    93,    93,    94,    95,    95,    95,    96,    97,
      97,    97,    97,    98,    98,    98,    98,    98,    99,   100,
     100,   100,   101,   101,   101,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     1,     1,     2,     1,     6,     6,     5,
       1,     2,     1,     6,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     6,     0,     2,     1,     3,     7,
       1,     3,     3,     4,     6,     6,     8,     1,     1,     1,
       7,     5,     6,     4,    12,    10,     7,     1,     1,     3,
       3,     3,     3,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     2,     0,     2,     2,     2,     0,     2,
       2,     2,     2,     2,     0,     3,     3,     2,     0,     3,
       3,     3,     1,     2,     2,     2,     0,     1,     1,     1,
       3,     0,     2,     2,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     0,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     0,     3,     3,     2,     0,
       3,     3,     3,     1,     2,     2,     2,     2,     2,     0,
       1,     1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     0,     1,     0,     0,     0,     4,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,   142,   143,   144,     0,     0,     0,     0,     5,
       6,    17,    25,    19,    20,    21,    22,    23,    24,     0,
     104,   106,   115,   119,   125,   129,   133,   139,     0,     2,
       0,    48,    47,     0,    49,     0,     0,   105,     0,     0,
       0,     0,   142,   136,   137,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,   110,   111,   112,   113,     0,
       0,   134,   135,     0,    18,    32,     0,     0,   114,     0,
       0,     0,     0,   118,     0,     0,   124,     0,     0,     0,
     128,   140,   141,   138,    12,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
      27,    28,    30,    26,    29,    31,   142,   107,   145,    42,
     116,   117,   121,   120,   123,   122,   125,   125,   129,   129,
     129,     9,     0,     0,    11,     0,     0,    43,     0,   145,
       0,    53,     0,     0,     0,     0,     0,     0,   126,   127,
     130,   131,   132,     0,     8,     0,     0,     0,     0,     0,
      51,     0,     0,     0,    36,    37,     0,    40,     0,    14,
      15,    16,     0,     7,    45,     0,    44,     0,    52,    97,
      98,    99,     0,     0,     0,   101,    58,    57,    65,    74,
      78,    84,    88,    92,    96,     0,     0,     0,    34,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
      67,    68,    69,    70,    71,    72,     0,     0,    97,    93,
      94,     0,     0,     0,     0,     0,    73,     0,     0,     0,
       0,    77,     0,     0,    83,     0,     0,     0,    87,    95,
     101,    56,    38,    39,    41,    13,    46,    60,    61,    63,
      59,    62,    64,    97,    66,   100,   102,   103,     0,    75,
      76,    80,    79,    82,    81,    84,    84,    88,    88,    88,
       0,     0,    85,    86,    89,    90,    91,     0,    55,     0,
       0,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     8,    29,     9,   107,   108,   182,    30,    31,
      57,    33,    34,   156,   174,    35,   178,    36,    37,    55,
      38,   195,   196,   197,   226,   198,   236,   199,   241,   200,
     244,   201,   248,   202,   203,   249,   204,   233,    39,    40,
      79,    41,    88,    42,    93,    43,    96,    44,   100,    45,
      46,   103,    47
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -179
static const yytype_int16 yypact[] =
{
      19,  -179,    18,    31,    38,  -179,    50,    58,    77,    15,
      78,    90,   104,  -179,    66,    53,   -18,    97,   127,   127,
      73,    83,   145,  -179,  -179,   137,   127,   127,    97,  -179,
    -179,    97,  -179,  -179,  -179,  -179,  -179,  -179,  -179,   108,
    -179,  -179,    20,   206,    27,    41,  -179,    88,    39,  -179,
     129,    98,  -179,   106,  -179,    85,   137,  -179,     2,   102,
     130,   149,  -179,  -179,  -179,   133,   143,   183,   187,   189,
     196,   202,   242,  -179,  -179,  -179,  -179,  -179,  -179,   147,
     247,  -179,  -179,   168,  -179,  -179,   127,   127,  -179,   127,
     127,   127,   127,  -179,   127,   127,  -179,   127,   127,   127,
    -179,  -179,  -179,  -179,  -179,   269,   254,    23,  -179,    97,
     250,    68,   251,    85,   270,   137,   239,   255,   256,   257,
    -179,  -179,  -179,  -179,  -179,  -179,   186,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,    27,    27,    41,    41,
      41,  -179,   258,   276,  -179,   279,    85,  -179,    85,     4,
     277,  -179,   272,   137,   137,   137,   262,   268,  -179,  -179,
    -179,  -179,  -179,    44,  -179,   271,   112,   281,    85,   283,
    -179,    74,   278,   273,   267,  -179,   286,  -179,   205,  -179,
    -179,  -179,   274,  -179,  -179,    85,  -179,   287,  -179,   160,
    -179,  -179,   137,   185,   185,   157,  -179,  -179,  -179,    21,
     210,   162,   115,  -179,  -179,    74,   288,   137,  -179,   289,
     280,   293,   294,  -179,   282,   284,   285,   290,   291,   292,
    -179,  -179,  -179,  -179,  -179,  -179,   194,   295,  -179,  -179,
    -179,    74,    74,   296,   185,   185,  -179,   185,   185,   185,
     185,  -179,   185,   185,  -179,   185,   185,   185,  -179,  -179,
     157,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,   195,  -179,  -179,  -179,  -179,    85,  -179,
    -179,  -179,  -179,  -179,  -179,   162,   162,   115,   115,   115,
     297,   299,  -179,  -179,  -179,  -179,  -179,   301,  -179,    85,
     300,  -179
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,  -179,  -179,   199,  -179,   -19,   302,
      -7,  -179,  -179,  -179,  -179,  -179,  -179,   -55,  -179,   259,
    -179,  -169,  -179,    91,  -179,  -179,  -179,    29,  -179,    12,
     -54,    24,   -20,  -178,  -179,  -179,  -179,    70,   -14,   244,
    -179,  -179,  -179,   182,  -179,   164,   134,   178,   122,   -13,
    -179,  -179,  -179
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     111,    58,    32,   114,    59,    63,    64,    54,    60,    83,
      32,    80,    84,    81,    82,   229,   230,   113,    12,   168,
       1,    32,     2,     4,    32,    13,    14,   143,    15,    16,
      17,     5,    18,    19,    20,    21,   250,    22,    23,    24,
     104,    25,   112,   105,    26,    27,    54,     6,    28,   106,
      28,   179,   180,     7,    86,   234,    94,    95,   150,    87,
     235,    28,   266,   267,    10,   106,   181,   277,   278,   279,
      18,    19,    97,    98,    99,    22,    23,    24,   147,    56,
     148,    11,    26,    27,   138,   139,   140,    48,    51,    52,
     145,   166,    53,   167,   169,    49,   189,   190,   191,    65,
     192,   152,    32,   193,   194,   101,   102,    13,    14,    66,
      15,    16,    17,   187,    18,    19,    20,    21,    85,    22,
      23,    24,   184,    25,   185,    50,    26,    27,    51,    52,
     212,    28,    67,    68,    69,    70,    71,    72,   109,   172,
     173,   175,   115,    28,    18,    19,   245,   246,   247,    62,
      23,    24,   116,    25,    18,    19,    26,    27,   118,    22,
      23,    24,   117,    25,    18,    19,    26,    27,   119,   126,
      23,    24,   129,    25,   231,   232,    26,    27,   227,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,   242,   243,   252,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   120,   228,   190,   191,
     121,   192,   122,   281,   193,   194,   263,   190,   191,   123,
     192,   282,   283,   193,   194,   124,    73,    74,    75,    76,
      77,    78,   209,   210,   290,   220,   221,   222,   223,   224,
     225,    89,    90,    91,    92,   237,   238,   239,   240,   271,
     272,   273,   274,   132,   133,   134,   135,   284,   285,   286,
     160,   161,   162,   269,   270,   125,   275,   276,   130,   131,
     158,   159,   136,   137,   128,   141,   142,   146,   149,   153,
     151,   154,   164,   165,   155,   157,   163,   170,   171,   176,
     177,   186,   183,   188,   205,   207,   208,   213,   251,   253,
     206,   211,   254,   255,   256,   257,   144,   258,   259,   288,
     291,   268,   110,   260,   261,   262,   289,   264,     0,    61,
     280,     0,   265,   127,   287
};

static const yytype_int16 yycheck[] =
{
      55,    15,     9,    58,    22,    18,    19,    14,    26,    28,
      17,    25,    31,    26,    27,   193,   194,    15,     3,    15,
       1,    28,     3,     5,    31,    10,    11,     4,    13,    14,
      15,     0,    17,    18,    19,    20,   205,    22,    23,    24,
       1,    26,    56,     4,    29,    30,    53,     9,    46,    26,
      46,     7,     8,     3,    34,    34,    29,    30,   113,    39,
      39,    46,   231,   232,     6,    26,    22,   245,   246,   247,
      17,    18,    31,    32,    33,    22,    23,    24,    10,    26,
      12,     4,    29,    30,    97,    98,    99,     9,    22,    23,
     109,   146,    26,   148,   149,     5,    22,    23,    24,    26,
      26,   115,   109,    29,    30,    17,    18,    10,    11,    26,
      13,    14,    15,   168,    17,    18,    19,    20,    10,    22,
      23,    24,    10,    26,    12,    21,    29,    30,    22,    23,
     185,    46,    34,    35,    36,    37,    38,    39,     9,   153,
     154,   155,    40,    46,    17,    18,    31,    32,    33,    22,
      23,    24,    22,    26,    17,    18,    29,    30,    25,    22,
      23,    24,    13,    26,    17,    18,    29,    30,    25,    22,
      23,    24,     4,    26,    17,    18,    29,    30,   192,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    29,    30,   207,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    23,    22,    23,    24,
      23,    26,    23,   268,    29,    30,    22,    23,    24,    23,
      26,   275,   276,    29,    30,    23,    40,    41,    42,    43,
      44,    45,    27,    28,   289,    40,    41,    42,    43,    44,
      45,    35,    36,    37,    38,    35,    36,    37,    38,   237,
     238,   239,   240,    89,    90,    91,    92,   277,   278,   279,
     138,   139,   140,   234,   235,    23,   242,   243,    86,    87,
     136,   137,    94,    95,    27,     6,    22,    27,    27,    40,
      10,    26,     6,     4,    28,    28,    28,    10,    16,    27,
      22,    10,    21,    10,    16,    28,    10,    10,    10,    10,
      27,    27,    22,    10,    10,    23,   107,    23,    23,    10,
      10,    15,    53,    23,    23,    23,    15,   226,    -1,    17,
     250,    -1,    27,    79,    27
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    50,     5,     0,     9,     3,    51,    53,
       6,     4,     3,    10,    11,    13,    14,    15,    17,    18,
      19,    20,    22,    23,    24,    26,    29,    30,    46,    52,
      57,    58,    59,    60,    61,    64,    66,    67,    69,    87,
      88,    90,    92,    94,    96,    98,    99,   101,     9,     5,
      21,    22,    23,    26,    59,    68,    26,    59,    87,    22,
      26,    58,    22,    98,    98,    26,    26,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    89,
      87,    98,    98,    57,    57,    10,    34,    39,    91,    35,
      36,    37,    38,    93,    29,    30,    95,    31,    32,    33,
      97,    17,    18,   100,     1,     4,    26,    54,    55,     9,
      68,    66,    87,    15,    66,    40,    22,    13,    25,    25,
      23,    23,    23,    23,    23,    23,    22,    88,    27,     4,
      92,    92,    94,    94,    94,    94,    96,    96,    98,    98,
      98,     6,    22,     4,    55,    57,    27,    10,    12,    27,
      66,    10,    87,    40,    26,    28,    62,    28,    95,    95,
      97,    97,    97,    28,     6,     4,    66,    66,    15,    66,
      10,    16,    87,    87,    63,    87,    27,    22,    65,     7,
       8,    22,    56,    21,    10,    12,    10,    66,    10,    22,
      23,    24,    26,    29,    30,    70,    71,    72,    74,    76,
      78,    80,    82,    83,    85,    16,    27,    28,    10,    27,
      28,    27,    66,    10,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    73,    87,    22,    82,
      82,    17,    18,    86,    34,    39,    75,    35,    36,    37,
      38,    77,    29,    30,    79,    31,    32,    33,    81,    84,
      70,    10,    87,    10,    22,    10,    10,    23,    23,    23,
      23,    23,    23,    22,    72,    27,    70,    70,    15,    76,
      76,    78,    78,    78,    78,    80,    80,    82,    82,    82,
      86,    66,    79,    79,    81,    81,    81,    27,    10,    15,
      66,    10
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 87 "parserast.y"
    {
        astRoot = createNode(NODE_PROGRAM);
        astRoot->data.children.left = (yyvsp[(4) - (6)].ast);
        
        if (!print_lexeme_token_pairs) {
            if (syntax_errors == 0) {
                //printAST(astRoot, 0);
                evaluate(astRoot);
                printSymbolTable();
            } else {
                printf("Syntax analysis completed with %d error(s).\n", syntax_errors);
            }
        }
        (yyval.ast) = astRoot;
    ;}
    break;

  case 3:
#line 102 "parserast.y"
    { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in program structure");
            exit(0);
        }
        (yyval.ast) = NULL;
        yyerrok; 
        {return 0;}
    ;}
    break;

  case 4:
#line 115 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 5:
#line 119 "parserast.y"
    {
        ASTNode* node = createNode(NODE_MAIN_SECTION);
        node->data.children.left = (yyvsp[(2) - (2)].ast);
        
        /* Link variable declarations with main section */
        if ((yyvsp[(1) - (2)].ast)) {
            ASTNode* varSection = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = varSection;
            
            /* Find the last node in the var_decl_section */
            while (varSection->next) {
                varSection = varSection->next;
            }
            varSection->next = node;
        } else {
            (yyval.ast) = node;
        }
    ;}
    break;

  case 6:
#line 141 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 7:
#line 145 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(4) - (6)].ast);
    ;}
    break;

  case 8:
#line 152 "parserast.y"
    {
        ASTNode* node = createNode(NODE_VARDECL_SECTION);
        node->data.children.left = (yyvsp[(4) - (6)].ast);
        (yyval.ast) = node;
    ;}
    break;

  case 9:
#line 158 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_VARDECL_SECTION);
    ;}
    break;

  case 10:
#line 165 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 11:
#line 169 "parserast.y"
    {
        if ((yyvsp[(1) - (2)].ast)) {
            addToList((yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast));
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        }
    ;}
    break;

  case 12:
#line 177 "parserast.y"
    { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in declaration");
            exit (0);
        }
        (yyval.ast) = NULL;
        yyerrok; 
        {return 0;}
    ;}
    break;

  case 13:
#line 190 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(2) - (6)].str));
        (yyval.ast) = createBinaryNode(NODE_VARDECL, idNode, (yyvsp[(4) - (6)].typed).ast);  // For AST
        insertSymbol((yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].typed).typeStr);                        
    ;}
    break;

  case 14:
#line 198 "parserast.y"
    {
        (yyval.typed).typeStr = strdup("int");
        (yyval.typed).ast = createNode(NODE_TYPE_INT);
    ;}
    break;

  case 15:
#line 202 "parserast.y"
    {
        (yyval.typed).typeStr = strdup("char");
        (yyval.typed).ast = createNode(NODE_TYPE_CHAR);
    ;}
    break;

  case 16:
#line 206 "parserast.y"
    {
        yyerror("Invalid data type");
        syntax_errors++;
        (yyval.typed).typeStr = strdup("invalid");
        (yyval.typed).ast = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 17:
#line 216 "parserast.y"
    {
        ASTNode* node = createNode(NODE_STATEMENT_LIST);
        node->data.children.left = (yyvsp[(1) - (1)].ast);
        (yyval.ast) = node;
    ;}
    break;

  case 18:
#line 222 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            ASTNode* stmtList = (yyvsp[(2) - (2)].ast);
            ASTNode* existingStmts = stmtList->data.children.left;
            
            if ((yyvsp[(1) - (2)].ast)) {
                (yyvsp[(1) - (2)].ast)->next = existingStmts;
                stmtList->data.children.left = (yyvsp[(1) - (2)].ast);
            }
            
            (yyval.ast) = stmtList;
        } else {
            ASTNode* node = createNode(NODE_STATEMENT_LIST);
            node->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = node;
        }
    ;}
    break;

  case 19:
#line 243 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 20:
#line 247 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 21:
#line 251 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 22:
#line 255 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 23:
#line 259 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 24:
#line 263 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 25:
#line 267 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 26:
#line 274 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_GE, idNode, constNode);
    ;}
    break;

  case 27:
#line 280 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_EQ, idNode, constNode);
    ;}
    break;

  case 28:
#line 286 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_GT, idNode, constNode);
    ;}
    break;

  case 29:
#line 292 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_LE, idNode, constNode);
    ;}
    break;

  case 30:
#line 298 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_LT, idNode, constNode);
    ;}
    break;

  case 31:
#line 304 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_NE, idNode, constNode);
    ;}
    break;

  case 32:
#line 313 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_EXPR_STMT, (yyvsp[(1) - (2)].ast), NULL);
    ;}
    break;

  case 33:
#line 317 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_EXPR_STMT);
    ;}
    break;

  case 34:
#line 324 "parserast.y"
    {
        char *src = (yyvsp[(3) - (6)].str), *dst = (yyvsp[(3) - (6)].str);
        while (*src) {
            if (*src != ' ') {
            *dst++ = *src;
            }
            src++;
        }
        *dst = '\0';
        ASTNode* formatNode = createStrNode(NODE_STRING_LITERAL, (yyvsp[(3) - (6)].str));
        (yyval.ast) = createIONode(NODE_PRINT_STMT, formatNode, (yyvsp[(4) - (6)].ast));
    ;}
    break;

  case 35:
#line 340 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 36:
#line 344 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(2) - (2)].ast);
    ;}
    break;

  case 37:
#line 351 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 38:
#line 355 "parserast.y"
    {
        if ((yyvsp[(1) - (3)].ast)) {
            addToList((yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = (yyvsp[(1) - (3)].ast);
        } else {
            (yyval.ast) = (yyvsp[(3) - (3)].ast);
        }
    ;}
    break;

  case 39:
#line 367 "parserast.y"
    {   
        char *src = (yyvsp[(3) - (7)].str), *dst = (yyvsp[(3) - (7)].str);
        while (*src) {
            if (*src != ' ') {
            *dst++ = *src;
            }
            src++;
        }
        *dst = '\0';
       
        ASTNode* formatNode = createStrNode(NODE_STRING_LITERAL, (yyvsp[(3) - (7)].str));
        (yyval.ast) = createIONode(NODE_SCAN_STMT, formatNode, (yyvsp[(5) - (7)].ast));
    ;}
    break;

  case 40:
#line 384 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (1)].str));
       
    ;}
    break;

  case 41:
#line 389 "parserast.y"
    {
        ASTNode* newNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(3) - (3)].str));
        if ((yyvsp[(1) - (3)].ast)) {
            addToList((yyvsp[(1) - (3)].ast), newNode);
            (yyval.ast) = (yyvsp[(1) - (3)].ast);
        } else {
            (yyval.ast) = newNode;
        }
      
    ;}
    break;

  case 42:
#line 403 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_COMPOUND_STMT, (yyvsp[(2) - (3)].ast), NULL);
    ;}
    break;

  case 43:
#line 410 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_IF_STMT, (yyvsp[(2) - (4)].ast), (yyvsp[(3) - (4)].ast));
    ;}
    break;

  case 44:
#line 414 "parserast.y"
    {
        (yyval.ast) = createTernaryNode(NODE_IF_ELSE_STMT, (yyvsp[(2) - (6)].ast), (yyvsp[(3) - (6)].ast), (yyvsp[(5) - (6)].ast));
    ;}
    break;

  case 45:
#line 418 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_IF_STMT, (yyvsp[(3) - (6)].ast), (yyvsp[(5) - (6)].ast));
    ;}
    break;

  case 46:
#line 422 "parserast.y"
    {
        (yyval.ast) = createTernaryNode(NODE_IF_ELSE_STMT, (yyvsp[(3) - (8)].ast), (yyvsp[(5) - (8)].ast), (yyvsp[(7) - (8)].ast));
    ;}
    break;

  case 47:
#line 429 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_INT_LITERAL, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 48:
#line 433 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 49:
#line 437 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 50:
#line 444 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_WHILE_STMT, (yyvsp[(3) - (7)].ast), (yyvsp[(6) - (7)].ast));
    ;}
    break;

  case 51:
#line 448 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_WHILE_STMT, (yyvsp[(2) - (5)].ast), (yyvsp[(4) - (5)].ast));
    ;}
    break;

  case 52:
#line 453 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_WHILE_STMT, (yyvsp[(3) - (6)].ast), (yyvsp[(5) - (6)].ast));
    ;}
    break;

  case 53:
#line 457 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_WHILE_STMT, (yyvsp[(2) - (4)].ast), (yyvsp[(3) - (4)].ast));
    ;}
    break;

  case 54:
#line 461 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(3) - (12)].str));
        ASTNode* initNode = createBinaryNode(NODE_ASSIGN, idNode, (yyvsp[(5) - (12)].ast));
    
        /* Store the increment expression and step expression with the loop condition */
        if ((yyvsp[(8) - (12)].ast)) {
            (yyvsp[(7) - (12)].ast)->next = (yyvsp[(8) - (12)].ast);
        }

        (yyval.ast) = createTernaryNode(NODE_FOR_STMT, initNode, (yyvsp[(7) - (12)].ast), (yyvsp[(11) - (12)].ast));

    ;}
    break;

  case 55:
#line 474 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(2) - (10)].str));
        ASTNode* initNode = createBinaryNode(NODE_ASSIGN, idNode, (yyvsp[(4) - (10)].ast));
        /* Store the increment expression and step expression with the loop condition */
        if((yyvsp[(7) - (10)].ast)){
            (yyvsp[(6) - (10)].ast)->next=(yyvsp[(7) - (10)].ast);
        }
        (yyval.ast) = createTernaryNode(NODE_FOR_STMT,initNode,(yyvsp[(6) - (10)].ast),(yyvsp[(9) - (10)].ast));
    ;}
    break;

  case 56:
#line 484 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_DO_WHILE_STMT, (yyvsp[(2) - (7)].ast), (yyvsp[(5) - (7)].ast));
    ;}
    break;

  case 57:
#line 491 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 58:
#line 495 "parserast.y"
    {
        (yyval.ast)=(yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 59:
#line 501 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_GE, idNode, constNode);
    ;}
    break;

  case 60:
#line 507 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_EQ, idNode, constNode);
    ;}
    break;

  case 61:
#line 513 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_GT, idNode, constNode);
    ;}
    break;

  case 62:
#line 519 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_LE, idNode, constNode);
    ;}
    break;

  case 63:
#line 525 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_LT, idNode, constNode);
    ;}
    break;

  case 64:
#line 531 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, (yyvsp[(3) - (3)].str));
        (yyval.ast) = createBinaryNode(NODE_NE, idNode, constNode);
    ;}
    break;

  case 65:
#line 539 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 66:
#line 543 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        (yyval.ast) = createBinaryNode((yyvsp[(2) - (3)].ast)->type, idNode, (yyvsp[(3) - (3)].ast));
        free((yyvsp[(2) - (3)].ast)); 
    ;}
    break;

  case 67:
#line 552 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_ASSIGN);
    ;}
    break;

  case 68:
#line 556 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_PLUS_ASSIGN);
    ;}
    break;

  case 69:
#line 560 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_MINUS_ASSIGN);
    ;}
    break;

  case 70:
#line 564 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_MULT_ASSIGN);
    ;}
    break;

  case 71:
#line 568 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_DIV_ASSIGN);
    ;}
    break;

  case 72:
#line 572 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_MOD_ASSIGN);
    ;}
    break;

  case 73:
#line 579 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the relational_expression as the left child of the equality expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 74:
#line 592 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 75:
#line 596 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_EQ, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 76:
#line 600 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_NE, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 77:
#line 607 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the additive_expression as the left child of the relational expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 78:
#line 620 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 79:
#line 624 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_LT, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 80:
#line 628 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_GT, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 81:
#line 632 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_LE, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 82:
#line 636 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_GE, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 83:
#line 643 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the multiplicative expression as the left child of the additive expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 84:
#line 656 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 85:
#line 660 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_ADD, NULL, (yyvsp[(2) - (3)].ast));
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 86:
#line 670 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_SUB, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 87:
#line 684 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the unary expression as the left child of the multiplicative expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 88:
#line 697 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 89:
#line 701 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_MUL, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 90:
#line 712 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_DIV, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 91:
#line 723 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_MOD, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 92:
#line 737 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 93:
#line 741 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_UNARY_PLUS, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 94:
#line 745 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_UNARY_MINUS, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 95:
#line 752 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Apply the postfix operator to the primary expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 96:
#line 765 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 97:
#line 772 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 98:
#line 776 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_INT_LITERAL, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 99:
#line 780 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_CHAR_LITERAL, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 100:
#line 784 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(2) - (3)].ast);
    ;}
    break;

  case 101:
#line 791 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 102:
#line 795 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_PRE_INC, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 103:
#line 799 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_PRE_DEC, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 104:
#line 806 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 105:
#line 810 "parserast.y"
    {
        (yyval.ast)=(yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 106:
#line 817 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 107:
#line 821 "parserast.y"
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (3)].str));
        (yyval.ast) = createBinaryNode((yyvsp[(2) - (3)].ast)->type, idNode, (yyvsp[(3) - (3)].ast));
        free((yyvsp[(2) - (3)].ast)); 
    ;}
    break;

  case 108:
#line 830 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_ASSIGN);
    ;}
    break;

  case 109:
#line 834 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_PLUS_ASSIGN);
    ;}
    break;

  case 110:
#line 838 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_MINUS_ASSIGN);
    ;}
    break;

  case 111:
#line 842 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_MULT_ASSIGN);
    ;}
    break;

  case 112:
#line 846 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_DIV_ASSIGN);
    ;}
    break;

  case 113:
#line 850 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_MOD_ASSIGN);
    ;}
    break;

  case 114:
#line 857 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the relational_expression as the left child of the equality expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 115:
#line 870 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 116:
#line 874 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_EQ, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 117:
#line 878 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_NE, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 118:
#line 885 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the additive_expression as the left child of the relational expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 119:
#line 898 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 120:
#line 902 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_LT, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 121:
#line 906 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_GT, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 122:
#line 910 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_LE, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 123:
#line 914 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_GE, NULL, (yyvsp[(2) - (2)].ast));
    ;}
    break;

  case 124:
#line 921 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the multiplicative expression as the left child of the additive expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 125:
#line 934 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 126:
#line 938 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_ADD, NULL, (yyvsp[(2) - (3)].ast));
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 127:
#line 948 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_SUB, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 128:
#line 962 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Set the unary expression as the left child of the multiplicative expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 129:
#line 975 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 130:
#line 979 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_MUL, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 131:
#line 990 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_DIV, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 132:
#line 1001 "parserast.y"
    {
        ASTNode* node = createBinaryNode(NODE_MOD, NULL, (yyvsp[(2) - (3)].ast));
        
        if ((yyvsp[(3) - (3)].ast)) {
            /* Chain the expressions */
            node->next = (yyvsp[(3) - (3)].ast);
        }
        
        (yyval.ast) = node;
    ;}
    break;

  case 133:
#line 1015 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(1) - (1)].ast);
    ;}
    break;

  case 134:
#line 1019 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_UNARY_PLUS, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 135:
#line 1023 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_UNARY_MINUS, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 136:
#line 1027 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_PRE_INC, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 137:
#line 1031 "parserast.y"
    {
        (yyval.ast) = createBinaryNode(NODE_PRE_DEC, (yyvsp[(2) - (2)].ast), NULL);
    ;}
    break;

  case 138:
#line 1038 "parserast.y"
    {
        if ((yyvsp[(2) - (2)].ast)) {
            /* Apply the postfix operator to the primary expression */
            (yyvsp[(2) - (2)].ast)->data.children.left = (yyvsp[(1) - (2)].ast);
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        }
    ;}
    break;

  case 139:
#line 1051 "parserast.y"
    {
        (yyval.ast) = NULL;
    ;}
    break;

  case 140:
#line 1055 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_POST_INC);
    ;}
    break;

  case 141:
#line 1059 "parserast.y"
    {
        (yyval.ast) = createNode(NODE_POST_DEC);
    ;}
    break;

  case 142:
#line 1066 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_IDENTIFIER, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 143:
#line 1070 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_INT_LITERAL, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 144:
#line 1074 "parserast.y"
    {
        (yyval.ast) = createStrNode(NODE_CHAR_LITERAL, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 145:
#line 1078 "parserast.y"
    {
        (yyval.ast) = (yyvsp[(2) - (3)].ast);
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2997 "parserast.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1083 "parserast.y"


void yyerror(const char *s) {
    syntax_errors++;
    if (!print_lexeme_token_pairs) {
        fprintf(stderr, "%s\n", s);
    }
    exit(1);
}

int main(int argc, char *argv[]) {
if (argc != 2) {
fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
return 1;
}
yyin = fopen(argv[1], "r");
if (!yyin) {
perror("Error opening file");
return 1;
}
yyparse();
fclose(yyin);
return 0;
}
