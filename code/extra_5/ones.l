%{
#include "ones.tab.h"
#include <string.h>

%}

%%
[01]+           { yylval.str = strdup(yytext); return BINARY; }
"\."            { return '.'; }
[ \t\r\n]+      ;
.               { printf("Invalid character: %s \n", yytext); }
%%
int yywrap() { return 1; }
