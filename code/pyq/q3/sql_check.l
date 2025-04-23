%{
#include "sql_check.tab.h"
#include <string.h>
%}

%%
SELECT              { return SELECT_TOKEN; }
FROM                { return FROM; }
WHERE               { return WHERE; }
AND                 { return AND; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENTIFIER; }
"="                 { return '='; }
">="                { return GE; }
"<="                { return LE; }
">"                 { return '>'; }
"<"                 { return '<'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"+"                 { return '+'; }
"-"                 { return '-'; }
"("                 { return '('; }
")"                 { return ')'; }
[0-9]+(\.[0-9]+)?   { return NUMBER; }
"'"                 { return QUOTE; }
"--"                { return COMMENT; }
";"                 { return SEMICOLON; }
[ \t\r\n]+          ;  // Ignore whitespace
.                   { return INVALID; }
%%
int yywrap() { return 1; }
