%{
// conflict.y
#include <stdio.h>
#include <stdlib.h>

// Function prototypes for lexer and error handler
int yylex();
void yyerror(const char *s);
%}

// Declare tokens
%token IF THEN ELSE ID ASSIGN SEMI

// Define the start symbol
%start program

%% /* Grammar Rules */

program: stmt SEMI { printf("Parsing successful (Conflict version).\n"); }
       ;

stmt: IF ID THEN stmt        /* Rule 1: Potential conflict source */
    | IF ID THEN stmt ELSE stmt /* Rule 2 */
    | ID ASSIGN ID          /* Rule 3: A simple statement */
    ;

%% /* C Code Section */

void yyerror(const char *s) {
    // Simple error reporting function
    fprintf(stderr, "Syntax error: %s\n", s);
    exit(1); // Exit on error
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