# Makefile for English to SQL Converter

# Tools
CC = gcc
LEX = flex
YACC = bison
RM = rm -f

# Compiler/Linker Flags
CFLAGS = -g -Wall -Wno-unused-function # Add -g for debugging, -Wall for warnings
LDFLAGS = -lfl # Link with the flex library (often needed for yywrap or main)

# Source Files
LEX_SRC = sql_converter.l
YACC_SRC = sql_converter.y
MAIN_SRC = main.c

# Generated Files
LEX_GEN_C = lex.yy.c
YACC_GEN_C = sql_converter.tab.c
YACC_GEN_H = sql_converter.tab.h

# Object Files
OBJS = main.o $(LEX_GEN_C:.c=.o) $(YACC_GEN_C:.c=.o)

# Target Executable
TARGET = converter

# Default target
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile main.c (depends on the generated header)
main.o: $(MAIN_SRC) $(YACC_GEN_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile the generated lexer C code (depends on the generated header)
lex.yy.o: $(LEX_GEN_C) $(YACC_GEN_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile the generated parser C code
sql_converter.tab.o: $(YACC_GEN_C) $(YACC_GEN_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to generate the parser C code and header from the .y file
# Bison creates both .c and .h (-d flag)
$(YACC_GEN_C) $(YACC_GEN_H): $(YACC_SRC)
	$(YACC) -d $(YACC_SRC) -o $(YACC_GEN_C) # Use -o to explicitly name the C file

# Rule to generate the lexer C code from the .l file
$(LEX_GEN_C): $(LEX_SRC)
	$(LEX) -o $@ $<

# Clean up generated files
clean:
	$(RM) $(TARGET) $(OBJS) $(LEX_GEN_C) $(YACC_GEN_C) $(YACC_GEN_H) *.output

# Phony targets
.PHONY: all clean