%{

#include <stdio.h>
#include <string.h>
int is_compound = 0;

%}

connectors "and"|"And"|"aNd"|"anD"|"AND"|"ANd"|"aND"|"AnD"|"but"|"But"|"bUt"|"buT"|"BUT"|"BUt"|"bUT"|"BuT"|"or"|"Or"|"oR"|"OR"|"nor"|"Nor"|"nOr"|"noR"|"NOR"|"NOr"|"nOR"|"NoR"|"for"|"For"|"fOr"|"foR"|"FOR"|"FOr"|"fOR"|"FoR"|"yet"|"Yet"|"yEt"|"yeT"|"YET"|"YEt"|"yET"|"YeT"|"so"|"So"|"sO"|"SO"  

%%
\b{connectors}                            { is_compound = 1; }
[ \t\n]                                  ;
(.)                                      ;  

%%

int main() {
    printf("Enter sentence and press Ctrl + D.\n");
    yylex();
    if (is_compound) {
        printf("The sentence is compound.\n");
    } 
    else {
        printf("The sentence is simple.\n");
    }
    return 0;
}

int yywrap() {
    return 1;
}
