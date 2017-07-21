/* recognize tokens for the calculator and print them out */

%{
  #include <string.h>
  #include "parser.tab.h"
  #include "../op_def.h"
  #include "../list.h"

  extern List varList;

%}

%%

"|"	   { return ABS; }
"#".*
","	   { return COMMA; }
[0-9]+|[-][0-9]+ { yylval.d = atoi(yytext); return NUMBER; }
0[xX][0-9a-fA-F]+ { yylval.d = strtol(yytext, NULL, 16); return NUMBER; }
\n     { return EOL; }
[ \t]  { /* ignore whitespace */ }
\"	   { return QUOTE; }

[a-zA-Z_][a-zA-Z0-9_]+":"  { yylval.str = strdup(yytext); yylval.str[strlen(yylval.str) - 1] = '\0'; return LABEL; }

".data"        { return DIR_DATA; }
".text"        { return DIR_TEXT; }

".int"         { yylval.d = ST_INT;  return STORAGE_TYPE; }

"$zero"|"$0"     { yylval.d = ZERO; return REG; }
"$at"|"$1"       { yylval.d = AT;   return REG; }
"$v0"|"$2"       { yylval.d = V0;   return REG; }
"$v1"|"$3"       { yylval.d = V1;   return REG; }
"$a0"|"$4"       { yylval.d = A0;   return REG; }
"$a1"|"$5"       { yylval.d = A1;   return REG; }
"$a2"|"$6"       { yylval.d = A2;   return REG; }
"$a3"|"$7"       { yylval.d = A3;   return REG; }
"$t0"|"$8"       { yylval.d = T0;   return REG; }
"$t1"|"$9"       { yylval.d = T1;   return REG; }
"$t2"|"$10"      { yylval.d = T2;   return REG; }
"$t3"|"$11"      { yylval.d = T3;   return REG; }
"$t4"|"$12"      { yylval.d = T4;   return REG; }
"$t5"|"$13"      { yylval.d = T5;   return REG; }
"$t6"|"$14"      { yylval.d = T6;   return REG; }
"$t7"|"$15"      { yylval.d = T7;   return REG; }
"$s0"|"$16"      { yylval.d = S0;   return REG; }
"$s1"|"$17"      { yylval.d = S1;   return REG; }
"$s2"|"$18"      { yylval.d = S2;   return REG; }
"$s3"|"$19"      { yylval.d = S3;   return REG; }
"$s4"|"$20"      { yylval.d = S4;   return REG; }
"$s5"|"$21"      { yylval.d = S5;   return REG; }
"$s6"|"$22"      { yylval.d = S6;   return REG; }
"$s7"|"$23"      { yylval.d = S7;   return REG; }
"$t8"|"$24"      { yylval.d = T8;   return REG; }
"$t9"|"$25"      { yylval.d = T9;   return REG; }
"$k0"|"$26"      { yylval.d = K0;   return REG; }
"$k1"|"$27"      { yylval.d = K1;   return REG; }
"$gp"|"$28"      { yylval.d = GP;   return REG; }
"$sp"|"$29"      { yylval.d = SP;   return REG; }
"$s8"|"$30"|"fp" { yylval.d = FP;   return REG; }
"$ra"|"$31"      { yylval.d = RA;   return REG; }

"add"    { yylval.d = ADD;   return OP_3; }
"addu"   { yylval.d = ADDU;  return OP_3; }
"addi"   { yylval.d = ADDI;  return OP_3I; }
"addiu"  { yylval.d = ADDIU; return OP_3I; }
"and"    { yylval.d = AND;   return OP_3; }
"andi"   { yylval.d = ANDI;  return OP_3I; }
"clo"    { yylval.d = CLO;   return OP_2; }
"clz"    { yylval.d = CLZ;   return OP_2; }
"div"    { yylval.d = DIV;   return OP_2; /* or OP_3 */ }
"divu"   { yylval.d = DIVU;  return OP_2; /* or OP_3 */ }
"mult"   { yylval.d = MULT;  return OP_2; }
"multu"  { yylval.d = MULTU; return OP_2; }
"mul"    { yylval.d = MUL;   return OP_3; }
"madd"   { yylval.d = MADD;  return OP_2; }
"maddu"  { yylval.d = MADDU; return OP_2; }
"msub"   { yylval.d = MSUB;  return OP_2; }

