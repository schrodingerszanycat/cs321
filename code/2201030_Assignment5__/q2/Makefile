.PHONY: all clean

all: parser

parser: lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -o parser

y.tab.c y.tab.h: parser.y
	yacc -d parser.y

lex.yy.c: parser.l y.tab.h
	flex parser.l

clean:
	rm -f lex.yy.c y.tab.c y.tab.h parser