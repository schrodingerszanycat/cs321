%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"  

extern YYSTYPE yylval;
%}

%%

[ \t\n]+        { /* Ignore whitespace */ }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
[0-9]+          { 
                    yylval.iValue = atoi(yytext); 
                    return INTEGER; 
                }
[a-zA-Z][a-zA-Z0-9_]*  { 
                    yylval.sValue = strdup(yytext);
                    return IDENTIFIER; 
                }
"="             { return ASSIGN; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
";"             { return ';'; }
.               { /* Ignore unrecognized characters */ }
<<EOF>>         { return END_OF_FILE; }

%%

int yywrap(void) {
    return 1;
}