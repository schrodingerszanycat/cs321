%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern YYSTYPE yylval;
%}

%%
"("     return LPAREN;
")"     return RPAREN;
"{"     return LCURL;
"}"     return RCURL;
"["     return LSQUARE;
"]"     return RSQUARE;
[\t ]+   ;
\n      return 0;
.       {
    fprintf(stderr, "Error: Illegal character '%s'\n", yytext);
    exit(1);
}
%%

int yywrap() {
    return 1;
}
