CC = gcc
YACC = yacc
LEX = lex
CFLAGS = -Wall

all: compiler

compiler: y.tab.c lex.yy.c
	$(CC) $(CFLAGS) -o compiler y.tab.c lex.yy.c -lfl

y.tab.c: parser.y
	$(YACC) -d parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean:
	rm -f compiler y.tab.c y.tab.h lex.yy.c *.o

test: compiler
	./compiler test_gcd.c > gcd_tac.txt
	./compiler test_interest.c > interest_tac.txt
	./compiler test_triangle.c > triangle_tac.txt