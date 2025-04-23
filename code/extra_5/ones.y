%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

int countOnes(const char *s) {
    int count = 0;
    for (int i = 0; s[i]; i++)
        if (s[i] == '1') count++;
    return count;
}

%}

%union {
    char *str;
    int count;
}

%token <str> BINARY
%type <count> input binary_number integer_part fractional_part

%%

input:
    binary_number {
        printf("Number of 1's: %d\n", $1);
    }
    ;

binary_number:
    integer_part                { $$ = $1; }
    | integer_part '.' fractional_part {
        $$ = $1 + $3;
    }
    ;

integer_part:
    BINARY {
        $$ = countOnes($1);
        free($1);
    }
    ;

fractional_part:
    BINARY {
        $$ = countOnes($1);
        free($1);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter a binary number: ");
    yyparse();
    return 0;
}
