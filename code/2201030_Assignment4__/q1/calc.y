    %{
    #include <stdio.h>
    #include <stdlib.h>
    int div_by_zero = 0;
    int yylex(void);
    void yyerror();
    int flag = 0; 
    %}

    %union {
        int ival;
        double dval;
    }

    %token <ival> NUMBER
    %token <dval> FLOAT
    %token ADD SUB MUL DIV LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE

    %type <dval> E
    %type <dval> ArithmeticExpression

    %left ADD SUB
    %left MUL DIV
    %left LPAREN RPAREN
    %left LCURL RCURL
    %left LSQUARE RSQUARE

    %%
    ArithmeticExpression : E {
        if (div_by_zero == 0) {
            printf("Result = %f\n", $$);
        }
    };

    E:
        E ADD E       { $$ = $1 + $3; }
        | E SUB E     { $$ = $1 - $3; }
        | E MUL E     { $$ = $1 * $3; }
        | E DIV E     {
            if ($3 == 0) {
                printf("ERROR: Division by zero.\n");
                div_by_zero = 1;
                $$ = 0.0;
            } else {
                $$ = $1 / $3;
            }
        }
        | LPAREN E RPAREN { $$ = $2; }
        | LCURL E RCURL { $$ = $2; }
        | LSQUARE E RSQUARE { $$ = $2; }
        | NUMBER      { $$ = $1; }
        | FLOAT       { $$ = $1; }
        ;
    %%

    void main() {
        printf("Enter Arithmetic Expression: ");
        yyparse();
        if (flag == 0) {
            printf("Entered arithmetic expression is Valid.\n");
        } 
    }
    void yyerror() {
        printf("Entered arithmetic expression is Invalid.\n");
        flag = 1;
    }