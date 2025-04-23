auxilliary      be|bE|Be|BE|am|aM|Am|AM|is|iS|Is|IS|are|arE|Are|ARE|was|waS|Was|WAS|were|werE|Were|WERE|being|beinG|Being|BEING|been|beeN|Been|BEEN|do|dO|Do|DO|does|doeS|Does|DOES|did|diD|Did|DID|have|havE|Have|HAVE|has|haS|Has|HAS|had|haD|Had|HAD|having|havinG|Having|HAVING|shall|shalL|Shall|SHALL|should|shoulD|Should|SHOULD|will|wilL|Will|WILL|would|woulD|Would|WOULD|can|caN|Can|CAN|could|coulD|Could|COULD|may|maY|May|MAY|might|mighT|Might|MIGHT|must|musT|Must|MUST|ought|oughT|Ought|OUGHT

%%

[ \t\n]+                                                                                                ;
[a-zA-Z]+(ing|inG|iNg|iNG|Ing|InG|INg|ING)                                                              { printf("Verb: %s\n", yytext); }
[a-zA-Z0-9]+(being|beinG|Being|BEING|been|beeN|Been|BEEN|does|Does|doeS|DOES)[a-zA-Z0-9]+               ;
[a-zA-Z0-9]+(being|beinG|Being|BEING|been|beeN|Been|BEEN|does|Does|doeS|DOES)                           ;
(being|beinG|Being|BEING|been|beeN|Been|BEEN|does|Does|doeS|DOES)[a-zA-Z0-9]+                           ;
being|beinG|Being|BEING|been|beeN|Been|BEEN|does|Does|doeS|DOES                                         { printf("Verb: %s\n", yytext); }
[a-zA-Z0-9]+{auxilliary}[a-zA-Z0-9]+                                                                    ;
[a-zA-Z0-9]+{auxilliary}                                                                                ;
{auxilliary}[a-zA-Z0-9]+                                                                                ;
{auxilliary}                                                                                            { printf("Verb: %s\n", yytext); }
[a-zA-Z]+("an""aN"|"An"|"AN")[a-zA-Z]+                                                                  ;
[a-zA-Z]+("an"|"aN"|"An"|"AN")   `                                                                       ;
("an"|"aN"|"An"|"AN")[a-zA-Z]+                                                                          ;
("an"|"aN"|"An"|"AN")                                                                                   { printf("Article: %s\n", yytext); }
[a-zA-Z]+("a"|"an"|"the"|"A"|"aN"|"An"|"AN"|"thE"|"tHE"|"tHE"|"The"|"ThE"|"THe"|"THE")[a-zA-Z]+         ;
[a-zA-Z]+("a"|"an"|"the"|"A"|"aN"|"An"|"AN"|"thE"|"tHE"|"tHE"|"The"|"ThE"|"THe"|"THE")                  ;
("a"|"an"|"the"|"A"|"aN"|"An"|"AN"|"thE"|"tHE"|"tHE"|"The"|"ThE"|"THe"|"THE")[a-zA-Z]+                  ;
("a"|"an"|"the"|"A"|"aN"|"An"|"AN"|"thE"|"tHE"|"tHE"|"The"|"ThE"|"THe"|"THE")                           { printf("Article: %s\n", yytext); }
(.)                                                                                                     ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter the input sentence: \n");
    yylex();
    return 0;
}
