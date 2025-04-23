%{
// resolved.l
#include "resolved.tab.h" // Will include the new token definitions from resolved.y
%}

%%
[ \t\n]+        ; /* Ignore whitespace and newlines */

if              { return IF; }
then            { return THEN; }
else            { return ELSE; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
=               { return ASSIGN; }
;               { return SEMI; }
.               { fprintf(stderr, "Lexer error: Unexpected character '%c'\n", *yytext); } 
%%

int yywrap() {
    return 1;
}