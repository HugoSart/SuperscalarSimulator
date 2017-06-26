/* simplest version of calculator */
%{
    #include <stdio.h>
    #include <string.h>
    #include "op_def.h"

    extern char *yytext;

    char yybuffer[200];

    const int zero = 0;

    FILE *file;

%}

%union yylval {
	int d;
    char *bin;
}

/* declare tokens */
%token<d> NUMBER REG LABEL
%token COMMA COLON 
%token OPCODE
%token REGISTER ADRESS
%token EOL QUOTE
%token ABS

%token<d> OP OP_3 OP_3I OP_3S OP_3B OP_2 OP_2I OP_2S OP_2B OP_1 OP_1I OP_1S OP_1B
%token ARG DIR_DATA DIR_TEXT DIR_GLOBL MAIN
%token ST_BYTE ST_SPACE ST_WORD STORAGE_TYPE

%%

line:
  | DIR_DATA EOL data_line
  | DIR_TEXT EOL text_line
  ;

data_line:
  | data_line expData EOL
  | data_line expData
  ;
expData:
  | LABEL STORAGE_TYPE argData
  | DIR_TEXT EOL text_line
  ;
argData: NUMBER
  | NUMBER COMMA argData
  ;

text_line:
  | text_line expText EOL
  | text_line expText
  ;
expText:
  | EOL
  | argText
  | LABEL argText
  | LABEL
  ;
argText: OP_3 REG COMMA REG COMMA REG {

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4, r3 = $6;

    char *ops = bsopcode(op), *funcs = bsfunc(op);
    char *rs = itbs(5,r2), *rt = itbs(5,r3), *rd = itbs(5,r1), *zero = itbs(5, 0);

    strcat(yybuffer, ops);
    strcat(yybuffer, rs);
    strcat(yybuffer, rt);
    strcat(yybuffer, rd);
    strcat(yybuffer, zero);
    strcat(yybuffer, funcs);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("dec: %d\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_3I REG COMMA REG COMMA NUMBER {

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4, num = $6;

    char *ops = bsopcode(op);
    char *rs = itbs(5,r2), *rt = itbs(5,r1), *imm = itbs(16, num);

    strcat(yybuffer, ops);
    strcat(yybuffer, rs);
    strcat(yybuffer, rt);
    strcat(yybuffer, itbs);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("dec: %d\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_3S REG COMMA REG COMMA NUMBER {

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4, num = $6;

    char *ops = bsopcode(op), *funcs = bsfunc(op);
    char *rs = itbs(5,0), *rt = itbs(5,r2), *rd = itbs(5,r1), *zero = rs;

    strcat(yybuffer, ops);
    strcat(yybuffer, rs);
    strcat(yybuffer, rt);
    strcat(yybuffer, rd);
    strcat(yybuffer, zero);
    strcat(yybuffer, funcs);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("dec: %d\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_2 REG COMMA REG {

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4;

    char *ops = bsopcode(op), *funcs = bsfunc(op);
    char *rs = itbs(5,r2), *rt = itbs(5,r1), *zero = itbs(10, 0);

    strcat(yybuffer, ops);
    strcat(yybuffer, rs);
    strcat(yybuffer, rt);
    strcat(yybuffer, zero);
    strcat(yybuffer, funcs);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("dec: %d\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_2I REG COMMA NUMBER {

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, num = $4;

    strcat(yybuffer, bsopcode(op));
    strcat(yybuffer, itbs(5, 0));
    strcat(yybuffer, itbs(5, r1));
    strcat(yybuffer, itbs(16, num));

    unsigned int bi = bsti(yybuffer);

    printf("bin: %s\n", yybuffer);
    printf("dec: %d\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  ;

%%

int main(int argc, char **argv) {

    if ((file = fopen("output", "w")) == NULL) return 1;

    char num[400] = {0};
    fwrite(num, sizeof(char), 400, file);

	yyparse();

	fclose(file);
	return 0;
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}
