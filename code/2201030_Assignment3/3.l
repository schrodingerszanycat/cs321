%{
#include <stdio.h>
#include <string.h>

int ddl_count = 0;
int dml_count = 0;

char* ddl_keywords[] = {
    "CREATE", "DROP", "ALTER", "TRUNCATE", "COMMENT", "RENAME", NULL
};

char* dml_keywords[] = {
    "INSERT", "UPDATE", "DELETE", "LOCK", NULL
};

int is_keyword(char* word, char* keywords[]) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
%}

%%

[A-Za-z]+   { 
                if (is_keyword(yytext, ddl_keywords)) {
                    ddl_count++;
                } 
                else if (is_keyword(yytext, dml_keywords)) {
                    dml_count++;
                }
            }

[ \t\n]+                ;
(.)                     ;
%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file) {
            yyin = file;
            yylex();
            fclose(file);
        } 
        else {
            fprintf(stderr, "Error opening input file.\n");
            return 1;
        }
    } 
    else {
        fprintf(stderr, "Usage: %s <input-file>.sql\n", argv[0]);
        return 1;
    }
    printf("Number of DDL queries: %d\n", ddl_count);
    printf("Number of DML queries: %d\n", dml_count);
    return 0;
}

int yywrap() {
    return 1;
}
