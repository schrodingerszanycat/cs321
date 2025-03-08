%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    NONTERM_E,
    NONTERM_EPRIME,
    NONTERM_T,
    NONTERM_TPRIME,
    NONTERM_F,
    NUM_NONTERMINALS
} NonTerminal;

typedef struct Production {
    NonTerminal lhs;
    char* rhs[10];
    int rhsLength;
} Production;

Production grammar[] = {
    {NONTERM_E, {"T", "E'", NULL}, 2},
    {NONTERM_EPRIME, {"PLUS", "T", "E'", NULL}, 3},
    {NONTERM_EPRIME, {"EPSILON", NULL}, 1},
    {NONTERM_T, {"F", "T'", NULL}, 2},
    {NONTERM_TPRIME, {"TIMES", "F", "T'", NULL}, 3},
    {NONTERM_TPRIME, {"EPSILON", NULL}, 1},
    {NONTERM_F, {"LPAREN", "E", "RPAREN", NULL}, 3},
    {NONTERM_F, {"IDENTIFIER", NULL}, 1},
    {NONTERM_F, {NULL}, 0} // Sentinel
};

// --- Data Structures for First/Follow and Parse Table ---

#define MAX_TERMINALS 10

char *parsingTable[NUM_NONTERMINALS][MAX_TERMINALS];
char *terminals[] = {"IDENTIFIER", "PLUS", "TIMES", "LPAREN", "RPAREN", "ENDMARKER", "EPSILON", NULL};
typedef enum{
    IDENTIFIER_INDEX,
    PLUS_INDEX,
    TIMES_INDEX,
    LPAREN_INDEX,
    RPAREN_INDEX,
    ENDMARKER_INDEX,
    EPSILON_INDEX
} TerminalIndex;

char *firstSets[NUM_NONTERMINALS][MAX_TERMINALS];
char *followSets[NUM_NONTERMINALS][MAX_TERMINALS];

// --- Stack for LL(1) Parsing ---

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
        if(temp!=NULL) free(temp);
    }
}

// --- Function Declarations ---
void computeFirstSets();
void computeFollowSets();
void buildParsingTable();
void printParsingTable();
int getTerminalIndex(const char *terminal);
NonTerminal getNonTerminal(const char *nonTerminal);
int getProductionIndex(NonTerminal lhs, const char** rhs, int rhsLength);
bool isNonTerminal(const char* symbol);
void parseInput();
void yyerror(const char *s);
extern int yylex();
extern char *yytext;
TerminalIndex getTokenIndex(int token);
char* productionToString(int productionIndex); // New function

// --- Reset Mechanism ---
int is_parsing_done = 0;

int yylex_reset() {
    is_parsing_done = 0;
     while (getchar() != '\n');
    return 0;
}
%}

%union {
    char *string;
    int   token;
}

%token <string> IDENTIFIER
%token PLUS TIMES LPAREN RPAREN ENDMARKER
%token  END_OF_INPUT

%start program

%%

program :  {
            computeFirstSets();
            computeFollowSets();
            buildParsingTable();
            printParsingTable();
            while(1){
                parseInput();
                if (is_parsing_done) {
                    yylex_reset();
                }
            }

           }
           ;
%%

// --- Function Definitions ---

