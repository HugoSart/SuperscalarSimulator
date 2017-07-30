/* simplest version of calculator */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../op_def.h"
    #include "../list.h"
    #include "../../source/simulator/machine/types.h"

#define YYDEBUG 1

    extern char *yytext;//dds
    extern FILE *yyin;

    char yybuffer[200];

    const int zero = 0;

    FILE *file_in, *file_out;

    int *array;
    int array_size = 0;

    int inst_count = 0;

    void inc_inst() {
      if (!inst_count) {
        char num[400] = {0};
        fwrite(num, sizeof(char), 400 - ftell(file_out), file_out);//adas
      }
      inst_count++;
    }

    union word {
        unsigned char byte[4];
        int value;
    };

    extern List varList;
    List labelList;

    int line_count;

%}

%union {
    int d;
    char *str;
}

/* declare tokens */
%token CP OP
%token<d> NUMBER DISP REG
%token<str> LABEL VAR
%token<d> OP_3 OP_3I OP_3S OP_2 OP_2I OP_2A OP_1 OP_1T OP_1S OP_1M OP_1M2 OP_2B OP_2O NOP
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

    list_add(&varList, $1, ftell(file_out) + MEM_TEXT_ADDRESS);

    for (int i = array_size - 1; i >= 0; i--) {
        fwrite(&array[i], sizeof(int), 1, file_out);
    }
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

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

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

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

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
    strcat(yybuffer, shamt);
    strcat(yybuffer, funcs);

    unsigned int bi = bsti(yybuffer);

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

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

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

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

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  | OP_2B REG COMMA value {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, r1 = $2, num = $4;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(5, r1));
    strcat(yybuffer, itbs(5, rtfunc(op))); //dsm
    strcat(yybuffer, itbs(16, num));

    unsigned int bi = bsti(yybuffer);

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);//d

  }
  | OP_2O REG COMMA value OP REG CP {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, rt = $2, rs = $6, num = $4;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(5, rs));
    strcat(yybuffer, itbs(5, rt));
    strcat(yybuffer, itbs(16, num));

    unsigned int bi = bsti(yybuffer);

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  | OP_2O REG COMMA value {

    inc_inst();

    yybuffer[0] = '\0';

    int op = $1, rt = $2, num = $4;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(5, 0));
    strcat(yybuffer, itbs(5, rt));
    strcat(yybuffer, itbs(16, num));

    unsigned int bi = bsti(yybuffer);

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

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

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  | OP_1T value {

    inc_inst(); //i2dd

    yybuffer[0] = '\0';

    int op = $1, num = $2;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(26, num));

    unsigned int bi = bsti(yybuffer);

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  | OP_1S {

    inc_inst();

    yybuffer[0] = '\0';

    strcat(yybuffer, itbs(26, 0));
    strcat(yybuffer, itbs(6, 0xc));

    unsigned int bi = bsti(yybuffer);

    printf("syscall: %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  | OP_1M REG {

    inc_inst(); //i2dd

    yybuffer[0] = '\0';

    int op = $1, r1 = $2;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(10, 0));
    strcat(yybuffer, itbs(5, r1));
    strcat(yybuffer, itbs(5, 0));
    strcat(yybuffer, itbs(6, func(op)));

    unsigned int bi = bsti(yybuffer);

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  | OP_1M2 REG {

    inc_inst(); //i2dd

    yybuffer[0] = '\0';

    int op = $1, r1 = $2;

    strcat(yybuffer, itbs(6, opcode(op)));
    strcat(yybuffer, itbs(5, r1));
    strcat(yybuffer, itbs(15, 0));
    strcat(yybuffer, itbs(6, func(op)));

    unsigned int bi = bsti(yybuffer);

    printf("opcode : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  | NOP {

    inc_inst();

    yybuffer[0] = '\0';

    strcat(yybuffer, itbs(32, 0));

    unsigned int bi = bsti(yybuffer);

    printf("NOP    : %s\n", yybuffer);
    fwrite(&bi, 4, 1, file_out);

  }
  ;
value: NUMBER { $$ = $1 };
  | VAR {

      LNode *var = list_get(&varList, $1);
      if (var == NULL) var = list_get(&labelList, $1);
      if (var == NULL) {
        yyerror("Variable undefined");
      }

      union word aux = {0};

      unsigned int return_offset = ftell(file_out);
      fseek(file_out, var->offset, SEEK_SET);
      fread(&(aux.byte[0]), 1, 1, file_out);
      fread(&(aux.byte[1]), 1, 1, file_out);
      fread(&(aux.byte[2]), 1, 1, file_out);
      fread(&(aux.byte[3]), 1, 1, file_out);
      fseek(file_out, return_offset, SEEK_SET);

      $$ = var->offset;

  }
  ;

%%

int main(int argc, char **argv) {

    char *input_name, *out_name;

    if (argc >= 3 && !strcmp(argv[1], "-c")) {
        input_name = strdup(argv[2]);
        out_name = strdup(argv[3]);
    } else if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
        printf("----------------------------- Assembler Helper -----------------------------\n\n");
        printf("  -c \"input_file\" \"output_file\"\t\t\t-> Compile the input_file and generate the output_file\n");
        printf("\n");
    } else {
        printf("Wrong parameters.\n");
        return 1;
    }

    //yydebug = 1;

    if ((file_in  = fopen(input_name, "r"))  == NULL) return 1;
    if ((file_out = fopen(out_name,   "w+b")) == NULL) return 1;

    char buffer[500], buffer2[500];
    fscanf(file_in, "%s", buffer);
    while (strcmp(buffer, ".text")) {
        fscanf(file_in, "%s", buffer);
    }
    //a
    while (fscanf(file_in, "%s %[^\n]", buffer, buffer2) != EOF) {

        int foi = 0;
        for (int i = 0; i < strlen(buffer2); i++) {
            if (buffer2[i] != ' ' || buffer2[i] != '\n') {
                if (buffer2[i] == '#') break;
                foi = 1;
            }
        }
        if (foi || !strcmp(buffer, "syscall") || !strcmp(buffer, "NOP")) line_count++;

        if (buffer[strlen(buffer) - 1] == ':') {
            buffer[strlen(buffer) - 1] = '\0';
            if (list_get(&labelList, buffer) == NULL)
                list_add(&labelList, buffer, (line_count - 1) * WORD_SIZE);
            else {
                printf("FAILED: Label \"%s\" already defined.\n", list_get(&labelList, buffer)->label);
                exit(1);
            }
        }
    }

    //list_print(&labelList);//

    rewind(file_in);
    yyin = file_in;
	yyparse();

    int end = -1;
    fwrite(&end, sizeof(end), 1, file_out);

    printf("Instruction counter: %d\n", line_count);

	fclose(file_out);
    fclose(file_in);
	return 0;
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}
