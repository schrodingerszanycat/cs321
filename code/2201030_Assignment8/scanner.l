%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.tab.h"

// Convert string to lowercase for case-insensitive matching
void lowercase(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
}
%}

%%
[ \t\n]+                    { /* Ignore whitespace and newlines */ }
[Pp]lease                   { /* Polite requests, ignore */ }
[Gg]ive[ \t]+me             { return GIVE; }
[Ss]how                     { return SHOW; }
[Uu]pdate                   { return UPDATE; }
[Tt]able                    { return TABLE_KEYWORD; }
[Ss]et                      { return SET; }
[Tt]he                      { /* Ignore */ }
[Aa]ll                      { return ALL; }
[Ii]nformation              { return INFORMATION; }
[Oo]f                       { /* Ignore */ }
[Ss]tudent[s]?              { yylval.strval = strdup("Student"); return TABLE; }
[Nn]ame                     { yylval.strval = strdup("name"); return COLUMN; }
[Rr]oll                     { yylval.strval = strdup("roll"); return COLUMN; }
[Nn]umber[s]?               { /* Ignore when following "roll" */ }
[Nn]o                       { return NO; }
[Cc]pi                      { yylval.strval = strdup("cpi"); return COLUMN; }
[Hh]aving                   { return HAVING; }
[Ww]hose                    { return WHOSE; }
[Ww]here                    { return WHERE; }
[Ii]s                       { /* Ignore */ }
[Tt]o                       { return TO; }
[Mm]ore[ \t]+than           { yylval.strval = strdup(">"); return COMP_OP; }
[Gg]reater[ \t]+than        { yylval.strval = strdup(">"); return COMP_OP; }
[Ll]ess[ \t]+than           { yylval.strval = strdup("<"); return COMP_OP; }
[Ee]qual[ \t]+to            { yylval.strval = strdup("="); return COMP_OP; }
[Ee]quals                   { yylval.strval = strdup("="); return COMP_OP; }
[Aa]nd                      { return AND; }
[Oo]r                       { return OR; }
[0-9]+                      { yylval.intval = atoi(yytext); return NUMBER; }
[0-9]+\.[0-9]+              { yylval.floatval = atof(yytext); return FLOAT; }
[a-zA-Z][a-zA-Z0-9_]*       { 
                              lowercase(yytext);
                              yylval.strval = strdup(yytext); 
                              return IDENTIFIER; 
                            }
\.                          { /* End of sentence, ignore */ }
","                         { return COMMA; }
.                           { /* Ignore any other character */ }
%%

int yywrap() {
    return 1;
}