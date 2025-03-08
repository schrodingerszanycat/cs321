%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
%}

%%

[a-z]+   { yylval.string = strdup(yytext); return IDENTIFIER; } 
"+"      { return PLUS; }
"*"      { return TIMES; }
"("      { return LPAREN; }
")"      { return RPAREN; }
"$"       {return ENDMARKER;} 
[ \t\n]  ;
.        { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1; 
}
