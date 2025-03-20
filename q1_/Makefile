CC = gcc
CFLAGS = -Wall -g

all: parser

y.tab.c y.tab.h: parser.y
	yacc -d parser.y

lex.yy.c: lexer.l y.tab.h
	flex lexer.l

parser: lex.yy.c y.tab.c
	$(CC) $(CFLAGS) -o parser y.tab.c lex.yy.c -lfl

clean:
	rm -f parser y.tab.c y.tab.h lex.yy.c