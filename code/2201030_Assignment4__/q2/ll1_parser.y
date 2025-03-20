%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex(void);
extern char *yytext;
extern YY_BUFFER_STATE yy_create_buffer(FILE *file, int size);
extern void yy_switch_to_buffer(YY_BUFFER_STATE new_buffer);
extern void yy_delete_buffer(YY_BUFFER_STATE b);
extern YY_BUFFER_STATE yy_scan_string(const char *yy_str);
extern YY_BUFFER_STATE yy_current_buffer;

typedef enum {
    NONTERM_START, // Special start symbol
    NUM_NONTERMINALS
} NonTerminal;

typedef struct Production {
    int lhs;
    char* rhs[10];
    int rhsLength;
} Production;

Production *grammar = NULL;
int numProductions = 0;
int maxProductions = 0;

#define MAX_TERMINALS 10
#define MAX_DERIVATION_LENGTH 100

char *parsingTable[MAX_DERIVATION_LENGTH][MAX_TERMINALS];

char **terminals = NULL;
int numTerminals = 0;
int maxTerminals = 0;

char ***firstSets;
char ***followSets;
char** nonTerminals = NULL;
int numNonTerminals = 0;

typedef struct StackNode {
    char *symbol;
    struct StackNode *next;
} StackNode;

StackNode *stack = NULL;

void push(const char *symbol) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed in push()\n");
        exit(1);
    }
    newNode->symbol = strdup(symbol);
    if (newNode->symbol == NULL) {
        fprintf(stderr, "Memory allocation error (strdup)!\n");
        exit(1);
    }
    newNode->next = stack;
    stack = newNode;
}

char *pop() {
    if (stack == NULL) {
        return NULL;
    }
    StackNode *temp = stack;
    stack = stack->next;
    char *symbol = temp->symbol;
    free(temp);
    return symbol;
}

bool isStackEmpty() {
    return stack == NULL;
}

void freeStack() {
    while (!isStackEmpty()) {
        char* temp = pop();
        if (temp != NULL) free(temp);
    }
}

void computeFirstSets();
void computeFollowSets();
void buildParsingTable();
void printParsingTable();
int getTerminalIndex(const char *terminal);
int getNonTerminalIndex(const char *nonTerminal);
int getProductionIndex(int lhs, const char** rhs, int rhsLength);
bool isNonTerminal(const char* symbol);
void parseInput();
void yyerror(const char *s);
int getTokenIndex(const char* token);
char* productionToString(int productionIndex);
void printFirstSets();
void printFollowSets();
char* nonTerminalToString(int nt);
void printDerivation(int derivation[], int derivationLength);
void readGrammar();
void addTerminal(const char* terminal);
void addNonTerminal(const char* nonTerminal);
void addProduction(int lhs, char** rhs, int rhsLength);
void freeMemory();

#ifdef __cplusplus
extern "C" int yylex(void);
#endif

int is_parsing_done = 0;

int yylex_reset() {
    is_parsing_done = 0;
    return 0;
}
%}

%union {
    char *string;
    int   token;
}

%token <string> IDENTIFIER
%token PLUS TIMES LPAREN RPAREN ENDMARKER
%token END_OF_INPUT

%start program

%%

program :  {
            readGrammar();
            computeFirstSets();
            computeFollowSets();
            buildParsingTable();
            printFirstSets();
            printFollowSets();
            printParsingTable();

            printf("Terminals: ");
            for (int i = 0; i < numTerminals; i++) {
                printf("%s ", terminals[i]);
            }
            printf("\n");

            char inputBuffer[1000];
            printf("Enter input string (or 'quit' to exit):\n");
            while (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) {
                inputBuffer[strcspn(inputBuffer, "\n")] = 0; // Remove trailing newline

                if (strcmp(inputBuffer, "quit") == 0) {
                    break;
                }

                if (strlen(inputBuffer) > 0) {
                    YY_BUFFER_STATE buffer = yy_scan_string(inputBuffer);
                    parseInput();
                    yy_delete_buffer(buffer);
                    yylex_reset();
                } else {
                    printf("Please enter a non-empty string.\n");
                }
                printf("Enter input string (or 'quit' to exit):\n");
            }
            freeMemory();
           }
           ;

%%

