/* recognize tokens for the calculator and print them out */

%{
  #include <string.h>
  #include "parser.tab.h"
%}

%%

"|"	   { return ABS; }
"#".*
","	   { return COMMA; }
[0-9]+ { yylval.d = atoi(yytext); return NUMBER; }
\n     { return EOL; }
[ \t]  { /* ignore whitespace */ }
\"	   { return QUOTE; }
.      { printf("Mystery character %c\n", *yytext); }

[a-zA-Z]+":"  { return LABEL; }
[a-zA-Z]+     { return STR; }
".data"       { return DIR_DATA; }
".text"       { return DIR_TEXT; }

".word"        { yylval.d = ST_WORD; return STORAGE_TYPE; }
".byte"        { yylval.d = ST_BYTE; return STORAGE_TYPE; }
".space"       { yylval.d = ST_SPACE; return STORAGE_TYPE; }

"$zero" | "$0"  { yylval.d = ZERO; return REG; }
"$at"   | "$1"  { yylval.d = AT; return REG; }
"$v0"   | "$2"  { yylval.d = V0; return REG; }
"$v1"   | "$3"  { yylval.d = V1; return REG; }
"$a0"   | "$4"  { yylval.d = A0; return REG; }
"$a1"   | "$5"  { yylval.d = A1; return REG; }
"$a2"   | "$6"  { yylval.d = A2; return REG; }
"$a3"   | "$7"  { yylval.d = A3; return REG; }
"$t0"   | "$8"  { yylval.d = T0; return REG; }
"$t1"   | "$9"  { yylval.d = T1; return REG; }
"$t2"   | "$10" { yylval.d = T2; return REG; }
"$t3"   | "$11" { yylval.d = T3; return REG; }
"$t4"   | "$12" { yylval.d = T4; return REG; }
"$t5"   | "$13" { yylval.d = T5; return REG; }
"$t6"   | "$14" { yylval.d = T6; return REG; }
"$t7"   | "$15" { yylval.d = T7; return REG; }
"$s0"   | "$16" { yylval.d = S0; return REG; }
"$s1"   | "$17" { yylval.d = S1; return REG; }
"$s2"   | "$18" { yylval.d = S2; return REG; }
"$s3"   | "$19" { yylval.d = S3; return REG; }
"$s4"   | "$20" { yylval.d = S4; return REG; }
"$s5"   | "$21" { yylval.d = S5; return REG; }
"$s6"   | "$22" { yylval.d = S6; return REG; }
"$s7"   | "$23" { yylval.d = S7; return REG; }
"$t8"   | "$24" { yylval.d = T8; return REG; }
"$t9"   | "$25" { yylval.d = T9; return REG; }
"$k0"   | "$26" { yylval.d = K0; return REG; }
"$k1"   | "$27" { yylval.d = K1; return REG; }
"$gp"   | "$28" { yylval.d = GP; return REG; }
"$sp"   | "$29" { yylval.d = SP; return REG; }
"$s8"   | "$30" { yylval.d = FP; return REG; }
"$fp"           { yylval.d = FP; return REG; }
"$ra"   | "$31" { yylval.d = RA; return REG; }

"add"    { yylval.d = ADD;   return OP; }
"addu"   { yylval.d = ADDU;  return OP; }
"addi"   { yylval.d = ADDI;  return OP; }
"addiu"  { yylval.d = ADDIU; return OP; }
"and"    { yylval.d = AND;   return OP; }
"andi"   { yylval.d = ANDI;  return OP; }
"clo"    { yylval.d = CLO;   return OP; }
"clz"    { yylval.d = CLZ;   return OP; }
"div"    { yylval.d = DIV;   return OP; }
"divu"   { yylval.d = DIVU;  return OP; }
"mult"   { yylval.d = MULT;  return OP; }
"multu"  { yylval.d = MULTU; return OP; }
"mul"    { yylval.d = MUL;   return OP; }
"mulo"   { yylval.d = MULO;  return OP; }
"mulou"  { yylval.d = MULOU; return OP; }
"madd"   { yylval.d = MADD;  return OP; }
"maddu"  { yylval.d = MADDU; return OP; }
"msub"   { yylval.d = MSUB;  return OP; }


%%

