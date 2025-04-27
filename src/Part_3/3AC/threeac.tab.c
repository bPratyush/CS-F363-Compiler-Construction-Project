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
int for_flag = -1;
char *if_dum;
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
typedef struct {
    char *L_else;
    char *L_end;
} LabelPair;

LabelPair label_stack[10];
int label_stack_ptr = -1;

void push_labels(char *L_else, char *L_end) {
    label_stack[++label_stack_ptr] = (LabelPair){L_else, L_end};
}

LabelPair pop_labels() {
    return label_stack[label_stack_ptr--];
}
char *F_var, *F_end, *F_inc;
char *F_Lstart, *F_Lend;
char *F_tmpcond;
char *W_Lstart, *W_Lend, *W_tmpcond;
char* L_else , *L_end;


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
#line 81 "threeac.y"
{
    char *str;
    int num;
}
/* Line 193 of yacc.c.  */
#line 283 "threeac.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 296 "threeac.tab.c"

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
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

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
     132,   134,   138,   142,   143,   151,   152,   156,   157,   158,
     159,   169,   170,   171,   179,   180,   181,   197,   198,   199,
     213,   214,   216,   218,   220,   222,   224,   228,   230,   232,
     234,   236,   238,   240,   242,   244,   248,   252,   256,   260,
     264,   268,   270,   274,   278,   280,   284,   288,   292,   294,
     297,   300,   303,   306,   309,   310,   312,   314,   316,   318,
     320
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
      69,    -1,    70,    -1,    74,    -1,    62,    -1,    22,    37,
      23,    -1,    22,    34,    23,    -1,    22,    35,    23,    -1,
      22,    38,    23,    -1,    22,    36,    23,    -1,    22,    39,
      23,    -1,    84,    10,    -1,    10,    -1,    19,    26,    25,
      65,    27,    10,    -1,    -1,    28,    66,    -1,    84,    -1,
      66,    28,    84,    -1,    20,    26,    25,    28,    68,    27,
      10,    -1,    22,    -1,    68,    28,    22,    -1,    46,    60,
       4,    -1,    -1,    11,    26,    84,    27,    71,    69,    72,
      -1,    -1,    12,    73,    69,    -1,    -1,    -1,    -1,    13,
      26,    84,    27,    15,    75,    69,    76,    10,    -1,    -1,
      -1,    13,    84,    15,    77,    69,    78,    10,    -1,    -1,
      -1,    14,    26,    22,    40,    84,    16,    84,    83,    84,
      27,    15,    79,    69,    80,    10,    -1,    -1,    -1,    14,
      22,    40,    84,    16,    84,    83,    84,    15,    81,    69,
      82,    10,    -1,    -1,    17,    -1,    18,    -1,    85,    -1,
      62,    -1,    87,    -1,    22,    86,    85,    -1,    40,    -1,
      41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,
      88,    -1,    89,    -1,    89,    35,    89,    -1,    89,    36,
      89,    -1,    89,    37,    89,    -1,    89,    38,    89,    -1,
      89,    34,    89,    -1,    89,    39,    89,    -1,    90,    -1,
      89,    29,    90,    -1,    89,    30,    90,    -1,    91,    -1,
      90,    31,    91,    -1,    90,    32,    91,    -1,    90,    33,
      91,    -1,    92,    -1,    29,    91,    -1,    30,    91,    -1,
      17,    91,    -1,    18,    91,    -1,    94,    93,    -1,    -1,
      17,    -1,    18,    -1,    22,    -1,    23,    -1,    24,    -1,
      26,    84,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   114,   114,   116,   119,   120,   123,   124,   127,   128,
     131,   132,   133,   136,   139,   140,   141,   144,   145,   148,
     149,   150,   151,   152,   153,   154,   157,   166,   175,   185,
     194,   203,   214,   215,   218,   221,   222,   225,   226,   229,
     232,   239,   248,   252,   251,   266,   265,   280,   305,   317,
     304,   326,   336,   325,   345,   370,   344,   385,   409,   384,
     425,   426,   427,   430,   431,   434,   435,   455,   458,   461,
     464,   467,   470,   475,   478,   479,   484,   489,   494,   499,
     504,   511,   512,   517,   525,   526,   531,   536,   543,   544,
     545,   550,   551,   554,   557,   559,   563,   569,   577,   578,
     579
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
  "compound_statement", "selection_statement", "@1", "optional_else", "@2",
  "iteration_statement", "@3", "@4", "@5", "@6", "@7", "@8", "@9", "@10",
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
      68,    68,    69,    71,    70,    73,    72,    72,    75,    76,
      74,    77,    78,    74,    79,    80,    74,    81,    82,    74,
      83,    83,    83,    84,    84,    85,    85,    86,    86,    86,
      86,    86,    86,    87,    88,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    90,    90,    90,    90,    91,    91,
      91,    91,    91,    92,    93,    93,    93,    94,    94,    94,
      94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     1,     1,     2,     1,     6,     6,     5,
       1,     2,     1,     6,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     6,     0,     2,     1,     3,     7,
       1,     3,     3,     0,     7,     0,     3,     0,     0,     0,
       9,     0,     0,     7,     0,     0,    15,     0,     0,    13,
       0,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     2,     2,     0,     1,     1,     1,     1,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     0,     1,     0,     0,     0,     4,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,    97,    98,    99,     0,     0,     0,     0,     5,     6,
      17,    25,    19,    20,    21,    22,    23,    24,     0,    63,
      65,    73,    74,    81,    84,    88,    94,     0,     2,     0,
       0,     0,    64,     0,     0,     0,    97,    91,    92,     0,
       0,     0,     0,     0,     0,     0,     0,    67,    68,    69,
      70,    71,    72,     0,     0,    89,    90,     0,    18,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    95,    96,    93,    12,     0,     0,     0,    10,     0,
       0,     0,    51,     0,     0,    35,     0,    27,    28,    30,
      26,    29,    31,    97,    66,   100,    42,    82,    83,    79,
      75,    76,    77,    78,    80,    85,    86,    87,     9,     0,
       0,    11,     0,    43,   100,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,    48,    52,     0,     0,    36,
      37,     0,    40,     0,    14,    15,    16,     0,     7,    47,
       0,     0,    60,     0,     0,    34,     0,     0,     0,    45,
      44,    49,    53,    61,    62,     0,    60,    38,    39,    41,
      13,     0,     0,     0,     0,    46,    50,    57,     0,     0,
       0,    58,    54,     0,     0,    59,    55,     0,    56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     8,    28,     9,    97,    98,   157,    29,    30,
      52,    32,    33,   139,   149,    34,   153,    35,    36,   144,
     170,   181,    37,   160,   182,   135,   161,   194,   197,   189,
     193,   175,    38,    39,    73,    40,    41,    42,    43,    44,
      45,    93,    46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -130