void computeFirstSets() {
     // (Same as before, no changes needed)
    // Initialize to empty
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            firstSets[i][j] = NULL;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
       for (int i = 0; grammar[i].rhsLength != 0 ; i++) { // Use rhsLength
            Production *p = &grammar[i];
            //Rule 1: If X is a terminal, FIRST(X) = {X}
            if(!isNonTerminal(p->rhs[0])){
                if(firstSets[p->lhs][getTerminalIndex(p->rhs[0])] == NULL){
                     firstSets[p->lhs][getTerminalIndex(p->rhs[0])] = strdup(p->rhs[0]);
                      if (firstSets[p->lhs][getTerminalIndex(p->rhs[0])] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                        exit(1);
                     }
                     changed = true;
                }

            } else {
            //Rule 2: If X->EPSILON, add EPSILON to FIRST(X)
                if(strcmp(p->rhs[0], "EPSILON")==0){
                     if(firstSets[p->lhs][getTerminalIndex("EPSILON")] == NULL){
                        firstSets[p->lhs][getTerminalIndex("EPSILON")] = strdup("EPSILON");
                        if (firstSets[p->lhs][getTerminalIndex("EPSILON")] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                            exit(1);
                        }
                        changed = true;
                     }
                }else{
            //Rule 3: If X is a non-terminal, and X-> Y1 Y2...Yk
                    int k=0;
                    while(p->rhs[k]!=NULL){
                        if(!isNonTerminal(p->rhs[k])){
                            if(firstSets[p->lhs][getTerminalIndex(p->rhs[k])] == NULL){
                                firstSets[p->lhs][getTerminalIndex(p->rhs[k])] = strdup(p->rhs[k]);
                                if (firstSets[p->lhs][getTerminalIndex(p->rhs[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                                    exit(1);
                                  }
                                changed = true;
                            }
                            break; //No more processing.
                        }
                        NonTerminal Y = getNonTerminal(p->rhs[k]);
                        //Add all of FIRST(Yi) except EPSILON
                        for(int j=0; j<MAX_TERMINALS; ++j){
                            if(firstSets[Y][j] != NULL && strcmp(firstSets[Y][j], "EPSILON") != 0){
                                if(firstSets[p->lhs][j] == NULL){
                                     firstSets[p->lhs][j] = strdup(firstSets[Y][j]);
                                     if (firstSets[p->lhs][j] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup) in computeFirstSets!\n");
                                        exit(1);
                                      }
                                     changed = true;
                                }

                            }
                        }
                        //If FIRST(Yi) does not contain epsilon, stop.
                        if(firstSets[Y][getTerminalIndex("EPSILON")] == NULL) break;

                        k++;
                        //if all Y1...Yk have EPSILON in FIRST, add EPSILON to FIRST(X)
                        if(p->rhs[k] == NULL && firstSets[Y][getTerminalIndex("EPSILON")] != NULL){
                             if(firstSets[p->lhs][getTerminalIndex("EPSILON")] == NULL){
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
     // (Same as before, no changes needed)
    // Initialize follow sets (except for the start symbol)
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
             followSets[i][j] = NULL;

        }
    }
     // Rule 1: FOLLOW(S) = {$}
    followSets[NONTERM_E][getTerminalIndex("ENDMARKER")] = strdup("ENDMARKER");
     if ( followSets[NONTERM_E][getTerminalIndex("ENDMARKER")] == NULL) {
        fprintf(stderr, "Memory allocation error (strdup) in computeFollowSets!\n");
        exit(1);
     }

    bool changed = true;
    while(changed){
        changed = false;

        for(int i=0; grammar[i].rhsLength != 0; ++i){ // Use rhsLength
            Production *p = &grammar[i];
            //Iterate through symbols on RHS.
            for(int j=0; j<p->rhsLength; ++j){
                if(isNonTerminal(p->rhs[j])){
                    NonTerminal B = getNonTerminal(p->rhs[j]);

                    //Rule 2: If A->alpha B beta, FOLLOW(B) = {FIRST(beta) - EPSILON}
                    int k = j+1;
                    while(p->rhs[k] != NULL){ //While there is a beta
                        if(!isNonTerminal(p->rhs[k])){ //If beta is terminal
                            if(followSets[B][getTerminalIndex(p->rhs[k])] == NULL){
                                 followSets[B][getTerminalIndex(p->rhs[k])] = strdup(p->rhs[k]);
                                 if ( followSets[B][getTerminalIndex(p->rhs[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in computeFollowSets!\n");
                                    exit(1);
                                 }
                                 changed = true;
                            }
                            break; //No more processing of beta
                        }

                        NonTerminal beta = getNonTerminal(p->rhs[k]);

                        for(int m=0; m<MAX_TERMINALS; ++m){
                             if(firstSets[beta][m] != NULL && strcmp(firstSets[beta][m], "EPSILON") !=0){ //Add FIRST(beta) - EPSILON
                                if(followSets[B][m] == NULL){
                                    followSets[B][m] = strdup(firstSets[beta][m]);
                                     if ( followSets[B][m] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup) in computeFollowSets!\n");
                                        exit(1);
                                     }
                                     changed = true;
                                }
                             }
                        }
                        //If EPSILON not in FIRST(beta), stop.
                        if(firstSets[beta][getTerminalIndex("EPSILON")] == NULL) break;
                        k++;
                    }
                    //Rule 3: If A->alpha B or A->alpha B beta where EPSILON is in FIRST(beta), FOLLOW(B) = FOLLOW(B) U FOLLOW(A)
                    if(p->rhs[k] == NULL){ //If beta is empty or all beta have epsilon
                        NonTerminal A = p->lhs;
                        for(int m=0; m<MAX_TERMINALS; ++m){
                            if(followSets[A][m] != NULL){ //Everything in FOLLOW(A) is in FOLLOW(B)
                                if(followSets[B][m] == NULL){
                                    followSets[B][m] = strdup(followSets[A][m]);
                                    if ( followSets[B][m] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup) in computeFollowSets!\n");
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
    // (Same as before, no changes needed)
    // Initialize to all NULLs (errors)
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            parsingTable[i][j] = NULL;
        }
    }

    // Iterate through productions
    for (int i = 0; grammar[i].rhsLength != 0; i++) {  // Use rhsLength
        Production *p = &grammar[i];
        NonTerminal A = p->lhs;

        // Rule 1: For each terminal a in FIRST(alpha), add A -> alpha to M[A, a]
        //Process RHS
        if(strcmp(p->rhs[0], "EPSILON") == 0){
              // Rule 2: If ε is in FIRST(α), for each terminal b in FOLLOW(A), add A -> α to M[A, b]
            for(int j = 0; j<MAX_TERMINALS; ++j){ //Find FOLLOW(A)
                if(followSets[A][j]!=NULL){
                    int terminalIndex = getTerminalIndex(followSets[A][j]);
                    if (terminalIndex == -1) continue; //Skip if invalid index.
                    char prod_str[50] = "";
                    sprintf(prod_str, "%d", i); // Convert production index to string
                    parsingTable[A][terminalIndex] = strdup(prod_str);
                     if ( parsingTable[A][terminalIndex] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup) in buildParsingTable!\n");
                        exit(1);
                     }
                }
            }
        } else { //Not epsilon
                int k=0;
                while(p->rhs[k] != NULL){
                    if(!isNonTerminal(p->rhs[k])){ //If terminal
                         int terminalIndex = getTerminalIndex(p->rhs[k]);
                         if(terminalIndex == -1) break; //invalid terminal
                        char prod_str[50] = "";
                        sprintf(prod_str, "%d", i); // Convert production index to string
                         parsingTable[A][terminalIndex] = strdup(prod_str); //Add the production
                          if ( parsingTable[A][terminalIndex] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup) in buildParsingTable!\n");
                            exit(1);
                         }
                         break;
                    }
                    //If NonTerminal
                    NonTerminal X = getNonTerminal(p->rhs[k]);

                    for(int j=0; j<MAX_TERMINALS; j++){//For each terminal in FIRST(X)
                        if(firstSets[X][j] != NULL && strcmp(firstSets[X][j], "EPSILON")!=0 ){
                             int terminalIndex = getTerminalIndex(firstSets[X][j]);
                             if(terminalIndex == -1) continue;
                            char prod_str[50] = "";
                            sprintf(prod_str, "%d", i); // Convert production index to string
                            parsingTable[A][terminalIndex] = strdup(prod_str);
                            if ( parsingTable[A][terminalIndex] == NULL) {
                                fprintf(stderr, "Memory allocation error (strdup) in buildParsingTable!\n");
                                exit(1);
                             }

                        }
                    }

                    if(firstSets[X][getTerminalIndex("EPSILON")] == NULL) break; //If no epsilon, break
                    k++;
                    //If all symbols have epsilon, then use follow set
                    if(p->rhs[k] == NULL && firstSets[X][getTerminalIndex("EPSILON")] != NULL){
                          for(int j = 0; j<MAX_TERMINALS; ++j){ //Find FOLLOW(A)
                            if(followSets[A][j]!=NULL){
                                int terminalIndex = getTerminalIndex(followSets[A][j]);
                                if (terminalIndex == -1) continue;
                                char prod_str[50] = "";
                                sprintf(prod_str, "%d", i); // Convert production index to string
                                parsingTable[A][terminalIndex] = strdup(prod_str);
                                if ( parsingTable[A][terminalIndex] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in buildParsingTable!\n");
                                    exit(1);
                                 }
                            }
                        }
                    }

                }

        }
    }
}
// New Function: Convert a production index to its string representation
char* productionToString(int productionIndex) {
    if (productionIndex < 0 || grammar[productionIndex].rhsLength == 0) {
        return "Invalid Production"; // Handle invalid index
    }

    Production *p = &grammar[productionIndex];
    static char productionStr[100]; // Static buffer to store the string
    char nonTerminalStr[20];

     //Map NonTerminal to String
    if(p->lhs == NONTERM_E) strcpy(nonTerminalStr, "E");
    else if (p->lhs == NONTERM_EPRIME) strcpy(nonTerminalStr, "E'");
    else if (p->lhs == NONTERM_T) strcpy(nonTerminalStr, "T");
    else if (p->lhs == NONTERM_TPRIME) strcpy(nonTerminalStr, "T'");
    else if(p->lhs == NONTERM_F) strcpy(nonTerminalStr, "F");
    else {
        strcpy(nonTerminalStr, "UNKNOWN");
    }

    snprintf(productionStr, sizeof(productionStr), "%s -> ", nonTerminalStr);

    for (int i = 0; i < p->rhsLength; i++) {
        strncat(productionStr, p->rhs[i], sizeof(productionStr) - strlen(productionStr) - 1);
        if (i < p->rhsLength - 1) {
            strncat(productionStr, " ", sizeof(productionStr) - strlen(productionStr) - 1);
        }
    }

    return productionStr;
}


void printParsingTable() {
    // Modified to print production strings
     printf("\nParsing Table:\n");
    printf("------------------------------------------------------------\n");
    printf("%-10s", ""); // Empty space for row labels

    // Print terminal headers
    for(int j=0; j<MAX_TERMINALS; ++j){
       if(terminals[j]!=NULL) printf("%-20s", terminals[j]);
    }
    printf("\n");


    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        // Print non-terminal label
        if(i == NONTERM_E) printf("%-10s", "E");
        else if (i == NONTERM_EPRIME) printf("%-10s", "E'");
        else if (i == NONTERM_T) printf("%-10s", "T");
        else if (i == NONTERM_TPRIME) printf("%-10s", "T'");
        else if (i == NONTERM_F) printf("%-10s", "F");


        for (int j = 0; j < MAX_TERMINALS; j++) {
            if (parsingTable[i][j] != NULL) {
                int productionIndex = atoi(parsingTable[i][j]);
                printf("%-20s", productionToString(productionIndex)); // Print string
            } else {
                printf("%-20s", "-"); // Indicate error/empty entry
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------------------\n");
}

int getTerminalIndex(const char *terminal) {
    // (Same as before, no changes needed)
    for (int i = 0; terminals[i] != NULL; i++) {
        if (strcmp(terminal, terminals[i]) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

NonTerminal getNonTerminal(const char *nonTerminal) {
    // (Same as before, no changes needed)
   if (strcmp(nonTerminal, "E") == 0) return NONTERM_E;
    if (strcmp(nonTerminal, "E'") == 0) return NONTERM_EPRIME;
    if (strcmp(nonTerminal, "T") == 0) return NONTERM_T;
    if (strcmp(nonTerminal, "T'") == 0) return NONTERM_TPRIME;
    if (strcmp(nonTerminal, "F") == 0) return NONTERM_F;
     fprintf(stderr, "Invalid non-terminal: %s\n", nonTerminal);
    return -1;
}

bool isNonTerminal(const char* symbol){
    // (Same as before, no changes needed)
   if (strcmp(symbol, "E") == 0) return true;
    if (strcmp(symbol, "E'") == 0) return true;
    if (strcmp(symbol, "T") == 0) return true;
    if (strcmp(symbol, "T'") == 0) return true;
    if (strcmp(symbol, "F") == 0) return true;
    return false;
}

int getProductionIndex(NonTerminal lhs, const char** rhs, int rhsLength) {
     // (Same as before, no changes needed)
    for (int i = 0; grammar[i].rhsLength != 0; i++) { // Use rhsLength
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
    return -1; // Not found
}

TerminalIndex getTokenIndex(int token) {
    // (Same as before, no changes needed)
   switch (token) {
        case IDENTIFIER: return IDENTIFIER_INDEX;
        case PLUS:       return PLUS_INDEX;
        case TIMES:      return TIMES_INDEX;
        case LPAREN:     return LPAREN_INDEX;
        case RPAREN:     return RPAREN_INDEX;
        case ENDMARKER:  return ENDMARKER_INDEX;
        default:         return -1; // Invalid token
    }
}

void parseInput() {
    // (Same as before, no changes needed)
   push("ENDMARKER");  // Push endmarker onto the stack
    push("E");      // Push the start symbol onto the stack

    int lookaheadToken = yylex();  // Get the first token *type*
    int lookahead = getTokenIndex(lookaheadToken); // Get the *index*

    while (!isStackEmpty()) {
        char *top = pop();

        if (isNonTerminal(top)) {
            int nonTermIndex = getNonTerminal(top);
            if (nonTermIndex == -1) {
                fprintf(stderr, "Invalid NonTerminal index!\n");
                free(top);
                freeStack();
                return;
            }
             if (lookahead == -1) { //CRITICAL CHECK
                fprintf(stderr, "Invalid lookahead index!\n");
                free(top);
                freeStack();
                return;
            }

            char *productionIndexStr = parsingTable[nonTermIndex][lookahead];

            if (productionIndexStr != NULL) {
                int productionIndex = atoi(productionIndexStr);
                Production *p = &grammar[productionIndex];

                // Push RHS symbols onto stack in reverse order
                for (int i = p->rhsLength - 1; i >= 0; i--) {
                    if (strcmp(p->rhs[i], "EPSILON") != 0) {
                        push(p->rhs[i]);
                    }
                }
                free(top);
            } else {
                printf("Syntax Error: No production for %s with lookahead %s\n", top, terminals[lookahead]);
                free(top);
                freeStack();
                return;
            }
        } else if (strcmp(top, terminals[lookahead]) == 0) {
            // Matched lookahead, consume token
            if (strcmp(terminals[lookahead], "ENDMARKER") == 0) {
                printf("Parsing successful!\n");
                free(top);
                freeStack();
                return;
            }
            free(top);
            lookaheadToken = yylex(); // Get next token *type*
            lookahead = getTokenIndex(lookaheadToken); // Get *index*

        } else {
            printf("Syntax Error: Expected %s, but got %s (%d)\n", top, terminals[lookahead], lookahead);
            free(top);
            freeStack();
            return;
        }
    }
    printf("Parsing failed (unexpected end of input or stack not empty).\n");
    freeStack();
}

void yyerror(const char *s) {
    // (Same as before, no changes needed)
   fprintf(stderr, "Error: %s near token %s\n", s, yytext);
}

int main() {
    // (Same as before, no changes needed)
  yyparse();
     //Free allocated memory (FIRST, FOLLOW, and Parse Table)
    for(int i=0; i<NUM_NONTERMINALS; ++i){
        for(int j=0; j<MAX_TERMINALS; ++j){
            if(firstSets[i][j] != NULL) free(firstSets[i][j]);
            if(followSets[i][j] != NULL) free(followSets[i][j]);
            if(parsingTable[i][j] != NULL) free(parsingTable[i][j]);
        }
    }
    return 0;
}
