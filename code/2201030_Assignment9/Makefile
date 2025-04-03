CC = gcc
LEX = lex
YACC = yacc -d
CFLAGS = -Wall

compiler: y.tab.c lex.yy.c
	$(CC) $(CFLAGS) -o compiler y.tab.c lex.yy.c -lfl

y.tab.c: parser.y
	$(YACC) parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean:
	rm -f compiler y.tab.c y.tab.h lex.yy.c