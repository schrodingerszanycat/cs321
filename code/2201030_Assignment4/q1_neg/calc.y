%{
#include <stdio.h>
#include <stdlib.h>

int div_by_zero = 0;
int yylex(void); // Declare the lexer function
void yyerror(const char *s); // Standard yyerror signature
int flag = 0; 
%}

// Define the types union
%union {
    int ival;
    double dval;
}

// Declare tokens and their types
%token <ival> NUMBER
%token <dval> FLOAT
%token ADD SUB MUL DIV LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE

// Declare non-terminal types
%type <dval> E
%type <dval> ArithmeticExpression

// Define operator precedence and associativity
%left ADD SUB
%left MUL DIV
%right UMINUS // Add precedence for unary minus (higher than MUL/DIV)

%%

// Start rule
ArithmeticExpression : E {
                        if (!flag) { // Only print result if no errors occurred (like div by zero or syntax error)
                            if (div_by_zero == 0) {
                                printf("Result = %f\n", $$);
                            }
                            // Validity is printed in main after successful parse or in yyerror on failure
                        }
                    };

E:
    E ADD E       { $$ = $1 + $3; }
    | E SUB E     { $$ = $1 - $3; } // Binary subtraction
    | E MUL E     { $$ = $1 * $3; }
    | E DIV E     {
                    if ($3 == 0.0) { // Use floating point comparison
                        fprintf(stderr, "ERROR: Division by zero.\n");
                        div_by_zero = 1;
                        YYERROR; // Trigger a parse error state
                    } else {
                        $$ = $1 / $3;
                    }
                  }
    | SUB E %prec UMINUS { $$ = -$2; } // Unary minus rule with UMINUS precedence
    | LPAREN E RPAREN { $$ = $2; }
    | LCURL E RCURL   { $$ = $2; }
    | LSQUARE E RSQUARE { $$ = $2; }
    | NUMBER          { $$ = (double)$1; } // Promote int NUMBER to double
    | FLOAT           { $$ = $1; }
    ;

%%

// Main function to drive the parser
int main() {
    printf("Enter Arithmetic Expression: ");
    if (yyparse() == 0 && div_by_zero == 0) { // yyparse returns 0 on success
        printf("Entered arithmetic expression is Valid.\n");
    } else if (flag == 1) {
        // Error message already printed by yyerror or division by zero check
        printf("Entered arithmetic expression is Invalid.\n");
    }
    // If div_by_zero happened but syntax was ok, yyparse might return 0,
    // but we still consider it invalid in terms of calculation.
    else if (div_by_zero != 0) {
         printf("Entered arithmetic expression is Invalid due to division by zero.\n");
    }

    return 0;
}

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
    flag = 1; // Set flag to indicate an error occurred
}