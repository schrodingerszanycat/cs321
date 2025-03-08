ll1: lex.yy.o y.tab.o
	gcc lex.yy.o y.tab.o -o ll1

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.c: ll1.l
	lex ll1.l

y.tab.c y.tab.h: ll1.y
	yacc -d ll1.y

clean:
	rm -f lex.yy.c y.tab.c y.tab.h *.o ll1
