%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
extern YYSTYPE yylval;
%}

%%
a      { yylval.str = strdup(yytext); return TOKEN_A; }
b      { yylval.str = strdup(yytext); return TOKEN_B; }
\$     { return END; }
[ \t\n] ; /* Ignore whitespace */
.      { return yytext[0]; }
%%

int yywrap() {
    return 1;
}