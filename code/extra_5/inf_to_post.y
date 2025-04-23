%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
extern char *yytext;

%}

%token ID

%%
S : E '\n'    { printf("\n"); }
  ;

E : E '+' T   { printf("+ "); }
  | T         { }
  ;

T : T '*' F   { printf("* "); }
  | F         { }
  ;

F : ID        { printf("%c ", yytext[0]); }
  ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
int main() {
    printf("Enter infix expression: ");
    yyparse();
    return 0;
}
