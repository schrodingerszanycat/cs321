%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

%}

%%
[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return TIMES; }
"/"         { return DIVIDE; }
"("         { return LPAREN; }
")"         { return RPAREN; }
[ \t\n]     { /* ignore whitespace */ }
.           { printf("Unrecognized character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}