static const yytype_int16 yypact[] =
{
      13,  -130,    18,    29,     9,  -130,    36,    37,    44,    27,
      54,    59,    51,  -130,    61,    89,    -9,   111,   111,    68,
      69,   136,  -130,  -130,   121,   111,   111,    79,  -130,  -130,
      79,  -130,  -130,  -130,  -130,  -130,  -130,  -130,    90,  -130,
    -130,  -130,    32,    53,  -130,  -130,     3,     6,  -130,    95,
     121,   121,  -130,    99,    70,    94,  -130,  -130,  -130,    92,
      96,    97,   101,   103,   104,   107,   108,  -130,  -130,  -130,
    -130,  -130,  -130,   135,   109,  -130,  -130,   138,  -130,  -130,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,  -130,  -130,  -130,  -130,   140,   132,    -2,  -130,    79,
     128,   129,  -130,   121,   122,   139,   160,  -130,  -130,  -130,
    -130,  -130,  -130,    38,  -130,  -130,  -130,    53,    53,    -4,
      -4,    -4,    -4,    -4,    -4,  -130,  -130,  -130,  -130,   161,
     157,  -130,   162,  -130,   153,   144,   175,   121,   121,   165,
     171,    20,  -130,   173,   144,  -130,  -130,   121,   179,   168,
    -130,   187,  -130,    31,  -130,  -130,  -130,   172,  -130,   186,
     144,   190,    16,   121,   121,  -130,   191,   180,   193,  -130,
    -130,  -130,  -130,  -130,  -130,   121,    16,  -130,  -130,  -130,
    -130,   144,   194,   192,   121,  -130,  -130,  -130,   178,   144,
     195,  -130,  -130,   196,   144,  -130,  -130,   198,  -130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,  -130,  -130,  -130,   112,  -130,   -22,  -130,
      -8,  -130,  -130,  -130,  -130,  -130,  -130,  -129,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,    35,   -15,   141,  -130,  -130,  -130,   100,   -26,   -14,
    -130,  -130,  -130
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      53,    31,   130,    57,    58,    77,   146,    94,    78,    74,
      95,    75,    76,    54,     1,   159,     2,    55,     6,    31,
      91,    92,    31,     4,    96,    80,    81,   154,   155,     5,
      12,   171,    96,   173,   174,   100,   101,    13,    14,     7,
      15,    16,   156,    10,    17,    18,    19,    20,    11,    21,
      22,    23,   185,    24,   117,   118,    25,    26,   166,   167,
     191,    80,    81,    47,    48,   196,    82,    83,    84,    85,
      86,    87,    49,    27,   125,   126,   127,   132,    67,    68,
      69,    70,    71,    72,    88,    89,    90,    50,   136,    13,
      14,    31,    15,    16,    59,    60,    17,    18,    19,    20,
      79,    21,    22,    23,    99,    24,    17,    18,    25,    26,
     103,    21,    22,    23,   102,    51,   104,   105,    25,    26,
     107,   106,   148,   150,   108,    27,   109,   110,    17,    18,
     111,   112,   162,    56,    22,    23,   115,    24,    17,    18,
      25,    26,   116,    21,    22,    23,   128,    24,   176,   177,
      25,    26,    17,    18,   129,   133,   134,   113,    22,    23,
     183,    24,   137,   142,    25,    26,   143,   138,   145,   188,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,   119,   120,   121,   122,   123,   124,   140,   141,
      27,   147,   151,   152,   158,   163,   164,   165,   169,   168,
     172,   178,   179,   180,   186,   190,   195,   187,   198,   131,
     192,   184,     0,     0,   114
};

