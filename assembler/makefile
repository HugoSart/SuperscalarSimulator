# part of the makefile
assembler: lexer.l parser.y
	bison -d parser.y
	flex lexer.l
	cc -o $@ parser.tab.c lex.yy.c bop.c op_def.c -lfl
