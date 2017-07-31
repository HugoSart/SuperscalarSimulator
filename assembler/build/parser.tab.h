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
     CP = 258,
     OP = 259,
     NUMBER = 260,
     DISP = 261,
     REG = 262,
     LABEL = 263,
     VAR = 264,
     OP_3 = 265,
     OP_3I = 266,
     OP_3S = 267,
     OP_2 = 268,
     OP_2I = 269,
     OP_2A = 270,
     OP_1 = 271,
     OP_1T = 272,
     OP_1S = 273,
     OP_1M = 274,
     OP_1M2 = 275,
     OP_2B = 276,
     OP_2O = 277,
     NOP = 278,
     COMMA = 279,
     COLON = 280,
     OPCODE = 281,
     ADRESS = 282,
     EOL = 283,
     QUOTE = 284,
     ABS = 285,
     ARG = 286,
     DIR_DATA = 287,
     DIR_TEXT = 288,
     DIR_GLOBL = 289,
     MAIN = 290,
     ST_BYTE = 291,
     ST_SPACE = 292,
     ST_WORD = 293,
     STORAGE_TYPE = 294,
     ST_INT = 295
   };
#endif
/* Tokens.  */
#define CP 258
#define OP 259
#define NUMBER 260
#define DISP 261
#define REG 262
#define LABEL 263
#define VAR 264
#define OP_3 265
#define OP_3I 266
#define OP_3S 267
#define OP_2 268
#define OP_2I 269
#define OP_2A 270
#define OP_1 271
#define OP_1T 272
#define OP_1S 273
#define OP_1M 274
#define OP_1M2 275
#define OP_2B 276
#define OP_2O 277
#define NOP 278
#define COMMA 279
#define COLON 280
#define OPCODE 281
#define ADRESS 282
#define EOL 283
#define QUOTE 284
#define ABS 285
#define ARG 286
#define DIR_DATA 287
#define DIR_TEXT 288
#define DIR_GLOBL 289
#define MAIN 290
#define ST_BYTE 291
#define ST_SPACE 292
#define ST_WORD 293
#define STORAGE_TYPE 294
#define ST_INT 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 46 "parser.y"
{
    int d;
    char *str;
}
/* Line 1489 of yacc.c.  */
#line 134 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

