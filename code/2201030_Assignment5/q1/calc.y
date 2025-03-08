%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
int flag = 0;
%}

%token LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE
%left LPAREN RPAREN
%left LCURL RCURL
%left LSQUARE RSQUARE

%start expression

%%

expression:
    /* empty */
    | group expression
    ;

group:
    LPAREN expression RPAREN
    | LCURL expression RCURL
    | LSQUARE expression RSQUARE
    ;

%%

int main() {
    printf("Enter Arithmetic Expression: ");
    yyparse();
    if (flag == 0) {
        printf("Entered arithmetic expression is Valid.\n");
    }
    return 0;
}

void yyerror(const char *s) {
    printf("Entered arithmetic expression is Invalid.\n");
    flag = 1;
}