"nor"    { yylval.d = NOR;   return OP_3; }
"or"     { yylval.d = OR;    return OP_3; }
"ori"    { yylval.d = ORI;   return OP_3I; }
"sll"    { yylval.d = SLL;   return OP_3S; }
"sllv"   { yylval.d = SLLV;  return OP_3; }
"sra"    { yylval.d = SRA;   return OP_3S; }
"srav"   { yylval.d = SRAV;  return OP_3; }
"srl"    { yylval.d = SRL;   return OP_3S; }
"srlv"   { yylval.d = SRLV;  return OP_3; /* or OP_3 */ }
"sub"    { yylval.d = SUB;   return OP_3; /* or OP_3 */ }
"subu"   { yylval.d = SUBU;  return OP_3; }
"xor"    { yylval.d = XOR;   return OP_3; }
"xori"   { yylval.d = XORI;  return OP_3I; }
"lui"    { yylval.d = LUI;   return OP_2I; }
"slt"    { yylval.d = SLT;   return OP_3; }
"sltu"   { yylval.d = SLTU;  return OP_3; }
"slti"   { yylval.d = SLTI;  return OP_3I; }
"sltiu"  { yylval.d = SLTIU; return OP_3I; }

"bclf"   { yylval.d = BCLF;  return OP_3S; }
"beq"    { yylval.d = BEQ;   return OP_3S; }
"bgez"   { yylval.d = BGEZ;  return OP_3; }
"bgezal" { yylval.d = BGEZAL;return OP_2; }
"bgtz"   { yylval.d = BGTZ;  return OP_2; }
"blez"   { yylval.d = BLEZ;  return OP_2; }
"bltzal" { yylval.d = BLTZAL;return OP_3S; }
"bltz"   { yylval.d = BLTZ;  return OP_3; }
"bne"    { yylval.d = BNE;   return OP_2; }

"j"      { yylval.d = J;     return OP_1T; }
"jal"    { yylval.d = JAL;   return OP_1T; }
"jalr"   { yylval.d = JALR;  return OP_2; }
"jr"     { yylval.d = JR;    return OP_1; }

"teq"    { yylval.d = TEQ;   return OP_2; }
"teqi"   { yylval.d = TEQI;  return OP_2I; }
"tge"    { yylval.d = TGE;   return OP_2; }
"tgeu"   { yylval.d = TGEU;  return OP_2; }
"tgei"   { yylval.d = TGEI;  return OP_2I; }
"tgeiu"  { yylval.d = TGEIU; return OP_2I; }
"tlt"    { yylval.d = TLT;   return OP_2; }
"tltu"   { yylval.d = TLTU;  return OP_2; }
"tlti"   { yylval.d = TLTI;  return OP_2I; }
"tltiu"  { yylval.d = TLTIU; return OP_2I; }

"lb"     { yylval.d = LB;    return OP_2I; }
"lbu"    { yylval.d = LBU;   return OP_2I; }
"lh"     { yylval.d = LH;    return OP_2I; }
"lhu"    { yylval.d = LHU;   return OP_2I; }
"lw"     { yylval.d = LW;    return OP_2I; }
"lwcl"   { yylval.d = LWCL;  return OP_2I; }
"lwl"    { yylval.d = LWL;   return OP_2I; }
"lwr"    { yylval.d = LWR;   return OP_2I; }
"ll"     { yylval.d = LL;    return OP_2I; }

"sb"     { yylval.d = SB;    return OP_2A; }
"sh"     { yylval.d = SH;    return OP_2A; }
"sw"     { yylval.d = SW;    return OP_2A; }
"swcl"   { yylval.d = SWCL;  return OP_2A; }
"sdcl"   { yylval.d = SDCL;  return OP_2A; }
"swl"    { yylval.d = SWL;   return OP_2A; }
"swr"    { yylval.d = SWR;   return OP_2A; }
"sc"     { yylval.d = SC;    return OP_2A; }

"mfhi"   { yylval.d = MFHI;  return OP_1; }
"mflo"   { yylval.d = MFLO;  return OP_1; }
"mthi"   { yylval.d = MTHI;  return OP_1; }
"movn"   { yylval.d = MOVN;  return OP_3; }
"movz"   { yylval.d = MOVZ;  return OP_3; }

[a-zA-Z_][a-zA-Z0-9_]+ {yylval.str = strdup(yytext); return VAR; }

.        { printf("Mystery chracter %c\n", *yytext); }

%%

