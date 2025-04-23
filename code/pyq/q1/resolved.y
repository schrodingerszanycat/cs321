%{
// resolved.y
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IF THEN ELSE ID ASSIGN SEMI

/* --- Conflict Resolution --- */
/* Define precedence. Lower lines = higher precedence. */
/* %nonassoc means these tokens don't associate with themselves at this level */
/* We assign the rule 'IF ID THEN stmt' a lower precedence than ELSE */
%nonassoc LOWER_THAN_ELSE  /* A pseudo-token representing the precedence level */
%nonassoc ELSE             /* ELSE token itself */
/* --- End Resolution --- */


%start program

%% /* Grammar Rules */

program: stmt SEMI { printf("Parsing successful (Resolved version).\n"); }
       ;

stmt: IF ID THEN stmt %prec LOWER_THAN_ELSE /* Assign lower precedence to this rule */
    | IF ID THEN stmt ELSE stmt         /* This rule implicitly gets precedence of ELSE */
    | ID ASSIGN ID
    ;

%% /* C Code Section */

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
    exit(1);
}

int main() {
    printf("Enter statement (e.g., 'if a then if b then x=y else z=w;' or 'a=b;' ):\n");
    if (yyparse() == 0) {
        // Success message printed by grammar rule action
    } else {
        printf("Parsing failed.\n");
    }
    return 0;
}