void addTerminal(const char* terminal) {
    // Check if terminal already exists to avoid duplicates
    for (int i = 0; i < numTerminals; i++) {
        if (strcmp(terminals[i], terminal) == 0) {
            return; // Terminal already exists, no need to add
        }
    }

    if (numTerminals == maxTerminals) {
        maxTerminals = (maxTerminals == 0) ? 1 : maxTerminals * 2; // Initial or Double
        terminals = (char**)realloc(terminals, maxTerminals * sizeof(char*));
        if (!terminals) {
            fprintf(stderr, "Memory allocation error for Terminals.\n");
            exit(1);
        }
    }

    terminals[numTerminals++] = strdup(terminal);
    if (!terminals[numTerminals-1]) {
        fprintf(stderr, "Memory allocation error for strdup.\n");
        exit(1);
    }
}

void addNonTerminal(const char* nonTerminal) {
    if (numNonTerminals == 0 || getNonTerminalIndex(nonTerminal) == -1)
    {
        numNonTerminals++;
        nonTerminals = (char**)realloc(nonTerminals, numNonTerminals * sizeof(char*));
         if (!nonTerminals) {
             fprintf(stderr, "Memory allocation error for Non-Terminals.\n");
             exit(1);
         }
        nonTerminals[numNonTerminals-1] = strdup(nonTerminal);
        if (!nonTerminals[numNonTerminals-1]) {
           fprintf(stderr, "Memory allocation error for strdup.\n");
           exit(1);
        }
    }
}

void addProduction(int lhs, char** rhs, int rhsLength) {
    if (numProductions == maxProductions) {
        maxProductions = (maxProductions == 0) ? 1 : maxProductions * 2;
        grammar = (Production*)realloc(grammar, maxProductions * sizeof(Production));
         if (!grammar) {
           fprintf(stderr, "Memory allocation error for Grammar.\n");
           exit(1);
         }
    }

    grammar[numProductions].lhs = lhs;
    grammar[numProductions].rhsLength = rhsLength;
    for (int i = 0; i < rhsLength; i++) {
        grammar[numProductions].rhs[i] = strdup(rhs[i]);
        if (!grammar[numProductions].rhs[i]) {
            fprintf(stderr, "Memory allocation error for strdup.\n");
            exit(1);
        }
    }
    grammar[numProductions].rhs[rhsLength] = NULL;

    numProductions++;
}

