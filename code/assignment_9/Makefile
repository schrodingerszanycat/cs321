# Makefile for Three-Address Code Generator

# Compiler and flags
CC = cc
YACC = yacc
CFLAGS = -Wall
LEX = lex
LFLAGS = -ll

# Output files for YACC/LEX
YTAB = y.tab
LEXOUT = lex.yy

# Targets
TARGET = compiler

all: $(TARGET)

$(TARGET): $(LEXOUT).o $(YTAB).o
	$(CC) $(CFLAGS) $(LEXOUT).o $(YTAB).o -o $(TARGET) $(LFLAGS)

$(YTAB).c $(YTAB).h: compiler.y
	$(YACC) -d compiler.y

$(LEXOUT).c: compiler.l $(YTAB).h
	$(LEX) compiler.l

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(YTAB).c $(YTAB).h $(LEXOUT).c *.o

.PHONY: all clean