static const yytype_int16 yycheck[] =
{
      15,     9,     4,    17,    18,    27,   135,     1,    30,    24,
       4,    25,    26,    22,     1,   144,     3,    26,     9,    27,
      17,    18,    30,     5,    26,    29,    30,     7,     8,     0,
       3,   160,    26,    17,    18,    50,    51,    10,    11,     3,
      13,    14,    22,     6,    17,    18,    19,    20,     4,    22,
      23,    24,   181,    26,    80,    81,    29,    30,    27,    28,
     189,    29,    30,     9,     5,   194,    34,    35,    36,    37,
      38,    39,    21,    46,    88,    89,    90,    99,    40,    41,
      42,    43,    44,    45,    31,    32,    33,    26,   103,    10,
      11,    99,    13,    14,    26,    26,    17,    18,    19,    20,
      10,    22,    23,    24,     9,    26,    17,    18,    29,    30,
      40,    22,    23,    24,    15,    26,    22,    25,    29,    30,
      23,    25,   137,   138,    23,    46,    23,    23,    17,    18,
      23,    23,   147,    22,    23,    24,    27,    26,    17,    18,
      29,    30,     4,    22,    23,    24,     6,    26,   163,   164,
      29,    30,    17,    18,    22,    27,    27,    22,    23,    24,
     175,    26,    40,     6,    29,    30,     4,    28,    15,   184,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    82,    83,    84,    85,    86,    87,    28,    28,
      46,    16,    27,    22,    21,    16,    28,    10,    12,    27,
      10,    10,    22,    10,    10,    27,    10,    15,    10,    97,
      15,   176,    -1,    -1,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    53,     5,     0,     9,     3,    54,    56,
       6,     4,     3,    10,    11,    13,    14,    17,    18,    19,
      20,    22,    23,    24,    26,    29,    30,    46,    55,    60,
      61,    62,    63,    64,    67,    69,    70,    74,    84,    85,
      87,    88,    89,    90,    91,    92,    94,     9,     5,    21,
      26,    26,    62,    84,    22,    26,    22,    91,    91,    26,
      26,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    86,    84,    91,    91,    60,    60,    10,
      29,    30,    34,    35,    36,    37,    38,    39,    31,    32,
      33,    17,    18,    93,     1,     4,    26,    57,    58,     9,
      84,    84,    15,    40,    22,    25,    25,    23,    23,    23,
      23,    23,    23,    22,    85,    27,     4,    90,    90,    89,
      89,    89,    89,    89,    89,    91,    91,    91,     6,    22,
       4,    58,    60,    27,    27,    77,    84,    40,    28,    65,
      28,    28,     6,     4,    71,    15,    69,    16,    84,    66,
      84,    27,    22,    68,     7,     8,    22,    59,    21,    69,
      75,    78,    84,    16,    28,    10,    27,    28,    27,    12,
      72,    69,    10,    17,    18,    83,    84,    84,    10,    22,
      10,    73,    76,    84,    83,    69,    10,    15,    84,    81,
      27,    69,    15,    82,    79,    10,    69,    80,    10
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
#line 115 "threeac.y"
    { print_result(); ;}
    break;

  case 3:
#line 116 "threeac.y"
    { yyerrok; print_result(); YYABORT; ;}
    break;

  case 8:
#line 127 "threeac.y"
    { ;}
    break;

  case 9:
#line 128 "threeac.y"
    { ;}
    break;

  case 12:
#line 133 "threeac.y"
    { yyerrok; syntax_errors++; printf("Syntax Error !!!\n"); return 0; ;}
    break;

  case 13:
#line 136 "threeac.y"
    { add_variable((yyvsp[(2) - (6)].str)); ;}
    break;

  case 14:
#line 139 "threeac.y"
    { ;}
    break;

  case 15:
#line 140 "threeac.y"
    { ;}
    break;

  case 16:
#line 141 "threeac.y"
    { yyerror("Invalid data type"); ;}
    break;

  case 17:
#line 144 "threeac.y"
    { ;}
    break;

  case 18:
#line 145 "threeac.y"
    { ;}
    break;

  case 19:
#line 148 "threeac.y"
    { ;}
    break;

  case 20:
#line 149 "threeac.y"
    { ;}
    break;

  case 21:
#line 150 "threeac.y"
    { ;}
    break;

  case 22:
#line 151 "threeac.y"
    { ;}
    break;

  case 23:
#line 152 "threeac.y"
    { ;}
    break;

  case 24:
#line 153 "threeac.y"
    { ;}
    break;

  case 25:
#line 154 "threeac.y"
    { ;}
    break;

  case 26:
#line 157 "threeac.y"
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
#line 166 "threeac.y"
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
#line 175 "threeac.y"
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

  case 30:
#line 194 "threeac.y"
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
#line 203 "threeac.y"
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
#line 214 "threeac.y"
    { ;}
    break;

  case 33:
#line 215 "threeac.y"
    { ;}
    break;

  case 34:
#line 218 "threeac.y"
    { ;}
    break;

  case 35:
#line 221 "threeac.y"
    { ;}
    break;

  case 36:
#line 222 "threeac.y"
    { ;}
    break;

  case 37:
#line 225 "threeac.y"
    { ;}
    break;

  case 38:
#line 226 "threeac.y"
    { ;}
    break;

  case 39:
#line 229 "threeac.y"
    { ;}
    break;

  case 40:
#line 232 "threeac.y"
    {
         if(!is_declared((yyvsp[(1) - (1)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (1)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 41:
#line 239 "threeac.y"
    {
         if(!is_declared((yyvsp[(3) - (3)].str))){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(3) - (3)].str));
            semantic_error(err);
         }
    ;}
    break;

  case 42:
#line 248 "threeac.y"
    { ;}
    break;

  case 43:
#line 252 "threeac.y"
    {
        char *L_else = newlabel();
        char *L_end = newlabel();
        push_labels(L_else, L_end);

        printf("t1 := %s\n", (yyvsp[(3) - (4)].str));
        printf("if t1 == 0 goto %s\n", L_else);
    ;}
    break;

  case 45:
#line 266 "threeac.y"
    {
        LabelPair current = label_stack[label_stack_ptr];
        printf("goto %s\n", current.L_end);
        printf("%s:\n", current.L_else);
    ;}
    break;

  case 46:
#line 272 "threeac.y"
    {
        LabelPair current = pop_labels();
        printf("%s:\n", current.L_end);
        free(current.L_else);
        free(current.L_end);
    ;}
    break;

  case 47:
#line 280 "threeac.y"
    {
        LabelPair current = pop_labels();
        printf("%s:\n", current.L_else);
        free(current.L_else);
        free(current.L_end);
    ;}
    break;

  case 48:
#line 305 "threeac.y"
    {
    
    W_Lstart = newlabel();
    W_Lend   = newlabel();
    W_tmpcond= newtemp();

    
    printf("%s:\n",             W_Lstart);
    printf("%s := %s\n",         W_tmpcond, (yyvsp[(3) - (5)].str));
    printf("if %s := 0 goto %s\n", W_tmpcond, W_Lend);
  ;}
    break;

  case 49:
#line 317 "threeac.y"
    {
   
    printf("goto %s\n", W_Lstart);
    printf("%s:\n",     W_Lend);
  ;}
    break;

  case 51:
#line 326 "threeac.y"
    {
    W_Lstart = newlabel();
    W_Lend   = newlabel();
    W_tmpcond= newtemp();

    printf("%s:\n",             W_Lstart);
    printf("%s := %s\n",         W_tmpcond, (yyvsp[(2) - (3)].str));
    printf("if %s := 0 goto %s\n", W_tmpcond, W_Lend);
  ;}
    break;

  case 52:
#line 336 "threeac.y"
    {
    printf("goto %s\n", W_Lstart);
    printf("%s:\n",     W_Lend);
  ;}
    break;

  case 54:
#line 345 "threeac.y"
    {   //printf("%s %s %s %s %s %s %s %s %s\n" , $1 , $2 , $3 , $4 , $5 , $6 , $7 , $8 , $9); 
    F_var    = (yyvsp[(3) - (11)].str);              
    F_end    = (yyvsp[(7) - (11)].str);              
    F_inc    = (yyvsp[(8) - (11)].str) ? (yyvsp[(9) - (11)].str) : "1";   

    F_Lstart = newlabel();
    F_Lend   = newlabel();
    F_tmpcond= newtemp();

   
    printf("%s := %s\n", F_var, (yyvsp[(5) - (11)].str));

 
    printf("%s:\n",    F_Lstart);

    if (for_flag) {
      
      printf("%s := %s > %s\n", F_tmpcond, F_var, F_end);
    } else if(for_flag == 0) {
     
      printf("%s := %s < %s\n", F_tmpcond, F_var, F_end);
    }
    printf("if %s == 1 goto %s\n", F_tmpcond, F_Lend);
;}
    break;

  case 55:
#line 370 "threeac.y"
    {
    if (for_flag) {
    
      printf("%s := %s + %s\n", F_var, F_var, F_inc);
    } else if(for_flag == 0) {
     
      printf("%s := %s - %s\n", F_var, F_var, F_inc);
    }
    printf("goto %s\n",     F_Lstart);
    printf("%s:\n",         F_Lend);
;}
    break;

  case 57:
#line 385 "threeac.y"
    {   // printf("%s %s %s %s %s %s %s %s %s\n" , $1 , $2 , $3 , $4 , $5 , $6 , $7 , $8 , $9); 
    F_var    = (yyvsp[(2) - (9)].str);
    F_end    = (yyvsp[(6) - (9)].str);
    F_inc    = (yyvsp[(7) - (9)].str) ? (yyvsp[(8) - (9)].str) : "1";
    F_Lstart = newlabel();
    F_Lend   = newlabel();
    F_tmpcond= newtemp();


    printf("%s := %s\n", F_var, (yyvsp[(4) - (9)].str));

   
    printf("%s:\n",    F_Lstart);

    if (for_flag) {
    
      printf("%s := %s > %s\n", F_tmpcond, F_var, F_end);
    } else if(for_flag == 0) {
      
      printf("%s := %s < %s\n", F_tmpcond, F_var, F_end);
    }
    printf("if %s == 1 goto %s\n", F_tmpcond, F_Lend);
;}
    break;

  case 58:
#line 409 "threeac.y"
    {
    if (for_flag) {
     
      printf("%s := %s + %s\n", F_var, F_var, F_inc);
    } else if(for_flag == 0) {
      
      printf("%s := %s - %s\n", F_var, F_var, F_inc);
    }
    printf("goto %s\n",     F_Lstart);
    printf("%s:\n",         F_Lend);
;}
    break;

  case 60:
#line 425 "threeac.y"
    { ;}
    break;

  case 61:
#line 426 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);  ;}
    break;

  case 62:
#line 427 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 63:
#line 430 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 64:
#line 431 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 65:
#line 434 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 66:
#line 435 "threeac.y"
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

  case 67:
#line 456 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 68:
#line 459 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 69:
#line 462 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 70:
#line 465 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 71:
#line 468 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 72:
#line 471 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str);
    ;}
    break;

  case 73:
#line 475 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 74:
#line 478 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 75:
#line 479 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s > %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 76:
#line 484 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s < %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 77:
#line 489 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s >= %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 78:
#line 494 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s <= %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 79:
#line 499 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s == %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 80:
#line 504 "threeac.y"
    {
         char *temp = newtemp();
         sprintf(temp, "%s != %s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 81:
#line 511 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 82:
#line 512 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s + %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 83:
#line 517 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s - %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 84:
#line 525 "threeac.y"
    {  ;}
    break;

  case 85:
#line 526 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s * %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 86:
#line 531 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s / %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 87:
#line 536 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := %s %% %s\n", temp, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 88:
#line 543 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 89:
#line 544 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 90:
#line 545 "threeac.y"
    {
         char *temp = newtemp();
         printf("%s := 0 - %s\n", temp, (yyvsp[(2) - (2)].str));
         (yyval.str) = temp;
     ;}
    break;

  case 91:
#line 550 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 92:
#line 551 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 93:
#line 554 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (2)].str); ;}
    break;

  case 94:
#line 557 "threeac.y"
    {
    ;}
    break;

  case 95:
#line 560 "threeac.y"
    { for_flag = 1;
      //printf("I am in the %s for loop\n" ,  $1); 
    ;}
    break;

  case 96:
#line 564 "threeac.y"
    { for_flag = 0;
      //printf("I am in the %s for loop\n" ,  $1); 
    ;}
    break;

  case 97:
#line 569 "threeac.y"
    {
         if(!is_declared((yyvsp[(1) - (1)].str))){
             char err[100];
             snprintf(err, sizeof(err),"Variable '%s' not declared", (yyvsp[(1) - (1)].str));
             semantic_error(err);
         }
         (yyval.str) = (yyvsp[(1) - (1)].str);
     ;}
    break;

  case 98:
#line 577 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 99:
#line 578 "threeac.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 100:
#line 579 "threeac.y"
    { (yyval.str) = (yyvsp[(2) - (3)].str); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2375 "threeac.tab.c"
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


#line 581 "threeac.y"

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

