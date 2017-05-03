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
}

/* declare tokens */
%token<d> NUMBER REG
%token COMMA COLON 
%token OPCODE
%token REGISTER ADRESS
%token EOL QUOTE
%token ABS

%token<d> OP OP_3 OP_3I OP_2 OP_1
%token ARG LABEL DIR_DATA DIR_TEXT DIR_GLOBL MAIN
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
  | argText
  | LABEL argText
  | LABEL
  ;
argText: OP_3 REG COMMA REG COMMA REG {
        yybuffer[0] = '\0';
        sprintf(yybuffer, "%d %d %d %d %d %d", $1, $6, $4, $2, 0, 0);
        printf("%s\n", yybuffer);
        fwrite(yybuffer, 1, 6, file);
  }
  | OP_3I REG COMMA REG COMMA NUMBER {

  }
  | OP_2 REG COMMA REG {

  }
  | OP_2 REG COMMA REG COMMA REG {

        yybuffer[0] = '\0';

        int aux = $1;

        if ($1 == DIV) {
            aux = DIV_3;
        } else if ($1 == DIVU) {
            aux = DIVU_3;
        } else {
            yyerror("syntax error");
            return 1;
        }

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
