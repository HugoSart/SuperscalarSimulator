/* simplest version of calculator */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../op_def.h"
    #include "../list.h"

    extern char *yytext;//

    char yybuffer[200];

    const int zero = 0;

    FILE *file;

    int *array;
    int array_size = 0;

    int inst_count = 0;

    void inc_inst() {
      if (!inst_count) {
        char num[400] = {0};
        fwrite(num, sizeof(char), 400 - ftell(file), file);//adas
      }
      inst_count++;
    }

    union word {
        unsigned char byte[4];
        int value;
    };

    extern List varList;

%}

%union {
    int d;
    char *str;
}

/* declare tokens */
%token<d> NUMBER REG
%token<str> LABEL VAR
%token<d> OP_3 OP_3I OP_3S OP_2 OP_2I OP_2A OP_1 OP_1T
%token COMMA COLON 
%token OPCODE
%token ADRESS
%token EOL QUOTE
%token ABS

%token ARG DIR_DATA DIR_TEXT DIR_GLOBL MAIN
%token ST_BYTE ST_SPACE ST_WORD STORAGE_TYPE ST_INT

%type<d> value

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
  | LABEL STORAGE_TYPE argData {

    list_add(&varList, $1, ftell(file));
    list_print(&varList);
    for (int i = array_size - 1; i >= 0; i--) {
        printf("aaa %d\n", array[i]);
        fwrite(&array[i], sizeof(int), 1, file);
    }
    printf("\n");
    free(array);
    array_size = 0;

  }
  | DIR_TEXT EOL text_line
  ;
argData: NUMBER {

    array = malloc(sizeof(int));
    array[0] = $1;
    array_size++;

  }
  | NUMBER COMMA argData {

    realloc(array, sizeof(int) * (array_size + 1));
    array[array_size] = $1;
    array_size++;

  }
  ;

text_line:
  | text_line expText EOL
  | text_line expText
  ;
expText:
  | EOL
  | argText
  | LABEL argText
  ;
argText: OP_3 REG COMMA REG COMMA REG {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4, r3 = $6;

    char *ops = itbs(6, opcode(op)), *funcs = itbs(6, func(op));
    char *rd = itbs(5,r1), *rs = itbs(5,r2), *rt = itbs(5,r3), *zero = itbs(5, 0);

    strcat(yybuffer, ops);
    strcat(yybuffer, rs);
    strcat(yybuffer, rt);
    strcat(yybuffer, rd);
    strcat(yybuffer, zero);
    strcat(yybuffer, funcs);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_3I REG COMMA REG COMMA value {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4, num = $6;

    char *ops = itbs(6, opcode(op));
    char *rt = itbs(5,r1), *rs = itbs(5,r2), *imm = itbs(16, num);

    strcat(yybuffer, ops);
    strcat(yybuffer, rs);
    strcat(yybuffer, rt);
    strcat(yybuffer, imm);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_3S REG COMMA REG COMMA value {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4, num = $6;

    char *ops = itbs(6, opcode(op)), *funcs = itbs(6, func(op));
    char *rd = itbs(5,r1), *rt = itbs(5,r2), *shamt = itbs(5,num), *zero = itbs(5,0);

    strcat(yybuffer, ops);
    strcat(yybuffer, zero);
    strcat(yybuffer, rt);
    strcat(yybuffer, rd);
    strcat(yybuffer, zero);
    strcat(yybuffer, funcs);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_2 REG COMMA REG {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, r2 = $4;

    char *ops = itbs(6, opcode(op)), *funcs = itbs(6, func(op));
    char *rs = itbs(5,r1), *rt = itbs(5,r2), *zero = itbs(10, 0);

    strcat(yybuffer, ops);
    strcat(yybuffer, rs);
    strcat(yybuffer, rt);
    strcat(yybuffer, zero);
    strcat(yybuffer, funcs);

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_2I REG COMMA value {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, num = $4;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(5, 0));
    strcat(yybuffer, itbs(5, r1));
    strcat(yybuffer, itbs(16, num));

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_2A REG COMMA value {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, num = $4;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(5, 0));//kojhv
    strcat(yybuffer, itbs(5, r1));
    strcat(yybuffer, itbs(16, num));

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_1 REG {

    inc_inst();

    yybuffer[0] = '\0';//dsa

    int op = $1, reg = $2;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(5, reg));
    strcat(yybuffer, itbs(15, itbs(15,0)));
    strcat(yybuffer, itbs(6, func(op)));


    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  | OP_1T value {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, num = $2;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(26, num));

    unsigned int bi = bsti(yybuffer);

    printf("operation: %d\n", op);
    printf("bin: %s\n", yybuffer);
    printf("hex: %08x08x\n", bi);
    printf("dec: %u\n\n", bi);
    fwrite(&bi, 4, 1, file);

  }
  ;
value: NUMBER { $$ = $1 };
  | VAR {
      printf("Teste: %s\n", $1);
      Node *var = list_get(&varList, $1);
      if (var == NULL) {
        yyerror("Variable undefined");
      }

      union word aux = {0};

      unsigned int return_offset = ftell(file);
      fseek(file, var->offset, SEEK_SET);
      fread(&(aux.byte[0]), 1, 1, file);
      fread(&(aux.byte[1]), 1, 1, file);
      fread(&(aux.byte[2]), 1, 1, file);
      fread(&(aux.byte[3]), 1, 1, file);
      fseek(file, return_offset, SEEK_SET);

      printf("aux.value: %d\n", aux.value);
      $$ = aux.value;

  }
  ;

%%

int main(int argc, char **argv) {

    if ((file = fopen("output", "w+b")) == NULL) return 1;

	yyparse();

	fclose(file);
	return 0;
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}
