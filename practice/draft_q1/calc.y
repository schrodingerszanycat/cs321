%{
#include <stdio.h>
int flag = 0;
int yylex(void);
void yyerror();
%}

%union {
    int ival;
    double dval;
}

%token <ival> NUMBER
%token <dval> FLOAT
%type <dval> E
%type <dval> ArithmeticExpression

%left '+' '-'
%left '*' '/'
%left '(' ')'
%left '{' '}'
%left '[' ']'


%%
ArithmeticExpression : E {
    printf("Result = %f\n", $$);
};

E : E '+' E      { $$ = $1 + $3; }
    | E '-' E    { $$ = $1 - $3; }
    | E '*' E    { $$ = $1 * $3; }           // TODO: ask if still to print expression valid or not when divided by 0
    | E '/' E    { if ($3 == 0) { printf("ERROR: Division by zero.\n"); YYABORT; } else { $$ = $1 / $3; } }
    | '(' E ')'  { $$ = $2; }
    | '{' E '}'  { $$ = $2; }
    | '[' E ']'  { $$ = $2; }
    | NUMBER { $$ = $1; }
    | FLOAT { $$ = $1; }
;

%%

void main() {
    printf("Enter Arithmetic Expression: ");
    yyparse();
    if (flag == 0)
        printf("Entered arithmetic expression is Valid.\n");
}

void yyerror() {
    printf("Entered arithmetic expression is Invalid.\n");
    flag = 1;
}
