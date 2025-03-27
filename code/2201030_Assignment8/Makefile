# Makefile for English to SQL Converter with GUI

CC = gcc
LEX = flex
YACC = bison
CFLAGS = -g -Wall -Wextra
MYSQL_CFLAGS = -I/usr/include/mysql
MYSQL_LIBS = -lmysqlclient
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)

# Default target - all versions
all: english_to_sql english_to_sql_gui

# Basic command-line version
english_to_sql: parser.tab.c lex.yy.c english_to_sql.o
	$(CC) $(CFLAGS) -o english_to_sql english_to_sql.o parser.tab.c lex.yy.c -lfl

english_to_sql.o: english_to_sql.c
	$(CC) $(CFLAGS) -c english_to_sql.c

english_to_sql.c:
	echo 'int parser_main(); int main() { return parser_main(); }' > english_to_sql.c

parser.tab.c: parser.y
	$(YACC) -d parser.y

lex.yy.c: scanner.l
	$(LEX) scanner.l

# GUI version with database connection
english_to_sql_gui: y_gui.tab.c lex_gui.yy.c db_connector.o gui.o
	$(CC) $(CFLAGS) $(MYSQL_CFLAGS) $(GTK_CFLAGS) -o english_to_sql_gui gui.o y_gui.tab.c lex_gui.yy.c db_connector.o -lfl $(MYSQL_LIBS) $(GTK_LIBS)

y_gui.tab.c: parser.y
	$(YACC) -d -o y_gui.tab.c parser.y

lex_gui.yy.c: scanner.l
	$(LEX) -o lex_gui.yy.c scanner.l

db_connector.o: db_connector.c
	$(CC) $(CFLAGS) $(MYSQL_CFLAGS) -c db_connector.c

gui.o: gui.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c gui.c

clean:
	rm -f english_to_sql english_to_sql_gui english_to_sql.c
	rm -f parser.tab.c lex.yy.c parser.tab.h
	rm -f y_gui.tab.c lex_gui.yy.c y_gui.tab.h
	rm -f *.o *~