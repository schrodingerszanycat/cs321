%{
#include <stdio.h>
%}

%%

[a-z]                           { printf("%s\n", yytext) ; } 
[ \t\n]+                        ;
(.)                             ;

%%

int main() {
    printf("Enter input: \n") ;
    yylex();
    return 0;
}

int yywrap() {                                        
    return 1;
}