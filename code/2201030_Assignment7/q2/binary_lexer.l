%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

0       { yylval.intval = 0; return BIT; }
1       { yylval.intval = 1; return BIT; }
\.      { return DOT; }
\n      { return EOL; }
[ \t]   { /* Ignore whitespace */ }
.       { fprintf(stderr, "Invalid character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}