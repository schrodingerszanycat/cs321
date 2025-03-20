%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern YYSTYPE yylval;
%}

%%
[0-9]+\.[0-9]+  {
    yylval.dval = atof(yytext);    
    return FLOAT;
}

[0-9]+  {
    yylval.ival = atoi(yytext);    
    return NUMBER;
}

[\t]                    ;
[\n]                    return 0;
.                       return yytext[0];
%%

int yywrap() {
    return 1;
}