%{
#include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*    { yylval.id = strdup(yytext); return ID; }  
[0-9]+                  { yylval.num = atoi(yytext); return NUM; }  
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"("                     { return '('; }
")"                     { return ')'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
"["                     { return '['; }
"]"                     { return ']'; }
[ \t\n]                 ; /* Ignore whitespace */
.                       { printf("Invalid character: %s\n", yytext); return 0; }

%%

int yywrap() {
    return 1;
}