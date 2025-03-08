%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Global variables
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

// Stack and parsing variables
int top = 0;
int t = 3, nt = 3, cr = 4, count = 0;
char FIRST[100][100], FOLLOW[100][100];
char T[100] = {'a', 'b', '$'}, NT[100] = {'S', 'A', 'B'}, G[100][10], STACK[100];
int LL1[100][100];

// Function declarations
void computeFirst();
void computeFollow();
void buildParseTable();
void printFirst();
void printFollow();
void printParseTable();
void add_symbol(char *, char);
void FIND_FIRST(char *, char);
void FIND_FOLLOW(char *, char);
void FIRST_SHOW();
void FOLLOW_SHOW();
int CREATE_LL1_TABLE();
void PARSING_TABLE_SHOW(int);
void LL1_PARSER(char *);
int yylex(void);
void yyerror(const char *s);

%}

// Token declarations
%token TOKEN_A TOKEN_B END

%%

// Grammar rules
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

// C code section

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
    char input[100];
    printf("Enter input string: ");
    scanf("%s", input);
    LL1_PARSER(input);

    return 0;
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

void add_symbol(char *arr, char ch) {
    int i, flag = 0;
    for (i = 0; arr[i] != '\0'; i++) {
        if (ch == arr[i]) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        arr[count++] = ch;
        arr[count] = '\0';
    }
}

void FIND_FIRST(char *arr, char ch) {
    int i;
    if (!isupper(ch))
        add_symbol(arr, ch);
    else {
        for (i = 0; i < cr; i++) {
            if (ch == G[i][0]) {
                if (G[i][3] == '!')
                    add_symbol(arr, G[i][3]);
                else
                    FIND_FIRST(arr, G[i][3]);
            }
        }
    }
}

void FIND_FOLLOW(char arr[], char ch) {
    int i, j, k, l, fl = 1, flag = 1;
    if (ch == G[0][0])
        add_symbol(arr, '$');
    for (i = 0; i < cr; i++) {
        for (j = 3; G[i][j] != '\0' && flag == 1; j++) {
            if (ch == G[i][j]) {
                flag = 0;
                if (G[i][j + 1] != '\0' && isupper(G[i][j + 1])) {
                    for (k = 0; k < nt; k++) {
                        if (NT[k] == G[i][j + 1]) {
                            for (l = 0; FIRST[k][l] != '\0'; l++) {
                                if (FIRST[k][l] != '\0' && FIRST[k][l] != '!') {
                                    add_symbol(arr, FIRST[k][l]);
                                }
                                if (FIRST[k][l] == '!')
                                    fl = 0;
                            }
                            break;
                        }
                    }
                } else if (G[i][j + 1] != '\0' && !isupper(G[i][j + 1])) {
                    add_symbol(arr, G[i][j + 1]);
                }
                if ((G[i][j + 1] == '\0' || fl == 0) && G[i][0] != ch) {
                    fl = 1;
                    FIND_FOLLOW(arr, G[i][0]);
                }
            }
        }
    }
}

void FIRST_SHOW() {
    int i, j;
    char arr[100];
    for (i = 0; i < nt; i++) {
        arr[0] = '\0';
        FIND_FIRST(arr, NT[i]);
        for (j = 0; arr[j] != '\0'; j++) {
            FIRST[i][j] = arr[j];
        }
        FIRST[i][j] = '\0';
        count = 0;
    }
    printf("\nFIRST:\n\n");
    for (i = 0; i < nt; i++) {
        printf("FIRST( %c ): { ", NT[i]);
        for (j = 0; FIRST[i][j + 1] != '\0'; j++)
            printf(" %c,", FIRST[i][j]);
        printf(" %c }", FIRST[i][j]);
        printf("\n");
    }
}

void FOLLOW_SHOW() {
    int i, j;
    char arr[100];
    for (i = 0; i < nt; i++) {
        count = 0;
        arr[0] = '\0';
        FIND_FOLLOW(arr, NT[i]);
        for (j = 0; arr[j] != '\0'; j++) {
            FOLLOW[i][j] = arr[j];
        }
        FOLLOW[i][j] = '\0';
    }
    printf("\nFOLLOW:\n\n");
    for (i = 0; i < nt; i++) {
        printf("FOLLOW( %c ): { ", NT[i]);
        for (j = 0; FOLLOW[i][j + 1] != '\0'; j++)
            printf(" %c,", FOLLOW[i][j]);
        printf(" %c }", FOLLOW[i][j]);
        printf("\n");
    }
}

