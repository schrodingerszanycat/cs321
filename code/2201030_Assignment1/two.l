%{
#include <stdio.h>
%}

articles a|A|an|An|aN|AN|the|The|tHe|thE|THe|tHE|ThE|THE
primary_aux be|Be|bE|BE|am|Am|aM|AM|is|Is|iS|IS|are|Are|aRe|ARE|was|Was|wAs|WAS|were|Were|wEre|WERE|being|Being|bEing|BEing|been|Been|bEen|BEen|does|Does|dOes|DOES|do|Do|dO|DO|did|Did|dId|DID|has|Has|hAs|HAS|have|Have|hAve|HAVE|had|Had|hAd|HAD
modal_aux can|Can|cAn|CAN|could|Could|cOuld|COULD|will|Will|wIll|WILL|would|Would|wOuld|WOULD|shall|Shall|sHall|SHALL|should|Should|sHould|SHOULD|may|May|mAy|MAY|might|Might|mIght|MIGHT|must|Must|mUst|MUST

%%
[a-zA-Z]+(a|A|an|An|aN|AN)[a-zA-Z]+ | [a-zA-Z]+(a|A|an|An|aN|AN) | (a|A|an|An|aN|AN)[a-zA-Z]+        ;                              
(a|A|an|An|aN|AN)                                                                                    { printf("Article found: %s\n", yytext); }
[a-zA-Z]+{articles}[a-zA-Z]+ | [a-zA-Z]+{articles} | {articles}[a-zA-Z]+                             ;
{articles}                                                                                           { printf("Article found: %s\n", yytext) ; }
[a-zA-Z0-9]+{primary_aux}[a-zA-Z0-9]+ | [a-zA-Z0-9]+{primary_aux} | {primary_aux}[a-zA-Z0-9]+        ;
{primary_aux}                                                                                        { printf("Verb found: %s\n", yytext) ; }
[a-zA-Z0-9]+{modal_aux}[a-zA-Z0-9]+ | [a-zA-Z0-9]+{modal_aux} | {modal_aux}[a-zA-Z0-9]+              ;
{modal_aux}                                                                                          { printf("Verb found: %s\n", yytext) ; }
[a-zA-Z]+(ing|inG|iNg|iNG|Ing|InG|INg|ING)                                                           { printf("Verb found: %s\n", yytext) ; }
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