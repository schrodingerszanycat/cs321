%{
#include "dec_to_bin.tab.h"
#include <stdlib.h>
#include <string.h>

char decimal_str[100];

%}

%%

[0-9]+("."[0-9]+)? { strcpy(decimal_str, yytext); return DECIMAL; }
[ \t\n]            ;
.                  { printf("Invalid character: %c\n", yytext[0]); exit(1); }

%%

int yywrap() {
    return 1;
}
