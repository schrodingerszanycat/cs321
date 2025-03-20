calc: lex.yy.o y.tab.o
	gcc lex.yy.o y.tab.o -o calc

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.c: calc.l
	lex calc.l

y.tab.c y.tab.h: calc.y
	yacc -d calc.y

clean:
	rm -f lex.yy.c y.tab.c y.tab.h *.o calc
