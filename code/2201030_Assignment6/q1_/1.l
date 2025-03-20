%{
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

"SELECT"    { return SELECT; }
"INSERT"    { return INSERT; }
"INTO"      { return INTO; }
"VALUES"    { return VALUES; }
"UPDATE"    { return UPDATE; }
"SET"       { return SET; }
"DELETE"    { return DELETE; }
"FROM"      { return FROM; }
"CREATE"    { return CREATE; }
"TABLE"     { return TABLE; }
"WHERE"     { return WHERE; }
"*"         { return STAR; }
"="         { return EQUALS; }
","         { return COMMA; }
";"         { return SEMICOLON; }
"("         { return LPAREN; }
")"         { return RPAREN; }
[0-9]+      { yylval.str = strdup(yytext); return NUMBER; }
'[^']*'     { yylval.str = strdup(yytext); return STRING; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return IDENTIFIER; }
[ \t\n]     ;
.           { printf("Invalid character: %c\n", yytext[0]); exit(1); }

%%
