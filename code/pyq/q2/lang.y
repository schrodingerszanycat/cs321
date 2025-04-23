/* lang.y: Yacc parser for the language a^m b^n c^n d^m */
%{
#include <stdio.h>
#include <stdlib.h>

// External declaration for the lexer function
extern int yylex();
// External declaration for the lexer's input buffer (optional, for error messages)
extern char *yytext;
// Function prototype for error reporting
void yyerror(const char *s);

// Counters for the tokens
int m_count = 0; // Count for 'a's and 'd's
int n_count = 0; // Count for 'b's and 'c's
int temp_c_count = 0; // Temporary counter for 'c's during parsing
int temp_d_count = 0; // Temporary counter for 'd's during parsing
%}

/* Declare tokens from Lex */
%token A B C D NL INVALID_CHAR

/* Define the start symbol */
%start program

%% /* Grammar rules start here */

program: /* empty */
       | program line
       ;

line:   valid_string NL { 
            printf("Input: Accepted (m=%d, n=%d)\n", m_count, n_count);
            // Reset counters for the next line
            m_count = 0; n_count = 0; temp_c_count = 0; temp_d_count = 0;
       }
      | NL { /* Empty line is valid (m=0, n=0) */
            printf("Input: Accepted (m=0, n=0)\n");
            m_count = 0; n_count = 0; temp_c_count = 0; temp_d_count = 0;
      }
      | error NL { /* Handles syntax errors or invalid counts detected by YYERROR */
            fprintf(stderr, "Input: Rejected (Syntax Error or Invalid Structure/Counts)\n");
            // Reset counters after error for the next line
            m_count = 0; n_count = 0; temp_c_count = 0; temp_d_count = 0;
            yyerrok; // Prevent cascading errors, try to recover at NL
      }
      ;

valid_string: a_sequence b_sequence c_sequence d_sequence {
                /* Semantic Check: Verify the counts */
                if (n_count != temp_c_count || m_count != temp_d_count) {
                    // If counts don't match, trigger a Yacc error.
                    // The 'error NL' rule above will catch this.
                    YYERROR; 
                }
                // If counts match, proceed. The message is printed in the 'line' rule.
            }
            ;

a_sequence: /* empty */ { m_count = 0; }
          | a_sequence A { m_count++; }
          ;

b_sequence: /* empty */ { n_count = 0; }
          | b_sequence B { n_count++; }
          ;

c_sequence: /* empty */ { temp_c_count = 0; }
          | c_sequence C { temp_c_count++; }
          ;

d_sequence: /* empty */ { temp_d_count = 0; }
          | d_sequence D { temp_d_count++; }
          ;

%% /* C code section */

// Error reporting function required by Yacc
void yyerror(const char *s) {
    // Yacc provides a generic "syntax error" message in 's'.
    // We print a slightly more user-friendly message, handled by the 'error NL' rule.
    // fprintf(stderr, "Parser Error: %s near '%s'\n", s, yytext); // You could add more detail here
}

// Main function to drive the parser
int main() {
    printf("Enter strings (one per line) conforming to a^m b^n c^n d^m (m, n >= 0):\n");
    if (yyparse() == 0) { // 0 means success (no fatal errors)
        printf("Parsing completed successfully.\n");
    } else {
        printf("Parsing failed.\n");
    }
    return 0;
}