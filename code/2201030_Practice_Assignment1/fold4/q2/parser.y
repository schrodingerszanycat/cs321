%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char parseTable[MAX][MAX][MAX];
int firstSet[MAX][MAX], followSet[MAX][MAX];
int firstComputed = 0, followComputed = 0;
char nonTerminals[] = {'S', 'A', 'B'};
char terminals[] = {'a', 'b', '$'};
int ntCount = 3, tCount = 3;

char productions[4][10] = {
    "S→AB",
    "A→aA",
    "A→ε",
    "B→b"
};
int prodCount = 4;

void computeFirst();
void computeFollow();
void buildParseTable();
void printFirst();
void printFollow();
void printParseTable();
int parseInput();
int yylex(void);
void yyerror(const char *s);
%}

%union {
    char* str;
}

%token <str> TOKEN_A TOKEN_B
%token END

%%

start : S END { printf("Input buffer is accepted\n"); return 0; }
      | error END { printf("Input buffer is not accepted\n"); return 1; }
      ;

S : A B { printf("Used production: S→AB\n"); }
  ;

A : TOKEN_A A { printf("Used production: A→aA\n"); }
  | /* epsilon */ { printf("Used production: A→ε\n"); }
  ;

B : TOKEN_B { printf("Used production: B→b\n"); }
  ;

%%

void yyerror(const char *s) {
    printf("%s\n", s);
}

int main() {
    printf("Computing FIRST sets:\n");
    computeFirst();
    printFirst();

    printf("\nComputing FOLLOW sets:\n");
    computeFollow();
    printFollow();

    printf("\nConstructing Parse Table:\n");
    buildParseTable();
    printParseTable();

    printf("\nParsing input:\n");
    return yyparse();
}

void computeFirst() {
    if (firstComputed) return;
    firstComputed = 1;

    // Initialize FIRST sets
    for (int i = 0; i < ntCount; i++) firstSet[i][0] = 0;

    // FIRST(A) = {a, ε}
    firstSet[1][firstSet[1][0]++] = 'a';
    firstSet[1][firstSet[1][0]++] = 'e'; // Use 'e' instead of 'ε'

    // FIRST(B) = {b}
    firstSet[2][firstSet[2][0]++] = 'b';

    // FIRST(S) = FIRST(A) ∪ FIRST(B)
    for (int i = 1; i <= firstSet[1][0]; i++) firstSet[0][firstSet[0][0]++] = firstSet[1][i];
    for (int i = 1; i <= firstSet[2][0]; i++) firstSet[0][firstSet[0][0]++] = firstSet[2][i];
}

void computeFollow() {
    if (followComputed) return;
    followComputed = 1;

    // Initialize FOLLOW sets
    for (int i = 0; i < ntCount; i++) followSet[i][0] = 0;

    // FOLLOW(S) = {$}
    followSet[0][followSet[0][0]++] = '$';

    // FOLLOW(A) = FIRST(B) ∪ FOLLOW(S)
    for (int i = 1; i <= firstSet[2][0]; i++) followSet[1][followSet[1][0]++] = firstSet[2][i];
    for (int i = 1; i <= followSet[0][0]; i++) followSet[1][followSet[1][0]++] = followSet[0][i];

    // FOLLOW(B) = FOLLOW(S)
    for (int i = 1; i <= followSet[0][0]; i++) followSet[2][followSet[2][0]++] = followSet[0][i];
}

void buildParseTable() {
    // Clear parse table
    for (int i = 0; i < ntCount; i++)
        for (int j = 0; j < tCount; j++)
            parseTable[i][j][0] = '\0';

    // S → AB
    for (int i = 1; i <= firstSet[0][0]; i++) {
        char t = firstSet[0][i];
        for (int j = 0; j < tCount; j++)
            if (terminals[j] == t) strcpy(parseTable[0][j], "S→AB");
    }

    // A → aA
    for (int i = 1; i <= firstSet[1][0]; i++) {
        char t = firstSet[1][i];
        if (t != 'e') { // Use 'e' instead of 'ε'
            for (int j = 0; j < tCount; j++)
                if (terminals[j] == t) strcpy(parseTable[1][j], "A→aA");
        }
    }
    // A → ε (add to FOLLOW(A))
    for (int i = 1; i <= followSet[1][0]; i++) {
        char t = followSet[1][i];
        for (int j = 0; j < tCount; j++)
            if (terminals[j] == t) strcpy(parseTable[1][j], "A→ε");
    }

    // B → b
    for (int i = 1; i <= firstSet[2][0]; i++) {
        char t = firstSet[2][i];
        for (int j = 0; j < tCount; j++)
            if (terminals[j] == t) strcpy(parseTable[2][j], "B→b");
    }
}

void printFirst() {
    for (int i = 0; i < ntCount; i++) {
        printf("FIRST(%c) = {", nonTerminals[i]);
        for (int j = 1; j <= firstSet[i][0]; j++) {
            printf("%c", firstSet[i][j]);
            if (j < firstSet[i][0]) printf(", ");
        }
        printf("}\n");
    }
}

void printFollow() {
    for (int i = 0; i < ntCount; i++) {
        printf("FOLLOW(%c) = {", nonTerminals[i]);
        for (int j = 1; j <= followSet[i][0]; j++) {
            printf("%c", followSet[i][j]);
            if (j < followSet[i][0]) printf(", ");
        }
        printf("}\n");
    }
}

void printParseTable() {
    printf("Parse Table:\n");
    printf("    ");
    for (int j = 0; j < tCount; j++) printf("%c   ", terminals[j]);
    printf("\n");
    for (int i = 0; i < ntCount; i++) {
        printf("%c | ", nonTerminals[i]);
        for (int j = 0; j < tCount; j++) {
            printf("%-5s", parseTable[i][j]);
        }
        printf("\n");
    }
}