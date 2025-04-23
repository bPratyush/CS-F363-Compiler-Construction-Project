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
     OR = 302,
     AND = 303,
     NOT = 304,
     UNARY = 305,
     IFX = 306
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
#define OR 302
#define AND 303
#define NOT 304
#define UNARY 305
#define IFX 306




/* Copy the first part of user declarations.  */
#line 1 "threeac.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern FILE *yyin;
extern int yylineno;
void yyerror(const char *s);
int print_lexeme_token_pairs = 0;
extern char* symbolTable[256];
extern int symbolCount;
extern int suppress_lexer_output;
int syntax_errors = 0;
int semantic_errors = 0;
int output_printed = 0;
int temp_count = 0;
char* newtemp() {
    char *temp = (char *)malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}
int label_count = 0;
void semantic_error(const char* msg) {
    semantic_errors++;
}
char* newlabel() {
    char *lbl = (char *)malloc(10);
    sprintf(lbl, "L%d", label_count++);
    return lbl;
}
void add_variable(const char* id) {
    int i;
    for(i = 0; i < symbolCount; i++){
        if(symbolTable[i] && strcmp(symbolTable[i], id) == 0)
            return;
    }
    symbolTable[symbolCount++] = strdup(id);
}
int is_declared(const char* id) {
    int i;
    for(i = 0; i < symbolCount; i++){
        if(symbolTable[i] && strcmp(symbolTable[i], id)==0)
            return 1;
    }
    return 0;
}
void print_result() {
    if(!output_printed) {
      //  printf("I am Here\n");
    //    if(syntax_errors==0 && semantic_errors==0)
        //    printf("Successfully Parsed !!!\n");
  //      else
      //      printf("Syntax Error !!!\n");
        output_printed = 1;
    }
}
char *F_var, *F_end, *F_inc;
char *F_Lstart, *F_Lend;
char *F_tmpcond;
char *W_Lstart, *W_Lend, *W_tmpcond;


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
#line 63 "threeac.y"
{
    char *str;
    int num;
}
/* Line 193 of yacc.c.  */
#line 265 "threeac.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 278 "threeac.tab.c"

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
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

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
      45,    46,    47,    48,    49,    50,    51
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
     176,   177,   178,   188,   189,   190,   198,   199,   200,   216,
     217,   218,   232,   233,   235,   237,   239,   241,   243,   247,
     249,   251,   253,   255,   257,   259,   261,   263,   267,   271,
     275,   279,   283,   287,   289,   293,   297,   299,   303,   307,
     311,   313,   316,   319,   322,   325,   328,   329,   331,   333,
     335,   337,   339
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,     3,     5,     9,    54,     4,     5,    -1,
       1,    -1,    56,    -1,    56,    55,    -1,    60,    -1,     3,
      21,     9,    60,     4,    21,    -1,     3,     6,     9,    57,
       4,     6,    -1,     3,     6,     9,     4,     6,    -1,    58,
      -1,    57,    58,    -1,     1,    -1,    26,    22,    28,    59,
      27,    10,    -1,     7,    -1,     8,    -1,    22,    -1,    61,
      -1,    61,    60,    -1,    63,    -1,    64,    -1,    67,    -1,
      69,    -1,    70,    -1,    72,    -1,    62,    -1,    22,    37,
      23,    -1,    22,    34,    23,    -1,    22,    35,    23,    -1,
      22,    38,    23,    -1,    22,    36,    23,    -1,    22,    39,
      23,    -1,    82,    10,    -1,    10,    -1,    19,    26,    25,
      65,    27,    10,    -1,    -1,    28,    66,    -1,    82,    -1,
      66,    28,    82,    -1,    20,    26,    25,    28,    68,    27,
      10,    -1,    22,    -1,    68,    28,    22,    -1,    46,    60,
       4,    -1,    11,    71,    69,    10,    -1,    11,    71,    69,
      12,    69,    10,    -1,    11,    26,    86,    27,    69,    10,
      -1,    11,    26,    86,    27,    69,    12,    69,    10,    -1,
      23,    -1,    22,    -1,    62,    -1,    -1,    -1,    13,    26,
      82,    27,    15,    73,    69,    74,    10,    -1,    -1,    -1,
      13,    82,    15,    75,    69,    76,    10,    -1,    -1,    -1,
      14,    26,    22,    40,    82,    16,    82,    81,    82,    27,
      15,    77,    69,    78,    10,    -1,    -1,    -1,    14,    22,
      40,    82,    16,    82,    81,    82,    15,    79,    69,    80,
      10,    -1,    -1,    17,    -1,    18,    -1,    83,    -1,    62,
      -1,    85,    -1,    22,    84,    83,    -1,    40,    -1,    41,
      -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,    86,
      -1,    87,    -1,    87,    35,    87,    -1,    87,    36,    87,
      -1,    87,    37,    87,    -1,    87,    38,    87,    -1,    87,
      34,    87,    -1,    87,    39,    87,    -1,    88,    -1,    87,
      29,    88,    -1,    87,    30,    88,    -1,    89,    -1,    88,
      31,    89,    -1,    88,    32,    89,    -1,    88,    33,    89,
      -1,    90,    -1,    29,    89,    -1,    30,    89,    -1,    17,
      89,    -1,    18,    89,    -1,    92,    91,    -1,    -1,    17,
      -1,    18,    -1,    22,    -1,    23,    -1,    24,    -1,    26,
      82,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    98,   101,   102,   105,   106,   109,   110,
     113,   114,   115,   118,   121,   122,   123,   126,   127,   130,
     131,   132,   133,   134,   135,   136,   139,   148,   157,   167,
     176,   185,   196,   197,   200,   203,   204,   207,   208,   211,
     214,   221,   230,   233,   234,   235,   247,   268,   269,   277,
     283,   295,   282,   304,   314,   303,   322,   339,   321,   349,
     363,   348,   372,   373,   374,   377,   378,   381,   382,   402,
     405,   408,   411,   414,   417,   422,   425,   426,   431,   436,
     441,   446,   451,   458,   459,   464,   472,   473,   478,   483,
     490,   491,   492,   497,   498,   501,   504,   506,   509,   514,
     522,   523,   524
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
  "MOD_ASSIGN", "TK_BLOCKBEGIN", "OR", "AND", "NOT", "UNARY", "IFX",
  "$accept", "program", "program_body", "main_section", "var_decl_section",
  "var_decl_list", "var_decl", "type", "statement_list", "statement",
  "conditional_statement", "expression_statement", "print_statement",
  "optional_print_args", "print_arg_list", "scan_statement", "id_list",
  "compound_statement", "selection_statement", "ifexpr",
  "iteration_statement", "@1", "@2", "@3", "@4", "@5", "@6", "@7", "@8",
  "optional_inc", "expression", "assignment_expression",
  "assignment_operator", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "postfix_expression", "postfix_expression_tail", "primary_expression", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    57,    58,    59,    59,    59,    60,    60,    61,
      61,    61,    61,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    63,    63,    64,    65,    65,    66,    66,    67,
      68,    68,    69,    70,    70,    70,    70,    71,    71,    71,
      73,    74,    72,    75,    76,    72,    77,    78,    72,    79,
      80,    72,    81,    81,    81,    82,    82,    83,    83,    84,
      84,    84,    84,    84,    84,    85,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    87,    88,    88,    88,    88,
      89,    89,    89,    89,    89,    90,    91,    91,    91,    92,
      92,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     1,     1,     2,     1,     6,     6,     5,
       1,     2,     1,     6,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     6,     0,     2,     1,     3,     7,
       1,     3,     3,     4,     6,     6,     8,     1,     1,     1,
       0,     0,     9,     0,     0,     7,     0,     0,    15,     0,
       0,    13,     0,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     2,     2,     2,     0,     1,     1,     1,
       1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     0,     1,     0,     0,     0,     4,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,    99,   100,   101,     0,     0,     0,     0,     5,     6,
      17,    25,    19,    20,    21,    22,    23,    24,     0,    65,
      67,    75,    76,    83,    86,    90,    96,     0,     2,     0,
      48,    47,     0,    49,     0,     0,    66,     0,     0,     0,
      99,    93,    94,     0,     0,     0,     0,     0,     0,     0,
       0,    69,    70,    71,    72,    73,    74,     0,     0,    91,
      92,     0,    18,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    98,    95,    12,     0,
       0,     0,    10,     0,     0,     0,     0,    53,     0,     0,
      35,     0,    27,    28,    30,    26,    29,    31,    99,    68,
     102,    42,    84,    85,    81,    77,    78,    79,    80,    82,
      87,    88,    89,     9,     0,     0,    11,     0,     0,    43,
       0,   102,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     0,     0,    50,    54,     0,     0,    36,    37,     0,
      40,     0,    14,    15,    16,     0,     7,    45,     0,    44,
       0,     0,    62,     0,     0,    34,     0,     0,     0,     0,
      51,    55,    63,    64,     0,    62,    38,    39,    41,    13,
      46,     0,     0,     0,    52,    59,     0,     0,     0,    60,
      56,     0,     0,    61,    57,     0,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     8,    28,     9,   101,   102,   165,    29,    30,
      56,    32,    33,   146,   157,    34,   161,    35,    36,    54,
      37,   170,   191,   142,   171,   202,   205,   197,   201,   184,
      38,    39,    77,    40,    41,    42,    43,    44,    45,    97,
      46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int16 yypact[] =
{
      12,   -54,    14,    24,    39,   -54,    48,    61,    53,    15,
      62,    78,    67,   -54,    51,    46,   -16,    77,    77,    79,
      84,   145,   -54,   -54,    96,    77,    77,    36,   -54,   -54,
      36,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   106,   -54,
     -54,   -54,    98,    59,   -54,   -54,     4,    26,   -54,   112,
     126,   -54,    77,   -54,    85,    96,   -54,   108,    99,   102,
     -54,   -54,   -54,   113,   118,   122,   128,   129,   132,   133,
     134,   -54,   -54,   -54,   -54,   -54,   -54,   124,   139,   -54,
     -54,   163,   -54,   -54,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,   -54,   -54,   -54,   -54,   162,
     154,    10,   -54,    36,   150,    74,   170,   -54,    96,   158,
     171,   172,   -54,   -54,   -54,   -54,   -54,   -54,   130,   -54,
     -54,   -54,    59,    59,    13,    13,    13,    13,    13,    13,
     -54,   -54,   -54,   -54,   173,   196,   -54,   199,    85,   -54,
      85,   189,    85,   190,    96,    96,   178,   185,     9,   -54,
     187,    92,   200,   -54,   -54,    96,   193,   183,   -54,   202,
     -54,    70,   -54,   -54,   -54,   186,   -54,   -54,    85,   -54,
      85,   204,    91,    96,    96,   -54,   205,   194,   207,   208,
     -54,   -54,   -54,   -54,    96,    91,   -54,   -54,   -54,   -54,
     -54,   209,   206,    96,   -54,   -54,   195,    85,   210,   -54,
     -54,   213,    85,   -54,   -54,   214,   -54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   -54,   -54,   -54,   -54,   119,   -54,   -22,   -54,
      -7,   -54,   -54,   -54,   -54,   -54,   -54,   -53,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,    41,
     -15,   151,   -54,   -54,   175,   105,    27,   -14,   -54,   -54,
     -54
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      57,   105,    31,    61,    62,    81,    58,    53,    82,    78,
      59,    79,    80,     1,   135,     2,   162,   163,    12,     4,
      31,    95,    96,    31,     5,    13,    14,    98,    15,    16,
      99,   164,    17,    18,    19,    20,   100,    21,    22,    23,
     106,    24,    84,    85,    25,    26,    13,    14,     6,    15,
      16,     7,   100,    17,    18,    19,    20,    11,    21,    22,
      23,    27,    24,    17,    18,    25,    26,    10,    21,    22,
      23,    47,    55,    50,    51,    25,    26,    52,   130,   131,
     132,   137,    27,    48,   139,   151,   140,   152,    49,   154,
      92,    93,    94,   143,    17,    18,    31,   176,   177,    60,
      22,    23,   167,    24,   168,    63,    25,    26,   182,   183,
      64,   122,   123,    17,    18,   179,    83,   180,    21,    22,
      23,   103,    24,   107,   109,    25,    26,    84,    85,   156,
     158,    27,    86,    87,    88,    89,    90,    91,   110,   108,
     172,    17,    18,   111,   199,   112,   118,    22,    23,   204,
      24,   113,   114,    25,    26,   115,   116,   117,   185,   186,
      65,    66,    67,    68,    69,    70,   120,   121,   133,   192,
      71,    72,    73,    74,    75,    76,   134,   138,   196,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,   124,   125,   126,   127,   128,   129,   141,   144,   145,
     147,   148,   149,   150,   153,   159,   155,   160,   166,   173,
     169,   174,   175,   178,   181,   187,   188,   189,   190,   194,
     136,   195,   198,   203,   206,   200,   193,   104,   119
};

