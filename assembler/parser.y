/* simplest version of calculator */
%{
    #include <stdio.h>
%}

%union yylval {
	int d;
    char s[20];
}

/* declare tokens */
%token NUMBER STR
%token COMMA COLON 
%token OPCODE
%token REGISTER ADRESS
%token EOL QUOTE
%token ABS

%token OP
%token ARG LABEL DIR_DATA DIR_TEXT DIR_GLOBL MAIN
%token ST_BYTE ST_SPACE ST_WORD STORAGE_TYPE
%token VALUE ADDRESS VAR REG

%token ZERO AT V0 V1 A0 A1 A2 A3 T0 T1 T2 T3 T4 T5 T6 T7 S0 S1 S2 S3 S4 S5 S6 S7 T8 T9 K0 K1 GP SP FP RA

// Instructions
%token ADD ADDU ADDI ADDIU
%token AND ANDI CLO CLZ
%token DIV DIVU
%token MULT MULTU MUL MULO MULOU MADD MADDU MSUB
%token NEG NEGU NOR NOT
%token OR ORI
%token REM REMU
%token SLL SLLV SRA SRAV SRL SRLV
%token ROL ROR
%token SUB SUBU
%token XOR XORI
%token LUI LI
%token SLT SLTU SLTI SLTIU SEQ SGE SGEU SGT SGTU SLE SLEU SNE
%token B BCLF BCLT BEQ BGEZ BGEZAL BGTZ BLEZ BLTZAL BLTZ BNE BEQZ BGE BGEU BGT BLE BLEU BLT BLTU BNEZ
%token J JAL JALR JR
%token TEQ TEQI TGE TGEU TGEI TGEIU TLT TLTU TLTI TLTIU LA LB LBU LH LHU LW LWCL LWL LWR LD ULH ULHU ULW LL
%token SB SH SW SWCL SDCL SWL SWR SD USH USW SC
%token MOVE MFHI MFLO MTHI MTLO MFC0 MFC1 MTC0 MTC1 MOVN MOVZ MOVF MOVT
%token SYSCALL BREAK NOP

%%

line:
  | line exp EOL {}
  ;
exp:
  | DIR_DATA EOL data_line {}
  | DIR_TEXT EOL text_line {}
  ;
data_line:
  | data_line expData EOL {}
expData:
  | LABEL STORAGE_TYPE paramData {}
  | DIR_TEXT EOL text_line       {}
  ;
paramData: NUMBER
  | NUMBER COMMA paramData
  ;
text_line:
  | text_line expText EOL {}
  ;
expText:
  | OP paramText
  ;
paramText: NUMBER;


%%

int main(int argc, char **argv) {
	yyparse();
	return 0;
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}
