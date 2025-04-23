%{
#include "inf_to_post.tab.h"
#include <stdio.h>


%}

%%
[0-9]+          { yylval = yytext[0]; return ID; }
[ \t]           ;  // ignore spaces/tabs
"+"             { return '+'; }
"*"             { return '*'; }
"\n"            { return '\n'; }
.               { return yytext[0]; }
%%
int yywrap() { return 1; }
