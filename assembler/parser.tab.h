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
     NUMBER = 258,
     STR = 259,
     COMMA = 260,
     COLON = 261,
     OPCODE = 262,
     REGISTER = 263,
     ADRESS = 264,
     EOL = 265,
     QUOTE = 266,
     ABS = 267,
     OP = 268,
     ARG = 269,
     LABEL = 270,
     DIR_DATA = 271,
     DIR_TEXT = 272,
     DIR_GLOBL = 273,
     MAIN = 274,
     ST_BYTE = 275,
     ST_SPACE = 276,
     ST_WORD = 277,
     STORAGE_TYPE = 278,
     VALUE = 279,
     ADDRESS = 280,
     VAR = 281,
     REG = 282,
     ZERO = 283,
     AT = 284,
     V0 = 285,
     V1 = 286,
     A0 = 287,
     A1 = 288,
     A2 = 289,
     A3 = 290,
     T0 = 291,
     T1 = 292,
     T2 = 293,
     T3 = 294,
     T4 = 295,
     T5 = 296,
     T6 = 297,
     T7 = 298,
     S0 = 299,
     S1 = 300,
     S2 = 301,
     S3 = 302,
     S4 = 303,
     S5 = 304,
     S6 = 305,
     S7 = 306,
     T8 = 307,
     T9 = 308,
     K0 = 309,
     K1 = 310,
     GP = 311,
     SP = 312,
     FP = 313,
     RA = 314,
     ADD = 315,
     ADDU = 316,
     ADDI = 317,
     ADDIU = 318,
     AND = 319,
     ANDI = 320,
     CLO = 321,
     CLZ = 322,
     DIV = 323,
     DIVU = 324,
     MULT = 325,
     MULTU = 326,
     MUL = 327,
     MULO = 328,
     MULOU = 329,
     MADD = 330,
     MADDU = 331,
     MSUB = 332,
     NEG = 333,
     NEGU = 334,
     NOR = 335,
     NOT = 336,
     OR = 337,
     ORI = 338,
     REM = 339,
     REMU = 340,
     SLL = 341,
     SLLV = 342,
     SRA = 343,
     SRAV = 344,
     SRL = 345,
     SRLV = 346,
     ROL = 347,
     ROR = 348,
     SUB = 349,
     SUBU = 350,
     XOR = 351,
     XORI = 352,
     LUI = 353,
     LI = 354,
     SLT = 355,
     SLTU = 356,
     SLTI = 357,
     SLTIU = 358,
     SEQ = 359,
     SGE = 360,
     SGEU = 361,
     SGT = 362,
     SGTU = 363,
     SLE = 364,
     SLEU = 365,
     SNE = 366,
     B = 367,
     BCLF = 368,
     BCLT = 369,
     BEQ = 370,
     BGEZ = 371,
     BGEZAL = 372,
     BGTZ = 373,
     BLEZ = 374,
     BLTZAL = 375,
     BLTZ = 376,
     BNE = 377,
     BEQZ = 378,
     BGE = 379,
     BGEU = 380,
     BGT = 381,
     BLE = 382,
     BLEU = 383,
     BLT = 384,
     BLTU = 385,
     BNEZ = 386,
     J = 387,
     JAL = 388,
     JALR = 389,
     JR = 390,
     TEQ = 391,
     TEQI = 392,
     TGE = 393,
     TGEU = 394,
     TGEI = 395,
     TGEIU = 396,
     TLT = 397,
     TLTU = 398,
     TLTI = 399,
     TLTIU = 400,
     LA = 401,
     LB = 402,
     LBU = 403,
     LH = 404,
     LHU = 405,
     LW = 406,
     LWCL = 407,
     LWL = 408,
     LWR = 409,
     LD = 410,
     ULH = 411,
     ULHU = 412,
     ULW = 413,
     LL = 414,
     SB = 415,
     SH = 416,
     SW = 417,
     SWCL = 418,
     SDCL = 419,
     SWL = 420,
     SWR = 421,
     SD = 422,
     USH = 423,
     USW = 424,
     SC = 425,
     MOVE = 426,
     MFHI = 427,
     MFLO = 428,
     MTHI = 429,
     MTLO = 430,
     MFC0 = 431,
     MFC1 = 432,
     MTC0 = 433,
     MTC1 = 434,
     MOVN = 435,
     MOVZ = 436,
     MOVF = 437,
     MOVT = 438,
     SYSCALL = 439,
     BREAK = 440,
     NOP = 441
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define STR 259
#define COMMA 260
#define COLON 261
#define OPCODE 262
#define REGISTER 263
#define ADRESS 264
#define EOL 265
#define QUOTE 266
#define ABS 267
#define OP 268
#define ARG 269
#define LABEL 270
#define DIR_DATA 271
#define DIR_TEXT 272
#define DIR_GLOBL 273
#define MAIN 274
#define ST_BYTE 275
#define ST_SPACE 276
#define ST_WORD 277
#define STORAGE_TYPE 278
#define VALUE 279
#define ADDRESS 280
#define VAR 281
#define REG 282
#define ZERO 283
#define AT 284
#define V0 285
#define V1 286
#define A0 287
#define A1 288
#define A2 289
#define A3 290
#define T0 291
#define T1 292
#define T2 293
#define T3 294
#define T4 295
#define T5 296
#define T6 297
#define T7 298
#define S0 299
#define S1 300
#define S2 301
#define S3 302
#define S4 303
#define S5 304
#define S6 305
#define S7 306
#define T8 307
#define T9 308
#define K0 309
#define K1 310
#define GP 311
#define SP 312
#define FP 313
#define RA 314
#define ADD 315
#define ADDU 316
#define ADDI 317
#define ADDIU 318
#define AND 319
#define ANDI 320
#define CLO 321
#define CLZ 322
#define DIV 323
#define DIVU 324
#define MULT 325
#define MULTU 326
#define MUL 327
#define MULO 328
#define MULOU 329
#define MADD 330
#define MADDU 331
#define MSUB 332
#define NEG 333
#define NEGU 334
#define NOR 335
#define NOT 336
#define OR 337
#define ORI 338
#define REM 339
#define REMU 340
#define SLL 341
#define SLLV 342
#define SRA 343
#define SRAV 344
#define SRL 345
#define SRLV 346
#define ROL 347
#define ROR 348
#define SUB 349
#define SUBU 350
#define XOR 351
#define XORI 352
#define LUI 353
#define LI 354
#define SLT 355
#define SLTU 356
#define SLTI 357
#define SLTIU 358
#define SEQ 359
#define SGE 360
#define SGEU 361
#define SGT 362
#define SGTU 363
#define SLE 364
#define SLEU 365
#define SNE 366
#define B 367
#define BCLF 368
#define BCLT 369
#define BEQ 370
#define BGEZ 371
#define BGEZAL 372
#define BGTZ 373
#define BLEZ 374
#define BLTZAL 375
#define BLTZ 376
#define BNE 377
#define BEQZ 378
#define BGE 379
#define BGEU 380
#define BGT 381
#define BLE 382
#define BLEU 383
#define BLT 384
#define BLTU 385
#define BNEZ 386
#define J 387
#define JAL 388
#define JALR 389
#define JR 390
#define TEQ 391
#define TEQI 392
#define TGE 393
#define TGEU 394
#define TGEI 395
#define TGEIU 396
#define TLT 397
#define TLTU 398
#define TLTI 399
#define TLTIU 400
#define LA 401
#define LB 402
#define LBU 403
#define LH 404
#define LHU 405
#define LW 406
#define LWCL 407
#define LWL 408
#define LWR 409
#define LD 410
#define ULH 411
#define ULHU 412
#define ULW 413
#define LL 414
#define SB 415
#define SH 416
#define SW 417
#define SWCL 418
#define SDCL 419
#define SWL 420
#define SWR 421
#define SD 422
#define USH 423
#define USW 424
#define SC 425
#define MOVE 426
#define MFHI 427
#define MFLO 428
#define MTHI 429
#define MTLO 430
#define MFC0 431
#define MFC1 432
#define MTC0 433
#define MTC1 434
#define MOVN 435
#define MOVZ 436
#define MOVF 437
#define MOVT 438
#define SYSCALL 439
#define BREAK 440
#define NOP 441




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union
#line 6 "parser.y"
yylval {
	int d;
    char s[20];
}
/* Line 1489 of yacc.c.  */
#line 426 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

