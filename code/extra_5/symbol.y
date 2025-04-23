%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

typedef struct {
    char *name;
    char *type;
} Symbol;

Symbol symtab[100];
int symcount = 0;

char *current_type = NULL;

void add_to_table(char* id) {
    if (!current_type) {
        fprintf(stderr, "Error: current_type is NULL for variable %s\n", id);
        exit(1);
    }
    symtab[symcount].name = strdup(id);
    symtab[symcount].type = strdup(current_type);
    symcount++;
}
%}

%union {
    char* str;
}

%token <str> ID
%token <str> INT FLOAT CHAR
%type <str> T

%%

S : D S
  | /* empty */
  ;

D : T id_list ';'
  ;

T : INT   { current_type = strdup($1); }
  | FLOAT { current_type = strdup($1); }
  | CHAR  { current_type = strdup($1); }
  ;

id_list : id_list ',' ID {
            add_to_table($3);
         }
        | ID {
            add_to_table($1);
        }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    printf("Enter declarations:\n");
    yyparse();

    printf("\n--- Symbol Table ---\n");
    printf("%-10s | %-10s\n", "Variable", "Type");
    printf("--------------------------\n");
    for (int i = 0; i < symcount; ++i) {
        printf("%-10s | %-10s\n", symtab[i].name, symtab[i].type);
    }

    return 0;
}
