%{
#include <stdio.h>
%}

%%

[a-z]+                      { printf("Token : STRING; Lexeme : %s\n", yytext); }
"Reverse"                   { printf("Token : REVERSE; Lexeme : Reverse\n"); }
[ ]                         ;
[\t\n]                      { printf("Token and Lexeme : <newline>\n"); }
["#" | "(" | ")"]           { printf("Token and Lexeme : %s\n", yytext); }
(.)                         { printf("Error message.\n") ;}  

%%

int main() {
    printf("Enter input: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}