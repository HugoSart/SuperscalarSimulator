/* recognize tokens for the calculator and print them out */

%{
  #include "parser.tab.h"
  int yylval;
%}

%%

"add"  { return OPCODE; }
"|"	   { return ABS; }
"#".*
","	   { return COMMA; }
[0-9]+ { yylval = atoi(yytext); return VALUE; }
\n     { return EOL; }
[ \t]  { /* ignore whitespace */ }
\"	   { return QUOTE; }
.      { printf("Mystery character %c\n", *yytext); }

%%

