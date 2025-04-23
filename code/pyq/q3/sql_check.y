%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

int invalid = 0;

%}

%union {
    char* str;
}

%token SELECT_TOKEN FROM WHERE AND
%token IDENTIFIER NUMBER
%token GE LE QUOTE COMMENT SEMICOLON INVALID

%left '+' '-'
%left '*' '/'

%start stmt

%%

stmt:
    SELECT_TOKEN select_list FROM IDENTIFIER WHERE condition
    {
        if (!invalid)
            printf("SQL select statement consist by correct arithmetic expression.\n");
        else
            printf("SQL select statement is incorrect or consists by incorrect arithmetic expression.\n");
    }
    ;

select_list:
    IDENTIFIER
    | '*'
    ;

condition:
    condition AND condition
    | IDENTIFIER '=' quoted_expr
    | IDENTIFIER GE quoted_expr
    | IDENTIFIER LE quoted_expr
    | IDENTIFIER '>' quoted_expr
    | IDENTIFIER '<' quoted_expr
    ;

quoted_expr:
    QUOTE expr QUOTE
    | QUOTE error QUOTE { invalid = 1; }
    ;

expr:
    expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | IDENTIFIER
    | NUMBER
    ;

%%

void yyerror(const char *s) {
    invalid = 1;
}

int main() {
    printf("Enter SQL SELECT statement:\n");
    yyparse();
    return 0;
}
