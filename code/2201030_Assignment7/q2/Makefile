CC = gcc
YACC = yacc
LEX = lex
CFLAGS = -Wall
LDFLAGS = -lm

all: binary_converter

binary_converter: lex.yy.c y.tab.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

y.tab.c y.tab.h: binary_parser.y
	$(YACC) -d binary_parser.y

lex.yy.c: binary_lexer.l y.tab.h
	$(LEX) binary_lexer.l

clean:
	rm -f binary_converter lex.yy.c y.tab.c y.tab.h