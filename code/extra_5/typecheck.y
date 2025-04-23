%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

enum { TYPE_INT, TYPE_BOOL, TYPE_ERROR };
%}

%union {
    int type;
}

%token <type> DIGIT TRUE FALSE
%token EQ
%type <type> E

%left EQ
%left '+'


%%

input:
    E { 
        if ($1 != TYPE_ERROR) {
            printf("Type check successful: %s\n", $1 == TYPE_INT ? "int" : "bool");
        } else {
            printf("Type error detected.\n");
        }
    }
;

E : E '+' E
    {
        if ($1 == TYPE_INT && $3 == TYPE_INT)
            $$ = TYPE_INT;
        else {
            printf("Error: '+' operator requires integers\n");
            $$ = TYPE_ERROR;
        }
    }
  | E EQ E
    {
        if (($1 == TYPE_INT || $1 == TYPE_BOOL) && $1 == $3)
            $$ = TYPE_BOOL;
        else {
            printf("Error: '==' operator requires operands of same type (int/bool)\n");
            $$ = TYPE_ERROR;
        }
    }
  | '(' E ')'
    { $$ = $2; }

  | DIGIT
    { $$ = TYPE_INT; }

  | TRUE
    { $$ = TYPE_BOOL; }

  | FALSE
    { $$ = TYPE_BOOL; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    printf("Enter expression:\n");
    yyparse();
    return 0;
}
