%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

int yywrap()
{
    return 1;
}

extern int yylex();

int column_count = 0;
int value_count = 0;
%}

%union
{
    char *str;
}

%token SELECT INSERT INTO VALUES UPDATE SET DELETE FROM CREATE TABLE WHERE
%token STAR EQUALS COMMA SEMICOLON LPAREN RPAREN
%token <str> IDENTIFIER NUMBER STRING

%%

query: select_statement SEMICOLON { printf("Valid SELECT query.\n"); }
    | insert_statement SEMICOLON {
        if (column_count != -1 && column_count != value_count) {
            yyerror("Number of columns and values do not match");
        } else {
            printf("Valid INSERT query.\n");
        }
        column_count = 0;
        value_count = 0;
    }
    | update_statement SEMICOLON { printf("Valid UPDATE query.\n"); }
    | delete_statement SEMICOLON { printf("Valid DELETE query.\n"); }
    | create_table_statement SEMICOLON { printf("Valid CREATE TABLE query.\n"); }

;

select_statement: SELECT columns FROM table where_clause;

columns: STAR
| column_list
;

column_list: IDENTIFIER {
    column_count = 1;
}
| column_list COMMA IDENTIFIER {
    column_count++;
}
;

table: IDENTIFIER;

where_clause: /* empty */
| WHERE condition
;

literal: NUMBER | STRING;

condition: IDENTIFIER EQUALS literal;

insert_statement: INSERT INTO table VALUES LPAREN value_list RPAREN {
        column_count = -1;
    }
    | INSERT INTO table LPAREN column_list RPAREN VALUES LPAREN value_list RPAREN
;

value_list: literal {
    value_count = 1;
}
| value_list COMMA literal {
    value_count++;
}
;

update_statement: UPDATE table SET assignments where_clause;

assignments: assignment
| assignments COMMA assignment
;

assignment: IDENTIFIER EQUALS literal;

delete_statement: DELETE FROM table where_clause;

create_table_statement: CREATE TABLE IDENTIFIER LPAREN column_defs RPAREN;

column_defs: column_def 
| column_defs COMMA column_def
;

column_def: IDENTIFIER IDENTIFIER;

%%
int main()
{
    yyparse();
    return 0;
}
