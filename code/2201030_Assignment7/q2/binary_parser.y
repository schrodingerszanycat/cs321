%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char* s);
int yylex(void);
%}

%union {
    int intval;
    double floatval;
    struct {
        double value;
        int position;
    } fracval;
}

%token <intval> BIT
%token DOT EOL

%type <intval> binary_integer
%type <fracval> binary_fraction
%type <floatval> binary

%%

start: binary EOL { 
    printf("Decimal equivalent: %.10g\n", $1); 
    return 0;
}
;

binary: binary_integer { 
    $$ = $1; 
}
| binary_integer DOT binary_fraction { 
    $$ = $1 + $3.value; 
}
;

binary_integer: BIT { 
    $$ = $1; 
}
| binary_integer BIT { 
    $$ = $1 * 2 + $2; 
}
;

binary_fraction: BIT { 
    $$.value = $1 * pow(2, -1);
    $$.position = 1;
}
| binary_fraction BIT { 
    $$.position = $1.position + 1;
    $$.value = $1.value + $2 * pow(2, -$$.position);
}
;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter a binary number: ");
    yyparse();
    return 0;
}