%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}

%%
[0-9]+      { yylval.value = atoi(yytext); return INTEGER; }
"+"         { return ADD; }
"-"         { return SUBTRACT; }
"*"         { return MULTIPLY; }
"/"         { return DIVIDE; }
"("         { return OPEN_PAREN; }
")"         { return CLOSE_PAREN; }
[ \t\n]     { /* ignore whitespace */ }
.           { printf("Unknown character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

