# Compiler and tools
CC = gcc
LEX = flex
YACC = bison
PYTHON = python3

# Flags
CFLAGS = -Wall -g
LDFLAGS = -lfl

# Files
LEX_FILE = converter.l
YACC_FILE = converter.y
C_SOURCE = converter.tab.c lex.yy.c
OBJ_FILES = converter.tab.o lex.yy.o
OUTPUT_LIB = libenglishtosql.so

# Targets
all: $(OUTPUT_LIB)

$(OUTPUT_LIB): $(OBJ_FILES)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

converter.tab.c converter.tab.h: $(YACC_FILE)
	$(YACC) -d -o converter.tab.c $<

lex.yy.c: $(LEX_FILE) converter.tab.h
	$(LEX) -o $@ $<

lex.yy.c lex.yy.h: converter.l
	flex --header-file=lex.yy.h converter.l

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) converter.tab.c converter.tab.h lex.yy.c $(OUTPUT_LIB)

run_gui:
	$(PYTHON) converter_gui.py
