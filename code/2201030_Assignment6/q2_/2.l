%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}
WHITESPACE      [ \t]+
NEWLINE         [\n]
ARTICLES        [Tt]he|[Aa]|[Aa]n
NOUNS           [Cc]at|[Dd]og|[Bb]oy|[Gg]irl|[Tt]ree|[Hh]ouse|[Bb]ook
VERBS           [Rr]uns|[Jj]umps|[Ww]alks|[Rr]eads|[Ee]ats|[Ss]leeps|[Rr]un|[Jj]ump|[Ww]alk|[Rr]ead|[Ee]at|[Ss]leep
AUXILIARIES     [Ii]s|[Aa]re|[Aa]m|[Ww]as|[Ww]ere|[Hh]as|[Hh]ave|[Hh]ad|[Cc]an|[Cc]ould|[Mm]ay|[Mm]ight|[Mm]ust|[Ss]hall|[Ss]hould|[Ww]ill|[Ww]ould|[Dd]o|[Dd]oes|[Dd]id
ADJECTIVES      [Bb]ig|[Ss]mall|[Ff]ast|[Ss]low|[Hh]appy|[Ss]ad
ADVERBS         [Qq]uickly|[Ss]lowly|[Hh]appily|[Ss]adly
PREPOSITIONS    [Oo]n|[Uu]nder|[Ii]n|[Aa]bove|[Nn]ear
CONJUNCTIONS    [Aa]nd|[Bb]ut|[Oo]r
PUNCTUATION_DOT [.]
PUNCTUATION_COMMA [,]
%%
{WHITESPACE}        ; /* Ignore whitespace */
{NEWLINE}           { return EOL; }
{ARTICLES}          { return ARTICLE; }
{NOUNS}             { yylval.str = strdup(yytext); return NOUN; }
{VERBS}             { yylval.str = strdup(yytext); return VERB; }
{AUXILIARIES}       { yylval.str = strdup(yytext); return AUX; }
{ADJECTIVES}        { yylval.str = strdup(yytext); return ADJECTIVE; }
{ADVERBS}           { yylval.str = strdup(yytext); return ADVERB; }
{PREPOSITIONS}      { yylval.str = strdup(yytext); return PREP; }
{CONJUNCTIONS}      { return CONJ; }
{PUNCTUATION_DOT}   { return DOT; }
{PUNCTUATION_COMMA} { return COMMA; }
[A-Za-z]+           { 
                      printf("Lexical Error: Unknown word: %s\n", yytext); 
                      return UNKNOWN; 
                    }
.                   { 
                      printf("Lexical Error: Unrecognized character: %s\n", yytext); 
                    }
%%
int yywrap() {
    return 1; 
}