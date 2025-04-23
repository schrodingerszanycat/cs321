%{
#include "symbol.tab.h"
%}

%%
"int"       { yylval.str = strdup("int"); return INT; }
"float"     { yylval.str = strdup("float"); return FLOAT; }
"char"      { yylval.str = strdup("char"); return CHAR; }
","         { return ','; }
";"         { return ';'; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }
[ \t\r\n]+ ;  // skip whitespace
.           { printf("Invalid character: %s\n", yytext); return 0; }
%%
int yywrap() { return 1; }
