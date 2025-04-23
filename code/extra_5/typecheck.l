%{
#include "typecheck.tab.h"
#include <string.h>
%}

%%
"true"      { return TRUE; }
"false"     { return FALSE; }
[0-9]+      { return DIGIT; }
"=="        { return EQ; }
"+"         { return '+'; }
"("         { return '('; }
")"         { return ')'; }
[ \t\n]+    ;  // Ignore whitespace
.           { printf("Invalid character: %s\n", yytext); return 0; }
%%
int yywrap() { return 1; }
