%{
#include "y.tab.h" 
extern YYSTYPE yylval; 
%}

%%

"a"                  { yylval.string = strdup(yytext); return TERMINAL; }
"b"                  { yylval.string = strdup(yytext); return TERMINAL; }
"$"                  { return END_OF_STREAM; } 
"+"                  { return ADD; }
"*"                  { return MULTIPLY; } 
"("                  { return LEFT_PAREN; } 
")"                  { return RIGHT_PAREN; } 
[ \t\n]              ; // Ignore whitespace
.                    { printf("Unrecognized token: %s\n", yytext); }

%%

int yywrap()
{
    return 1;
}