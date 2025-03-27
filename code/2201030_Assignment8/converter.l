%{
#include <stdio.h>
#include <string.h>
#include "converter.tab.h"

void yyerror(char *);
%}

%option nounput
%option noinput

%%
[Pp]lease                { return PLEASE; }
give|show|display        { return SHOW; }
me                       { return ME; }
the                      { return THE; }
of                       { return OF; }
all                      { return ALL; }
information              { return INFORMATION; }
student(s)?              { return STUDENT; }
whose                    { return WHOSE; }
having                   { return HAVING; }
with                     { return WITH; }
name                     { yylval.str = strdup("name"); return NAME; }
roll                     { yylval.str = strdup("roll"); return ROLL; }
cpi                      { yylval.str = strdup("cpi"); return CPI; }
number(s)?               { return NUMBER; }
is                       { return IS; }
to                       { return TO; }
more[ \t]+than           { return MORE_THAN; }
less[ \t]+than           { return LESS_THAN; }
[aA][nN][dD]             { return AND; }
no                       { return NO; }
update                   { return UPDATE; }
delete                   { return DELETE; }
ordered                  { return ORDERED; }
by                       { return BY; }
descending               { return DESC; }
ascending                { return ASC; }
\"[^"]+\"               {
                           yylval.str = strdup(yytext + 1);
                           yylval.str[yyleng - 2] = '\0';
                           return STRING;
                         }
[0-9]+                   { yylval.num = atoi(yytext); return INTEGER; }
\.                       { return DOT; }
\,                       { return COMMA; }
[ \t\n]+                 ;
.                        { /* Ignore other characters */ }
%%

int yywrap(void) {
    return 1;
}