static const yytype_uint8 yycheck[] =
{
      15,    54,     9,    17,    18,    27,    22,    14,    30,    24,
      26,    25,    26,     1,     4,     3,     7,     8,     3,     5,
      27,    17,    18,    30,     0,    10,    11,     1,    13,    14,
       4,    22,    17,    18,    19,    20,    26,    22,    23,    24,
      55,    26,    29,    30,    29,    30,    10,    11,     9,    13,
      14,     3,    26,    17,    18,    19,    20,     4,    22,    23,
      24,    46,    26,    17,    18,    29,    30,     6,    22,    23,
      24,     9,    26,    22,    23,    29,    30,    26,    92,    93,
      94,   103,    46,     5,    10,   138,    12,   140,    21,   142,
      31,    32,    33,   108,    17,    18,   103,    27,    28,    22,
      23,    24,    10,    26,    12,    26,    29,    30,    17,    18,
      26,    84,    85,    17,    18,   168,    10,   170,    22,    23,
      24,     9,    26,    15,    22,    29,    30,    29,    30,   144,
     145,    46,    34,    35,    36,    37,    38,    39,    25,    40,
     155,    17,    18,    25,   197,    23,    22,    23,    24,   202,
      26,    23,    23,    29,    30,    23,    23,    23,   173,   174,
      34,    35,    36,    37,    38,    39,    27,     4,     6,   184,
      40,    41,    42,    43,    44,    45,    22,    27,   193,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    86,    87,    88,    89,    90,    91,    27,    40,    28,
      28,    28,     6,     4,    15,    27,    16,    22,    21,    16,
      10,    28,    10,    27,    10,    10,    22,    10,    10,    10,
     101,    15,    27,    10,    10,    15,   185,    52,    77
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    53,     5,     0,     9,     3,    54,    56,
       6,     4,     3,    10,    11,    13,    14,    17,    18,    19,
      20,    22,    23,    24,    26,    29,    30,    46,    55,    60,
      61,    62,    63,    64,    67,    69,    70,    72,    82,    83,
      85,    86,    87,    88,    89,    90,    92,     9,     5,    21,
      22,    23,    26,    62,    71,    26,    62,    82,    22,    26,
      22,    89,    89,    26,    26,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    84,    82,    89,
      89,    60,    60,    10,    29,    30,    34,    35,    36,    37,
      38,    39,    31,    32,    33,    17,    18,    91,     1,     4,
      26,    57,    58,     9,    86,    69,    82,    15,    40,    22,
      25,    25,    23,    23,    23,    23,    23,    23,    22,    83,
      27,     4,    88,    88,    87,    87,    87,    87,    87,    87,
      89,    89,    89,     6,    22,     4,    58,    60,    27,    10,
      12,    27,    75,    82,    40,    28,    65,    28,    28,     6,
       4,    69,    69,    15,    69,    16,    82,    66,    82,    27,
      22,    68,     7,     8,    22,    59,    21,    10,    12,    10,
      73,    76,    82,    16,    28,    10,    27,    28,    27,    69,
      69,    10,    17,    18,    81,    82,    82,    10,    22,    10,
      10,    74,    82,    81,    10,    15,    82,    79,    27,    69,
      15,    80,    77,    10,    69,    78,    10
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
#line 97 "threeac.y"
    { print_result(); ;}
    break;

  case 3:
#line 98 "threeac.y"
    { yyerrok; print_result(); YYABORT; ;}
    break;

  case 8:
#line 109 "threeac.y"
    { ;}
    break;

  case 9:
#line 110 "threeac.y"
    { ;}
    break;

  case 12:
#line 115 "threeac.y"
    { yyerrok; syntax_errors++; printf("Syntax Error !!!\n"); return 0; ;}
    break;

  case 13:
#line 118 "threeac.y"
    { add_variable((yyvsp[(2) - (6)].str)); ;}
    break;

  case 14:
#line 121 "threeac.y"
    { ;}
    break;

  case 15:
#line 122 "threeac.y"
    { ;}
    break;

  case 16:
#line 123 "threeac.y"
    { yyerror("Invalid data type"); ;}
    break;

  case 17:
#line 126 "threeac.y"
    { ;}
    break;

  case 18:
#line 127 "threeac.y"
    { ;}
    break;

  case 19:
#line 130 "threeac.y"
    { ;}
    break;

  case 20:
#line 131 "threeac.y"
    { ;}
    break;

  case 21:
#line 132 "threeac.y"
    { ;}
    break;

  case 22:
#line 133 "threeac.y"
    { ;}
    break;

  case 23:
#line 134 "threeac.y"
    { ;}
    break;

  case 24:
#line 135 "threeac.y"
    { ;}
    break;

  case 25:
#line 136 "threeac.y"
    { ;}
    break;

  case 26:
#line 139 "threeac.y"
    {
         char*c = strcat((yyvsp[(1) - (3)].str) , (yyvsp[(2) - (3)].str));
         (yyval.str) = strcat(c , (yyvsp[(3) - (3)].str));
         if(!is_declared((yyvsp[(1) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 27:
#line 148 "threeac.y"
    {
         char*c = strcat((yyvsp[(1) - (3)].str) , (yyvsp[(2) - (3)].str));
         (yyval.str) = strcat(c , (yyvsp[(3) - (3)].str));
         if(!is_declared((yyvsp[(1) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 28:
#line 157 "threeac.y"
    {
       //  printf("DEBUG: %s   GT\n" , $3);
         char*c = strcat((yyvsp[(1) - (3)].str) , (yyvsp[(2) - (3)].str));
         (yyval.str) = strcat(c , (yyvsp[(3) - (3)].str));
         if(!is_declared((yyvsp[(1) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 29:
#line 167 "threeac.y"
    {
         char*c = strcat((yyvsp[(1) - (3)].str) , (yyvsp[(2) - (3)].str));
         (yyval.str) = strcat(c , (yyvsp[(3) - (3)].str));
         if(!is_declared((yyvsp[(1) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 30:
#line 176 "threeac.y"
    {
         char*c = strcat((yyvsp[(1) - (3)].str) , (yyvsp[(2) - (3)].str));
         (yyval.str) = strcat(c , (yyvsp[(3) - (3)].str));
         if(!is_declared((yyvsp[(1) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 31:
#line 185 "threeac.y"
    {
         char*c = strcat((yyvsp[(1) - (3)].str) , (yyvsp[(2) - (3)].str));
         (yyval.str) = strcat(c , (yyvsp[(3) - (3)].str));
         if(!is_declared((yyvsp[(1) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 32:
#line 196 "threeac.y"
    { ;}
    break;

  case 33:
#line 197 "threeac.y"
    { ;}
    break;

  case 34:
#line 200 "threeac.y"
    { ;}
    break;

  case 35:
#line 203 "threeac.y"
    { ;}
    break;

  case 36:
#line 204 "threeac.y"
    { ;}
    break;

  case 37:
#line 207 "threeac.y"
    { ;}
    break;

  case 38:
#line 208 "threeac.y"
    { ;}
    break;

  case 39:
#line 211 "threeac.y"
    { ;}
    break;

  case 40:
#line 214 "threeac.y"
    {
         if(!is_declared((yyvsp[(1) - (1)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (1)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 41:
#line 221 "threeac.y"
    {
         if(!is_declared((yyvsp[(3) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(3) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 42:
#line 230 "threeac.y"
    { ;}
    break;

  case 45:
#line 236 "threeac.y"
    {
        char *L1 = newlabel();
        
        printf("t1 := %s\n", (yyvsp[(3) - (6)].str));
       
        printf("if t1 goto %s\n", L1);
       
        printf("%s:\n", L1);
        
    ;}
    break;

  case 46:
#line 249 "threeac.y"
    {
        char *L1 = newlabel();
        char *L2 = newlabel();
        
        printf("t1 := %s\n", (yyvsp[(3) - (8)].str));
        printf("if t1 goto %s\n", L1);
       
        printf("goto %s\n", L2);
        
        printf("%s:\n", L1);
        
        printf("goto %s\n", L2);
       
        printf("%s:\n", L2);
        
    ;}
    break;

  case 47:
#line 268 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 48:
#line 269 "threeac.y"
    {
         if(!is_declared((yyvsp[(1) - (1)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (1)].str));
            semantic_error(err);
         }
         (yyval.str) = (yyvsp[(1) - (1)].str);
     ;}
    break;

  case 49:
#line 277 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 50:
#line 283 "threeac.y"
    {
    /* 1) make labels and temp */
    W_Lstart = newlabel();
    W_Lend   = newlabel();
    W_tmpcond= newtemp();

    /* 2) emit loop‐entry and test */
    printf("%s:\n",             W_Lstart);
    printf("%s := %s\n",         W_tmpcond, (yyvsp[(3) - (5)].str));
    printf("if %s := 0 goto %s\n", W_tmpcond, W_Lend);
  ;}
    break;

  case 51:
#line 295 "threeac.y"
    {
    /* 3) after body, jump back + end label */
    printf("goto %s\n", W_Lstart);
    printf("%s:\n",     W_Lend);
  ;}
    break;

  case 53:
#line 304 "threeac.y"
    {
    W_Lstart = newlabel();
    W_Lend   = newlabel();
    W_tmpcond= newtemp();

    printf("%s:\n",             W_Lstart);
    printf("%s := %s\n",         W_tmpcond, (yyvsp[(2) - (3)].str));
    printf("if %s := 0 goto %s\n", W_tmpcond, W_Lend);
  ;}
    break;

  case 54:
#line 314 "threeac.y"
    {
    printf("goto %s\n", W_Lstart);
    printf("%s:\n",     W_Lend);
  ;}
    break;

  case 56:
#line 322 "threeac.y"
    {

      F_var    = (yyvsp[(3) - (11)].str);                /* loop variable */
      F_end    = (yyvsp[(7) - (11)].str);                /* upper bound */
      F_inc    = (yyvsp[(8) - (11)].str) ? (yyvsp[(9) - (11)].str) : "1";     /* optional step */
    
      F_Lstart = newlabel();
      F_Lend   = newlabel();
      F_tmpcond= newtemp();
   
      printf("%s := %s\n", F_var, (yyvsp[(5) - (11)].str));    /* var = lower */
      printf("%s:\n",    F_Lstart);      /* Lstart: */
    
      printf("%s := %s > %s\n", F_tmpcond,   F_var , F_end);
      printf("if %s == 1 goto %s\n", F_tmpcond, F_Lend);
    ;}
    break;

  case 57:
#line 339 "threeac.y"
    {
      /* 5) after the body, emit increment/jump/end */
      printf("%s := %s + %s\n", F_var, F_var, F_inc);
      printf("goto %s\n",     F_Lstart);
      printf("%s:\n",         F_Lend);
    ;}
    break;

  case 59:
#line 349 "threeac.y"
    {
      /* same as above but shift the $‑indices down by one */
      F_var    = (yyvsp[(2) - (9)].str);
      F_end    = (yyvsp[(6) - (9)].str);
      F_inc    = (yyvsp[(7) - (9)].str) ? (yyvsp[(8) - (9)].str) : "1";
      F_Lstart = newlabel();
      F_Lend   = newlabel();
      F_tmpcond= newtemp();
      printf("%s := %s\n", F_var, (yyvsp[(4) - (9)].str));
      printf("%s:\n",    F_Lstart);
      printf("%s := %s > %s\n", F_tmpcond,  F_var , F_end);
      printf("if %s == 1 goto %s\n", F_tmpcond, F_Lend);
    ;}
    break;

  case 60:
#line 363 "threeac.y"
    {
      printf("%s := %s + %s\n", F_var, F_var, F_inc);
      printf("goto %s\n",     F_Lstart);
      printf("%s:\n",         F_Lend);
    ;}
    break;

  case 62:
#line 372 "threeac.y"
    { ;}
    break;

  case 63:
#line 373 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);  ;}
    break;

  case 64:
#line 374 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 65:
#line 377 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 66:
#line 378 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 67:
#line 381 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 68:
#line 382 "threeac.y"
    {
         if(!is_declared((yyvsp[(1) - (3)].str))){
             char err[100];
             snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (3)].str));
             semantic_error(err);
         }
         if((yyvsp[(3) - (3)].str) && (yyvsp[(3) - (3)].str)[0]=='(') {
             int val, base;
             if(sscanf((yyvsp[(3) - (3)].str), "(%d,%d)", &val, &base)==2) {
                 printf("%s := %s\n", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
             } else {
                 printf("%s := %s\n", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
             }
         } else {
             printf("%s := %s\n", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         }
         (yyval.str) = (yyvsp[(1) - (3)].str);
     ;}
    break;

  case 69:
#line 403 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 70:
#line 406 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 71:
#line 409 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 72:
#line 412 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 73:
#line 415 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 74:
#line 418 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 75:
#line 422 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 76:
#line 425 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 77:
#line 426 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s > %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 78:
#line 431 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s < %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 79:
#line 436 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s >= %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 80:
#line 441 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s <= %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 81:
#line 446 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s == %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 82:
#line 451 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s != %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 83:
#line 458 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 84:
#line 459 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s + %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 85:
#line 464 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s - %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 86:
#line 472 "threeac.y"
    {  ;}
    break;

  case 87:
#line 473 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s * %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 88:
#line 478 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s / %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 89:
#line 483 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s %% %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 90:
#line 490 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 91:
#line 491 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 92:
#line 492 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := 0 - %s\n", temp, (yyvsp[(2) - (2)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 93:
#line 497 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 94:
#line 498 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 95:
#line 501 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (2)].str); ;}
    break;

  case 96:
#line 504 "threeac.y"
    {
    ;}
    break;

  case 97:
#line 507 "threeac.y"
    {
    ;}
    break;

  case 98:
#line 510 "threeac.y"
    {
    ;}
    break;

  case 99:
#line 514 "threeac.y"
    {
         if(!is_declared((yyvsp[(1) - (1)].str))){
             char err[100];
             snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (1)].str));
             semantic_error(err);
         }
         (yyval.str) = (yyvsp[(1) - (1)].str);
     ;}
    break;

  case 100:
#line 522 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 101:
#line 523 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 102:
#line 524 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (3)].str); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2348 "threeac.tab.c"
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


#line 526 "threeac.y"

void yyerror(const char *s) { syntax_errors++; }
int main(int argc, char *argv[]) {
    if(argc != 2) {
         fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
         return 1;
    }
    yyin = fopen(argv[1], "r");
    if(!yyin) { perror("Error opening file"); return 1; }
    print_lexeme_token_pairs = 0;
    output_printed = 0;
    syntax_errors = 0;
    semantic_errors = 0;
    temp_count = 0;
    label_count = 0;
    yyparse();
    fclose(yyin);
    return 0;
}
