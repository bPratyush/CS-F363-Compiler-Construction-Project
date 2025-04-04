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
     IDENTIFIER = 258,
     INTEGER_CONSTANT = 259,
     CHARACTER_CONSTANT = 260,
     STRING_CONSTANT = 261,
     TK_BEGIN = 262,
     TK_END = 263,
     TK_VARDECL = 264,
     TK_PROGRAM = 265,
     TK_INT = 266,
     TK_CHAR = 267,
     TK_IF = 268,
     TK_ELSE = 269,
     TK_WHILE = 270,
     TK_FOR = 271,
     TK_PRINT = 272,
     TK_SCAN = 273,
     TK_ASSIGN = 274,
     TK_RELOP = 275,
     TK_ARITHOP = 276,
     TK_SEP = 277,
     TK_COLON = 278,
     TK_TO = 279,
     TK_INC = 280,
     TK_DEC = 281,
     TK_DO = 282,
     IFX = 283
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define INTEGER_CONSTANT 259
#define CHARACTER_CONSTANT 260
#define STRING_CONSTANT 261
#define TK_BEGIN 262
#define TK_END 263
#define TK_VARDECL 264
#define TK_PROGRAM 265
#define TK_INT 266
#define TK_CHAR 267
#define TK_IF 268
#define TK_ELSE 269
#define TK_WHILE 270
#define TK_FOR 271
#define TK_PRINT 272
#define TK_SCAN 273
#define TK_ASSIGN 274
#define TK_RELOP 275
#define TK_ARITHOP 276
#define TK_SEP 277
#define TK_COLON 278
#define TK_TO 279
#define TK_INC 280
#define TK_DEC 281
#define TK_DO 282
#define IFX 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "src.y"
{
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 109 "src.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

