/* simplest version of calculator */
%{
    #include <stdio.h>
%}

/* declare tokens */
%token VALUE
%token COMMA COLON 
%token OPCODE
%token REGISTER ADRESS
%token EOL QUOTE
%token ABS
%token ADD

%%

calclist: /* nothing */
  | calclist opcode EOL { printf("= %d\n", $2); }
  ;
opcode: 
  | OPCODE args     { $$ = 0 }
  ;
args: term
  | term COMMA args { $$ = 3 }
  ;
term: VALUE
  | ABS term  { $$ = $2 >= 0? $2 : - $2; }
  ;

%%

int main(int argc, char **argv) {
	yyparse();
	return 0;
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}
