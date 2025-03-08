%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
%}

%%

[a-z]+   { yylval.string = strdup(yytext); return VAR; } 
"+"      { return PLUS; }
"*"      { return STAR; }
"("      { return OPEN; }
")"      { return CLOSE; }
"$"       {return END;} 
[ \t\n]  ;
.        { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1; 
}