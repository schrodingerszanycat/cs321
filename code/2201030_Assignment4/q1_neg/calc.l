%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern YYSTYPE yylval;
%}

%%
[0-9]+\.[0-9]+ {
    yylval.dval = atof(yytext);
    return FLOAT;
}

[0-9]+ {
    yylval.ival = atoi(yytext);
    return NUMBER;
}

"+"     return ADD;
"-"     return SUB;
"*"     return MUL;
"/"     return DIV;
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