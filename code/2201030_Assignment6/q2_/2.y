%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *error_message);
extern int yylex();
extern int yyparse();
extern FILE *yyin;

%}

%union {
    char *str;
}

%token <str> NOUN VERB ADJECTIVE ADVERB PREP UNKNOWN
%token ARTICLE CONJ DOT COMMA EOL

%start input

%%
/* Grammar rules */

input:          /* empty */
                | input sentence { printf("Valid.\n"); }
                | input error EOL { 
                    printf("Invalid sentence structure.\n"); 
                    yyerrok; 
                  }
                ;

sentence:       simple_sentence DOT EOL
                | compound_sentence DOT EOL
                ;

simple_sentence: noun_phrase verb_phrase
                ;

compound_sentence: simple_sentence COMMA CONJ simple_sentence
                ;

noun_phrase:    NOUN
                | ARTICLE NOUN
                | ARTICLE ADJECTIVE NOUN
                | ADJECTIVE NOUN
                ;

verb_phrase:    VERB
                | VERB ADVERB
                | VERB noun_phrase
                | VERB ADVERB noun_phrase
                | VERB prep_phrase
                | VERB ADVERB prep_phrase
                | VERB noun_phrase prep_phrase
                ;

prep_phrase:    PREP noun_phrase
                ;

%%

void yyerror(const char *error_message) {
    fprintf(stderr, "%s\n", error_message);
}


int main(int argc, char **argv) {
    printf("Enter sentences and end them with a fullstop: \n");
    yyparse();
    
    return 0;
}