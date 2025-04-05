/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     NO_ELSE = 301
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
#define NO_ELSE 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 37 "parser.y"
{
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 145 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

