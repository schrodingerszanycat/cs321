%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

%}

WHITESPACE      [ \t]+
NEWLINE         [\n]

ARTICLES        [Tt]he|[Aa]|[Aa]n

NOUNS           [Cc]at|[Dd]og|[Bb]oy|[Gg]irl|[Tt]ree|[Hh]ouse|[Bb]ook
VERBS           [Rr]uns|[Jj]umps|[Ww]alks|[Rr]eads|[Ee]ats|[Ss]leeps|[Ii]s
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