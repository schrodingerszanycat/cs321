%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex(void);
extern char *yytext;
extern YY_BUFFER_STATE yy_create_buffer(FILE *file, int size);
extern void yy_switch_to_buffer(YY_BUFFER_STATE new_buffer);
extern void yy_delete_buffer(YY_BUFFER_STATE b);
extern YY_BUFFER_STATE yy_scan_string(const char *yy_str);
extern YY_BUFFER_STATE yy_current_buffer;
extern int yydebug;

#define MAX_ID 100

typedef struct {
    char* name;
    int value;
    int assigned; 
} Symbol;

Symbol symbolTable[MAX_ID];
int symbolCount = 0;
int evaluating = 0;
int yydebug = 0;


int findSymbol(char* name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i;
        }
    }
    symbolTable[symbolCount].name = strdup(name);
    symbolTable[symbolCount].value = 0;
    symbolTable[symbolCount].assigned = 0;
    return symbolCount++;
}

void setSymbolValue(char* name, int value) {
    int idx = findSymbol(name);
    symbolTable[idx].value = value;
    symbolTable[idx].assigned = 1;
}

int getSymbolValue(char* name) {
    int idx = findSymbol(name);
    if (!symbolTable[idx].assigned) {
        printf("Error: Value for %s not assigned.\n", name);
        exit(1);
    }
    return symbolTable[idx].value;
}

int yyerror(char* s) {
    fprintf(stderr, "Expression is invalid\n");
    return 0;
}

int yylex();
%}

%union {
    char* id;
    int num;
}

%token <id> ID
%token <num> NUM

%type <num> expr term factor

%left '+' '-'
%left '*' '/'

%%

program:
    expr { 
        if (evaluating) {
            printf("Final Result: %d\n", $1);
        }
    }
    ;

expr:
    expr '+' term { 
        if (evaluating) {
            $$ = $1 + $3;
            printf("Intermediate: %d + %d = %d\n", $1, $3, $$);
        } else {
            $$ = 0;  
        }
    }
    | expr '-' term { 
        if (evaluating) {
            $$ = $1 - $3;
            printf("Intermediate: %d - %d = %d\n", $1, $3, $$);
        } else {
            $$ = 0;
        }
    }
    | term { $$ = $1; }
    ;

term:
    term '*' factor { 
        if (evaluating) {
            $$ = $1 * $3;
            printf("Intermediate: %d * %d = %d\n", $1, $3, $$);
        } else {
            $$ = 0;
        }
    }
    | term '/' factor { 
        if (evaluating) {
            if ($3 == 0) {
                yyerror("Division by zero");
                YYABORT;
            }
            $$ = $1 / $3;
            printf("Intermediate: %d / %d = %d\n", $1, $3, $$);
        } else {
            $$ = 0;
        }
    }
    | factor { $$ = $1; }
    ;

factor:
    ID { 
        if (evaluating) {
            $$ = getSymbolValue($1);
        } else {
            findSymbol($1);
            $$ = 0;
        }
    }
    | NUM { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
    | '{' expr '}' { $$ = $2; }
    | '[' expr ']' { $$ = $2; }
    ;

%%

int main() {
    char inputExpr[1000];
    
    printf("Enter arithmetic grammar expression: ");
    fgets(inputExpr, 1000, stdin);
    inputExpr[strcspn(inputExpr, "\n")] = 0;

    yydebug = 1;

    YY_BUFFER_STATE buf1 = yy_scan_string(inputExpr);
    if (yyparse() == 0) {
        printf("Expression is valid.\n");

        for (int i = 0; i < symbolCount; i++) {
            if (!symbolTable[i].assigned) {
                int value;
                printf("Enter value for %s: ", symbolTable[i].name);
                scanf("%d", &value);
                if (value < 0) {
                    printf("Only positive integers allowed. Using 0 instead.\n");
                    value = 0;
                }
                setSymbolValue(symbolTable[i].name, value);
            }
        }
        while (getchar() != '\n');  

        evaluating = 1;
        YY_BUFFER_STATE buf2 = yy_scan_string(inputExpr);
        yyparse();
        yy_delete_buffer(buf2);
    } else {
        printf("Expression is invalid.\n");
    }
    yy_delete_buffer(buf1);
    return 0;
}