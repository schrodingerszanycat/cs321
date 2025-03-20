2: lex.yy.o y.tab.o
	gcc lex.yy.o y.tab.o -o 2

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.c: 2.l
	lex 2.l

y.tab.c y.tab.h: 2.y
	yacc -d 2.y

clean:
	rm -f lex.yy.c y.tab.c y.tab.h *.o 2