void readGrammar() {
    char inputBuffer[1000];
    int num_productions;

    printf("Enter the number of productions: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &num_productions);

    addTerminal("ENDMARKER");
    addTerminal("EPSILON");

    printf("Enter the productions (e.g., E -> T E'  |  EPSILON):\n");

    for (int i = 0; i < num_productions; i++) {
        printf("Production %d: ", i + 1);
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = 0;

        char lhsStr[100];
        char rhsStr[1000];
        if (sscanf(inputBuffer, "%s -> %[^\n]", lhsStr, rhsStr) != 2) {
            fprintf(stderr, "Invalid production format.\n");
            exit(1);
        }

        addNonTerminal(lhsStr);
        int lhs = getNonTerminalIndex(lhsStr);

        char *rhsTokens[10]; // Maximum 10 tokens on the RHS
        int rhsCount = 0;
        char *token = strtok(rhsStr, " ");
        while (token != NULL) {
            if (strcmp(token, "|") != 0) {  // Ignore '|' ******
                if (!isNonTerminal(token)) {
                    addTerminal(token);
                } else {
                    addNonTerminal(token);
                }
                rhsTokens[rhsCount++] = token;
            }
            token = strtok(NULL, " ");
        }

        addProduction(lhs, rhsTokens, rhsCount);
    }
    // Add Sentinel:
    if (numProductions == maxProductions) {
        maxProductions += 1;
        grammar = (Production*)realloc(grammar, maxProductions * sizeof(Production));
         if (!grammar) {
           fprintf(stderr, "Memory allocation error for Grammar.\n");
           exit(1);
         }
    }
    grammar[numProductions].lhs = -1; // Sentinel value
    grammar[numProductions].rhsLength = 0;
    numProductions++;
}

void computeFirstSets() {
    firstSets = (char***)malloc(numNonTerminals * sizeof(char**));
    if (!firstSets) {
        fprintf(stderr, "Memory allocation error for firstSets.\n");
        exit(1);
    }
    for (int i = 0; i < numNonTerminals; i++) {
        firstSets[i] = (char**)malloc(numTerminals * sizeof(char*));
        if (!firstSets[i]) {
            fprintf(stderr, "Memory allocation error for firstSets.\n");
            exit(1);
        }
        for (int j = 0; j < numTerminals; j++) {
            firstSets[i][j] = NULL;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < numProductions && grammar[i].rhsLength != 0; i++) {
            Production *p = &grammar[i];
            if (!isNonTerminal(p->rhs[0])) {
                if (firstSets[p->lhs][getTerminalIndex(p->rhs[0])] == NULL) {
                    firstSets[p->lhs][getTerminalIndex(p->rhs[0])] = strdup(p->rhs[0]);
                    if (firstSets[p->lhs][getTerminalIndex(p->rhs[0])] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                        exit(1);
                    }
                    changed = true;
                }
            } else {
                if (strcmp(p->rhs[0], "EPSILON") == 0) {
                    if (firstSets[p->lhs][getTerminalIndex("EPSILON")] == NULL) {
                        firstSets[p->lhs][getTerminalIndex("EPSILON")] = strdup("EPSILON");
                        if (firstSets[p->lhs][getTerminalIndex("EPSILON")] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                            exit(1);
                        }
                        changed = true;
                    }
                } else {
                    int k = 0;
                    while (p->rhs[k] != NULL) {
                        if (!isNonTerminal(p->rhs[k])) { // Terminal
                            if (firstSets[p->lhs][getTerminalIndex(p->rhs[k])] == NULL) {
                                firstSets[p->lhs][getTerminalIndex(p->rhs[k])] = strdup(p->rhs[k]); // Add terminal to FIRST set and break
                                if (firstSets[p->lhs][getTerminalIndex(p->rhs[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                            break;
                        }
                        int Y = getNonTerminalIndex(p->rhs[k]); // Non-terminal
                        for (int j = 0; j < numTerminals; ++j) {
                            if (firstSets[Y][j] != NULL && strcmp(firstSets[Y][j], "EPSILON") != 0) {
                                if (firstSets[p->lhs][j] == NULL) {
                                    firstSets[p->lhs][j] = strdup(firstSets[Y][j]); // Add FIRST(Y) to FIRST(X) if not EPSILON
                                    if (firstSets[p->lhs][j] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                                        exit(1);
                                    }
                                    changed = true;
                                }
                            }
                        }
                        if (firstSets[Y][getTerminalIndex("EPSILON")] == NULL) break; // No EPSILON in FIRST(Y)
                        k++;
                        if (p->rhs[k] == NULL && firstSets[Y][getTerminalIndex("EPSILON")] != NULL) { // Add EPSILON to FIRST(X) if EPSILON in all FIRST(Y)
                            if (firstSets[p->lhs][getTerminalIndex("EPSILON")] == NULL) {
                                firstSets[p->lhs][getTerminalIndex("EPSILON")] = strdup("EPSILON");
                                if (firstSets[p->lhs][getTerminalIndex("EPSILON")] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void computeFollowSets() {
    followSets = (char***)malloc(numNonTerminals * sizeof(char**));
    if (!followSets) {
        fprintf(stderr, "Memory allocation error for followSets.\n");
        exit(1);
    }
    for (int i = 0; i < numNonTerminals; i++) {
        followSets[i] = (char**)malloc(numTerminals * sizeof(char*));
        if (!followSets[i]) {
            fprintf(stderr, "Memory allocation error for followSets.\n");
            exit(1);
        }
        for (int j = 0; j < numTerminals; j++) {
            followSets[i][j] = NULL;
        }
    }

    followSets[0][getTerminalIndex("ENDMARKER")] = strdup("ENDMARKER"); // Add ENDMARKER to FOLLOW(Start)
    if (followSets[0][getTerminalIndex("ENDMARKER")] == NULL) {
        fprintf(stderr, "Memory allocation error (strdup).\n");
        exit(1);
    }
    bool changed = true;
    while (changed) {
        changed = false;

        for (int i = 0; i < numProductions && grammar[i].rhsLength != 0; ++i) {
            Production* p = &grammar[i];

            for (int j = 0; j < p->rhsLength; ++j) {
                if (isNonTerminal(p->rhs[j])) { // Non-terminal
                    int B = getNonTerminalIndex(p->rhs[j]);

                    int k = j + 1;
                    while (p->rhs[k] != NULL) {
                        if (!isNonTerminal(p->rhs[k])) { // Terminal
                            if (followSets[B][getTerminalIndex(p->rhs[k])] == NULL) {
                                followSets[B][getTerminalIndex(p->rhs[k])] = strdup(p->rhs[k]); // Add terminal to FOLLOW set and break
                                if (followSets[B][getTerminalIndex(p->rhs[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup).\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                            break;
                        }

                        int beta = getNonTerminalIndex(p->rhs[k]); // Non-terminal

                        for (int m = 0; m < numTerminals; ++m) {
                            if (firstSets[beta][m] != NULL && strcmp(firstSets[beta][m], "EPSILON") != 0) {
                                if (followSets[B][m] == NULL) {
                                    followSets[B][m] = strdup(firstSets[beta][m]); // Add FIRST(beta) to FOLLOW(B) if not EPSILON
                                    if (followSets[B][m] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup).\n");
                                        exit(1);
                                    }
                                    changed = true;
                                }
                            }
                        }
                        if (firstSets[beta][getTerminalIndex("EPSILON")] == NULL) break; // No EPSILON in FIRST(beta)
                        k++;
                    }

                    if (p->rhs[k] == NULL) {
                        int A = p->lhs;
                        for (int m = 0; m < numTerminals; ++m) {
                            if (followSets[A][m] != NULL) {
                                if (followSets[B][m] == NULL) {
                                    followSets[B][m] = strdup(followSets[A][m]); // Add FOLLOW(A) to FOLLOW(B) if EPSILON in all FIRST(beta)
                                    if (followSets[B][m] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup).\n");
                                        exit(1);
                                    }
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void buildParsingTable() {
    for (int i = 0; i < numNonTerminals; ++i) {
        for (int j = 0; j < numTerminals; ++j) {
            parsingTable[i][j] = NULL;
        }
    }

    for (int i = 0; i < numProductions && grammar[i].rhsLength != 0; i++) {
        Production *p = &grammar[i];
        int A = p->lhs;

        if (strcmp(p->rhs[0], "EPSILON") == 0) {
            for (int j = 0; j < numTerminals; ++j) {
                if (followSets[A][j] != NULL) {
                    int terminalIndex = getTerminalIndex(followSets[A][j]); // Add EPSILON production to FOLLOW(A)
                    if (terminalIndex == -1) continue;
                    char prod_str[50] = "";
                    sprintf(prod_str, "%d", i);
                    parsingTable[A][terminalIndex] = strdup(prod_str);
                    if (parsingTable[A][terminalIndex] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup).\n");
                        exit(1);
                    }
                }
            }
        } else {
            int k = 0;
            while (p->rhs[k] != NULL) {
                if (!isNonTerminal(p->rhs[k])) {
                    int terminalIndex = getTerminalIndex(p->rhs[k]);
                    if (terminalIndex == -1) break;
                    char prod_str[50] = "";
                    sprintf(prod_str, "%d", i);
                    parsingTable[A][terminalIndex] = strdup(prod_str); // Add production to FIRST(A) if terminal
                    if (parsingTable[A][terminalIndex] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup).\n");
                        exit(1);
                    }
                    break;
                }
                int X = getNonTerminalIndex(p->rhs[k]);

                for (int j = 0; j < numTerminals; j++) {
                    if (firstSets[X][j] != NULL && strcmp(firstSets[X][j], "EPSILON") != 0) {
                        int terminalIndex = getTerminalIndex(firstSets[X][j]);
                        if (terminalIndex == -1) continue;
                        char prod_str[50] = "";
                        sprintf(prod_str, "%d", i);
                        parsingTable[A][terminalIndex] = strdup(prod_str); // Add production to FIRST(A) if not EPSILON
                        if (parsingTable[A][terminalIndex] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup).\n");
                            exit(1);
                        }
                    }
                }

                if (firstSets[X][getTerminalIndex("EPSILON")] == NULL) break; // No EPSILON in FIRST(X)
                k++;
                if (p->rhs[k] == NULL && firstSets[X][getTerminalIndex("EPSILON")] != NULL) {
                    for (int j = 0; j < numTerminals; ++j) {
                        if (followSets[A][j] != NULL) {
                            int terminalIndex = getTerminalIndex(followSets[A][j]);
                            if (terminalIndex == -1) continue;
                            char prod_str[50] = "";
                            sprintf(prod_str, "%d", i);
                            parsingTable[A][terminalIndex] = strdup(prod_str); // Add production to FOLLOW(A) if EPSILON in all FIRST(X)
                            if (parsingTable[A][terminalIndex] == NULL) {
                                fprintf(stderr, "Memory allocation error (strdup).\n");
                                exit(1);
                            }
                        }
                    }
                }
            }
        }
    }
}

char* productionToString(int productionIndex) {
    if (productionIndex < 0 || productionIndex >= numProductions || grammar[productionIndex].rhsLength == 0) {
        return "Invalid Production";
    }

    Production *p = &grammar[productionIndex];
    static char productionStr[100];
    char* nonTerminalStr = nonTerminalToString(p->lhs);

    snprintf(productionStr, sizeof(productionStr), "%s -> ", nonTerminalStr);

    for (int i = 0; i < p->rhsLength; i++) {
        strncat(productionStr, p->rhs[i], sizeof(productionStr) - strlen(productionStr) - 1);
        if (i < p->rhsLength - 1) {
            strncat(productionStr, " ", sizeof(productionStr) - strlen(productionStr) - 1); // Add space between symbols
        }
    }

    return productionStr;
}

void printParsingTable() {
    printf("\nParsing Table:\n");
    printf("------------------------------------------------------------\n");
    printf("%-15s", ""); // Empty space for row labels

    // Print column headers (only terminals)
    for (int j = 0; j < numTerminals; j++) {
        if (!isNonTerminal(terminals[j]) && strcmp(terminals[j], "EPSILON") != 0) {
            printf("%-20s", terminals[j]);
        }
    }
    printf("\n");

    // Print table rows
    for (int i = 0; i < numNonTerminals; i++) {
        printf("%-15s", nonTerminalToString(i));

        // Print table entries (only for terminals, excluding EPSILON)
        for (int j = 0; j < numTerminals; j++) {
            if (!isNonTerminal(terminals[j]) && strcmp(terminals[j], "EPSILON") != 0) {
                if (parsingTable[i][j] != NULL) {
                    int productionIndex = atoi(parsingTable[i][j]);
                    printf("%-20s", productionToString(productionIndex));
                } else {
                    printf("%-20s", "-");
                }
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------------------\n");
}

int getTerminalIndex(const char *terminal) {
    for (int i = 0; i < numTerminals; i++) {
        if (strcmp(terminals[i], terminal) == 0) {
            return i;
        }
    }
    return -1;
}

int getNonTerminalIndex(const char *nonTerminal) {
    for (int i = 0; i < numNonTerminals; ++i) {
        if (strcmp(nonTerminals[i], nonTerminal) == 0) return i;
    }
    return -1;
}

bool isNonTerminal(const char* symbol) {
    for (int i = 0; i < numNonTerminals; ++i) {
        if (strcmp(nonTerminals[i], symbol) == 0) return true;
    }
    return false;
}

int getProductionIndex(int lhs, const char** rhs, int rhsLength) {
    for (int i = 0; i < numProductions; i++) {
        if (grammar[i].lhs == lhs && grammar[i].rhsLength == rhsLength) {
            bool match = true;
            for (int j = 0; j < rhsLength; j++) {
                if (strcmp(grammar[i].rhs[j], rhs[j]) != 0) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
    }
    return -1;
}

int getTokenIndex(const char* token) {
    for (int i = 0; i < numTerminals; ++i) {
        if (strcmp(terminals[i], token) == 0) return i;
    }
    return -1;
}

void parseInput() {
    push("ENDMARKER");
    push(nonTerminals[0]);

    int lookaheadToken = yylex();

    int derivation[MAX_DERIVATION_LENGTH];
    int derivationLength = 0;

    while (!isStackEmpty()) {
        char *top = pop();

        // Debug: Print current state
        printf("Stack top: %s, Lookahead: %s\n", top, yytext);

        if (isNonTerminal(top)) {
            int nonTermIndex = getNonTerminalIndex(top);
            if (nonTermIndex == -1) {
                fprintf(stderr, "Invalid NonTerminal index!\n");
                free(top);
                freeStack();
                return;
            }

            int lookahead = getTokenIndex(yytext);
            if (lookahead == -1) {
                fprintf(stderr, "Invalid lookahead index! Token '%s' not in terminals.\n", yytext);
                free(top);
                freeStack();
                return;
            }

            char *productionIndexStr = parsingTable[nonTermIndex][lookahead];
            if (productionIndexStr != NULL) {
                int productionIndex = atoi(productionIndexStr);
                Production *p = &grammar[productionIndex];

                if (derivationLength < MAX_DERIVATION_LENGTH) {
                    derivation[derivationLength++] = productionIndex;
                } else {
                    fprintf(stderr, "Derivation too long!\n");
                    free(top);
                    freeStack();
                    return;
                }

                for (int i = p->rhsLength - 1; i >= 0; i--) {
                    if (strcmp(p->rhs[i], "EPSILON") != 0) {
                        push(p->rhs[i]);
                    }
                }
                free(top);
            } else {
                printf("Syntax Error: No production for %s with lookahead %s\n", top, yytext);
                free(top);
                freeStack();
                return;
            }
        } else {
            // Special handling for ENDMARKER
            if (strcmp(top, "ENDMARKER") == 0) {
                if (strcmp(yytext, "$") == 0 || yytext[0] == '\0') { // Accept $ or end of input
                    printf("Parsing successful!\n");
                    printDerivation(derivation, derivationLength);
                    free(top);
                    freeStack();
                    return;
                } else {
                    printf("Syntax Error: Expected ENDMARKER, but got %s\n", yytext);
                    free(top);
                    freeStack();
                    return;
                }
            } else if (strcmp(top, yytext) == 0) {
                free(top);
                lookaheadToken = yylex();
            } else {
                printf("Syntax Error: Expected %s, but got %s\n", top, yytext);
                free(top);
                freeStack();
                return;
            }
        }
    }
    printf("Parsing failed (unexpected end of input or stack not empty).\n");
    freeStack();
}

void printDerivation(int derivation[], int derivationLength) {
    printf("Derivation:\n");
    if (derivationLength > 0) {
        printf("%s", nonTerminals[0]);
        for (int i = 0; i < derivationLength; ++i) {
            printf(" => %s", productionToString(derivation[i]));
        }
        printf("\n");
    }
}

void printFirstSets() {
    printf("\nFIRST Sets:\n");
    printf("---------------------\n");
    for (int i = 0; i < numNonTerminals; i++) {
        printf("FIRST(%s) = { ", nonTerminalToString(i));
        for (int j = 0; j < numTerminals; j++) {
            if (firstSets[i][j] != NULL) {
                printf("%s", firstSets[i][j]);
                int k = j + 1;
                while (k < numTerminals && firstSets[i][k] == NULL) {
                    k++;
                }
                if (k < numTerminals && firstSets[i][k] != NULL) {
                    printf(", ");
                }
            }
        }
        printf(" }\n");
    }
    printf("---------------------\n");
}

void printFollowSets() {
    printf("\nFOLLOW Sets:\n");
    printf("---------------------\n");
    for (int i = 0; i < numNonTerminals; i++) {
        printf("FOLLOW(%s) = { ", nonTerminalToString(i));
        for (int j = 0; j < numTerminals; j++) {
            if (followSets[i][j] != NULL) {
                printf("%s", followSets[i][j]);
                int k = j + 1;
                while (k < numTerminals && followSets[i][k] == NULL) {
                    k++;
                }
                if (k < numTerminals && followSets[i][k] != NULL) {
                    printf(", ");
                }
            }
        }
        printf(" }\n");
    }
    printf("---------------------\n");
}

char* nonTerminalToString(int nt) {
    return nonTerminals[nt];
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s near token %s\n", s, yytext);
    freeMemory();
    exit(1);
}

void freeMemory() {
    for (int i = 0; i < numTerminals; ++i) {
        if (terminals[i] != NULL) free(terminals[i]);
    }
    if (terminals != NULL) free(terminals);

    for (int i = 0; i < numNonTerminals; ++i) {
        if (nonTerminals[i] != NULL) free(nonTerminals[i]);
    }
    if (nonTerminals != NULL) free(nonTerminals);

    for (int i = 0; i < numProductions; ++i) {
        for (int j = 0; j < grammar[i].rhsLength; ++j) {
            if (grammar[i].rhs[j] != NULL) free(grammar[i].rhs[j]);
        }
    }
    if (grammar != NULL) free(grammar);

    if (firstSets) {
        for (int i = 0; i < numNonTerminals; i++) {
            for (int j = 0; j < numTerminals; j++) {
                if (firstSets[i][j] != NULL) {
                    free(firstSets[i][j]);
                }
            }
            free(firstSets[i]);
        }
        free(firstSets);
    }

    if (followSets) {
        for (int i = 0; i < numNonTerminals; i++) {
            for (int j = 0; j < numTerminals; j++) {
                if (followSets[i][j] != NULL) {
                    free(followSets[i][j]);
                }
            }
            free(followSets[i]);
        }
        free(followSets);
    }

    for (int i = 0; i < numNonTerminals; ++i) {
        for (int j = 0; j < numTerminals; ++j) {
            if (parsingTable[i][j] != NULL) free(parsingTable[i][j]);
        }
    }

    freeStack();
}

int main() {
    yyparse();
    return 0;
}
