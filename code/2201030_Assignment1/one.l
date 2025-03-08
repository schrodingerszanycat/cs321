%{
#include <stdio.h>
%}

articles a|A|an|An|aN|AN|the|The|tHe|thE|THe|tHE|ThE|THE

%%

[a-zA-Z]+(a|A|an|An|aN|AN)[a-zA-Z]+ | [a-zA-Z]+(a|A|an|An|aN|AN) | (a|A|an|An|aN|AN)[a-zA-Z]+        ;                              
(a|A|an|An|aN|AN)                                                                                    { printf("Article found: %s\n", yytext) ; }
[a-zA-Z]+{articles}[a-zA-Z]+ | [a-zA-Z]+{articles} | {articles}[a-zA-Z]+                             ;
{articles}                                                                                           { printf("Article found: %s\n", yytext) ; }
[ \t\n]+                                                                                             ;
(.)                                                                                                  ;

%%

int main() {
    printf("Enter input: \n") ;
    yylex();
    return 0;
}

int yywrap() {                                        
    return 1;
}
