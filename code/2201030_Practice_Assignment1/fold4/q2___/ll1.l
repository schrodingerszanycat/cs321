%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
%}

%%

"a"   { yylval.string = strdup(yytext); return LOWER_A; }
"b"   { yylval.string = strdup(yytext); return LOWER_B; }
"$"   { return END; }
[ \t\n]  ;
.     { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}