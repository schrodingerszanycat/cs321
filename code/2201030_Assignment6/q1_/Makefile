1: lex.yy.o y.tab.o
	gcc lex.yy.o y.tab.o -o 1

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.c: 1.l
	lex 1.l

y.tab.c y.tab.h: 1.y
	yacc -d 1.y

clean:
	rm -f lex.yy.c y.tab.c y.tab.h *.o 1
