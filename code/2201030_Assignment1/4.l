%{
#include <stdio.h>
int char_cnt = 0;
int word_cnt = 0;
int space_cnt = 0;
int EOL_cnt = 0;
%}

%%

[^\t\n ]+   { word_cnt++;  char_cnt += yyleng; }  
[ \t]       { space_cnt++; char_cnt += yyleng; }
[\n]        { EOL_cnt++; char_cnt += yyleng; }

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file) {
            yyin = file; 
            yylex();
            printf("Number of characters : %d\n", char_cnt);
            printf("Number of words : %d\n", word_cnt);
            printf("Number of spaces: %d\n", space_cnt);
            printf("Number of EOL: %d\n", EOL_cnt);
            fclose(file);
        } else {
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }
}

int yywrap() {                                        
    return 1;
}