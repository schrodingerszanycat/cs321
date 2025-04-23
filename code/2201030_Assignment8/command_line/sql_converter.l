/* sql_converter.l */
%{
#include <stdio.h>
#include <stdlib.h> // Add for atoi
#include <string.h>
#include "sql_converter.tab.h" // <-- CHANGE HERE

void yyerror(char *);
%}

%option nounput
%option noinput
%option noyywrap 

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
                           yylval.str = strdup(yytext + 1); /* Keep original logic */
                           if (yylval.str) {                /* Check strdup result */
                             yylval.str[yyleng - 2] = '\0';
                           } else {
                             perror("strdup failed");
                             exit(EXIT_FAILURE);
                           }
                           return STRING;
                         }
[0-9]+                   { yylval.num = atoi(yytext); return INTEGER; }
\.                       { return DOT; }
\,                       { return COMMA; }
[ \t\n]+                 ; /* Ignore whitespace and newlines */
.                        { fprintf(stderr, "Ignoring invalid character: %s\n", yytext); /* Ignore other characters but maybe warn */ }
%%

/* Remove yywrap if using %option noyywrap */
/*
int yywrap(void) {
    return 1;
}
*/

/* Note: yyerror is usually defined in the .y file, but can be here too.
   Let's keep it in the .y file as originally intended. */