int CREATE_LL1_TABLE() {
    int i, j, k, fl, pos, flag = 0;
    char arr[100];
    for (i = 0; i < cr; i++) {
        arr[0] = '\0';
        count = 0;
        FIND_FIRST(arr, G[i][3]);
        for (j = 0; j < count; j++) {
            if (arr[j] == '!') {
                FIND_FOLLOW(arr, G[i][0]);
                break;
            }
        }
        for (k = 0; k < nt; k++) {
            if (NT[k] == G[i][0]) {
                pos = k;
                break;
            }
        }
        for (j = 0; j < count; j++) {
            if (arr[j] != '!') {
                for (k = 0; k < t; k++) {
                    if (arr[j] == T[k]) {
                        if (LL1[pos][k] > 0) {
                            printf("\n\nConflict occur between %s and %s rules!", G[LL1[pos][k] - 1], G[i]);
                            printf("\nGiven grammar is not LL(1) grammar!\n");
                            flag = 1;
                            return flag;
                        } else
                            LL1[pos][k] = i + 1;
                        break;
                    }
                }
            }
        }
    }
    return flag;
}

void PARSING_TABLE_SHOW(int flag) {
    int i, j;
    if (flag == 0) {
        printf("\n\nPredictive Parsing Table:\n\n\t");
        for (j = 0; j < t; j++) {
            printf("\t%c\t", T[j]);
        }
        printf("\n----------------------------------------------------------------------------------------");
        printf("\n\n");
        for (i = 0; i < nt; i++) {
            printf("%c\t|\t", NT[i]);
            for (j = 0; j < t; j++) {
                if (LL1[i][j] != 0)
                    printf("%s\t\t", G[LL1[i][j] - 1]);
                else
                    printf("%c\t\t", '_');
            }
            printf("\n\n");
        }
    }
}

void LL1_PARSER(char *STR) {
    int i = 0, j, pos, pos1, n, k;

    STR[strlen(STR)] = '$';
    STACK[top++] = '$';
    STACK[top] = G[0][0];

    printf("\nParsing sequence and actions\n\n");
    printf("STACK\t\t\tINPUT\t\t\tACTION");
    printf("\n------------------------------------------------------------------------------------\n");

    i = 0;
    while (STACK[top] != '$') {
        for (j = 0; STACK[j] != '\0'; j++)
            printf("%c  ", STACK[j]);
        printf("\t\t");

        for (j = i; STR[j] != '\0'; j++)
            printf("%c  ", STR[j]);

        if (STR[i] == STACK[top]) {
            printf("\t\tReduced: %c", STACK[top]);
            STACK[top] = '\0';
            top = top - 1;
            i = i + 1;
        } else {
            for (j = 0; j < nt; j++) {
                if (STACK[top] == NT[j]) {
                    pos = j;
                    break;
                }
            }
            for (j = 0; j < t; j++) {
                if (STR[i] == T[j]) {
                    pos1 = j;
                    break;
                }
            }
            n = LL1[pos][pos1];
            if (G[n - 1][3] == '!') {
                STACK[top] = '\0';
                top--;
            } else {
                for (j = 3; G[n - 1][j] != '\0'; j++)
                    k = j;
                STACK[top] = '\0';
                for (j = k; j > 2; j--)
                    STACK[top++] = G[n - 1][j];
                top--;
            }
            printf("\t\tShift: %s", G[n - 1]);
        }
        printf("\n");
    }
    for (j = 0; STACK[j] != '\0'; j++)
        printf("%c  ", STACK[j]);
    printf("\t\t");

    for (j = i; STR[j] != '\0'; j++)
        printf("%c  ", STR[j]);

    printf("\n");
    if (STACK[top] == '$' && STR[i] == '$')
        printf("\nParsing successfully\n");
}