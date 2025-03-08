%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULE_SYMBOLS 10
#define MAX_TOKENS 4
#define MAX_PRODUCTION_DISPLAY_LENGTH 100
#define MAX_NAME_LENGTH 20
#define INVALID_LOOKUP -1
void yyerror(const char* s);

typedef enum {
    S,
    A,
    B,
    NUM_NONTERMINALS
} GrammarSymbol;

typedef enum{
    LOWER_A_INDEX,
    LOWER_B_INDEX,
    END_INDEX,
    EMPTY_INDEX,
    NUM_TERMINALS_ENUM
} TokenIndex;

typedef struct ProductionRule {
    GrammarSymbol leftSide;
    char* rightSide[MAX_RULE_SYMBOLS];
    int rightSideLength;
} ProductionRule;

typedef struct StackNode {
    char *symbol;
    struct StackNode *next;
} StackNode;


ProductionRule grammar[] = {
    {S, {"A", "B", NULL}, 2},  // S -> AB
    {A, {"a", "A", NULL}, 2},  // A -> aA
    {A, {"EMPTY", NULL}, 1},  // A -> e (epsilon)
    {B, {"b", NULL}, 1},      // B -> b
    {S, {NULL}, 0} 
};

char *parseTable[NUM_NONTERMINALS][MAX_TOKENS];
char *tokens[] = {"a", "b", "END", "EMPTY", NULL}; // a and b are terminals.

char *firstSet[NUM_NONTERMINALS][MAX_TOKENS];
char *followSet[NUM_NONTERMINALS][MAX_TOKENS];

StackNode *stack = NULL;

int appliedRules[100]; 
int numAppliedRules = 0;

void initializeSymbolSets();
void clearParseTable();
void releaseMemory();
void safeStringCopy(char** destination, const char* source, const char* context);

void calculateFirstSets();
void calculateFollowSets();
void constructParseTable();
void displayParseTable();

int getTokenIndex(const char *token);
GrammarSymbol getGrammarSymbol(const char *nonTerminal);
bool isNonTerminal(const char* symbol);

char* getProductionRuleString(int ruleIndex);
void stackPush(const char *symbol);
char *stackPop();
bool isStackEmpty();
void releaseStack();
void analyzeInput();
void reportError(const char *message);

int resetLexer();
TokenIndex getTokenTypeIndex(int tokenType);

extern int yylex();
extern char *yytext;

int parseDoneFlag = 0;

void printGrammar();
void printFirstSets();
void printFollowSets();
void printAppliedRules();

%}

%union {
    char *string;
    int   token;
}

%token <string> LOWER_A
%token LOWER_B END
%token  END_OF_INPUT

%start program

%%

program :  {
            initializeSymbolSets();
            clearParseTable();

            calculateFirstSets();
            calculateFollowSets();
            constructParseTable();

            printf("\n--- Grammar ---\n");
            printGrammar();

            printf("\n--- FIRST Sets ---\n");
            printFirstSets();

            printf("\n--- FOLLOW Sets ---\n");
            printFollowSets();

            printf("\n--- Parse Table ---\n");
            displayParseTable();


            while(1){
                analyzeInput();
                if (parseDoneFlag) {
                    resetLexer();
                }
            }
           }
           ;
%%


void initializeSymbolSets() {
    // Initialize first and follow sets to NULL
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < MAX_TOKENS; j++) {
            firstSet[i][j] = NULL;
            followSet[i][j] = NULL;
        }
    }
}

void clearParseTable() {
    // Initialize parsing table to NULL
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < MAX_TOKENS; j++) {
            parseTable[i][j] = NULL;
        }
    }
}

void safeStringCopy(char** destination, const char* source, const char* context) {
    *destination = strdup(source);
    if (*destination == NULL) {
        fprintf(stderr, "Memory allocation error (strdup) in %s!\n", context);
        exit(EXIT_FAILURE);
    }
}

void calculateFirstSets() {
   bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; grammar[i].rightSideLength != 0 ; i++) {
            ProductionRule *rule = &grammar[i];

            //Rule 1: If X is a terminal, FIRST(X) = {X}
            if(!isNonTerminal(rule->rightSide[0])){
                int terminalIndex = getTokenIndex(rule->rightSide[0]);
                if(firstSet[rule->leftSide][terminalIndex] == NULL){
                     safeStringCopy(&firstSet[rule->leftSide][terminalIndex], rule->rightSide[0], "calculateFirstSets");
                     changed = true;
                }
            } else {
                //Rule 2: If X->EMPTY, add EMPTY to FIRST(X)
                if(strcmp(rule->rightSide[0], "EMPTY")==0){
                    int emptyIndex = getTokenIndex("EMPTY");
                    if(firstSet[rule->leftSide][emptyIndex] == NULL){
                        safeStringCopy(&firstSet[rule->leftSide][emptyIndex], "EMPTY", "calculateFirstSets");
                        changed = true;
                    }
                } else {
                    //Rule 3: If X is a non-terminal, and X-> Y1 Y2...Yk
                    int k=0;
                    while(rule->rightSide[k]!=NULL){
                        if(!isNonTerminal(rule->rightSide[k])){
                            int terminalIndex = getTokenIndex(rule->rightSide[k]);
                            if(firstSet[rule->leftSide][terminalIndex] == NULL){
                                safeStringCopy(&firstSet[rule->leftSide][terminalIndex], rule->rightSide[k], "calculateFirstSets");
                                changed = true;
                            }
                            break; //No more processing.
                        }

                        GrammarSymbol Y = getGrammarSymbol(rule->rightSide[k]);

                        //Add all of FIRST(Yi) except EMPTY
                        for(int j=0; j<MAX_TOKENS; ++j){
                            if(firstSet[Y][j] != NULL && strcmp(firstSet[Y][j], "EMPTY") != 0){
                                if(firstSet[rule->leftSide][j] == NULL){
                                     safeStringCopy(&firstSet[rule->leftSide][j], firstSet[Y][j], "calculateFirstSets");
                                     changed = true;
                                }
                            }
                        }

                        //If FIRST(Yi) does not contain empty, stop.
                        if(firstSet[Y][getTokenIndex("EMPTY")] == NULL) break;

                        k++;
                        //if all Y1...Yk have EMPTY in FIRST, add EMPTY to FIRST(X)
                        if(rule->rightSide[k] == NULL && firstSet[Y][getTokenIndex("EMPTY")] != NULL){
                             if(firstSet[rule->leftSide][getTokenIndex("EMPTY")] == NULL){
                                 safeStringCopy(&firstSet[rule->leftSide][getTokenIndex("EMPTY")], "EMPTY", "calculateFirstSets");
                                 changed = true;
                             }
                        }
                    }
                }
            }
        }
    }
}

void calculateFollowSets() {
    // Rule 1: FOLLOW(S) = {$}
    safeStringCopy(&followSet[S][getTokenIndex("END")], "END", "calculateFollowSets");

    bool changed = true;
    while(changed){
        changed = false;

        for(int i=0; grammar[i].rightSideLength != 0; ++i){ 
            ProductionRule *rule = &grammar[i];
            //Iterate through symbols on RHS.
            for(int j=0; j<rule->rightSideLength; ++j){
                if(isNonTerminal(rule->rightSide[j])){
                    GrammarSymbol B = getGrammarSymbol(rule->rightSide[j]);

                    //Rule 2: If A->alpha B beta, FOLLOW(B) = {FIRST(beta) - EMPTY}
                    int k = j+1;
                    while(rule->rightSide[k] != NULL){ //While there is a beta
                        if(!isNonTerminal(rule->rightSide[k])){ //If beta is terminal
                            int terminalIndex = getTokenIndex(rule->rightSide[k]);
                            if(followSet[B][terminalIndex] == NULL){
                                 safeStringCopy(&followSet[B][terminalIndex], rule->rightSide[k], "calculateFollowSets");
                                 changed = true;
                            }
                            break; //No more processing of beta
                        }

                        GrammarSymbol beta = getGrammarSymbol(rule->rightSide[k]);

                        for(int m=0; m<MAX_TOKENS; ++m){
                             if(firstSet[beta][m] != NULL && strcmp(firstSet[beta][m], "EMPTY") !=0){ //Add FIRST(beta) - EMPTY
                                if(followSet[B][m] == NULL){
                                    safeStringCopy(&followSet[B][m], firstSet[beta][m], "calculateFollowSets");
                                    changed = true;
                                }
                             }
                        }
                        //If EMPTY not in FIRST(beta), stop.
                        if(firstSet[beta][getTokenIndex("EMPTY")] == NULL) break;
                        k++;
                    }
                    //Rule 3: If A->alpha B or A->alpha B beta where EMPTY is in FIRST(beta), FOLLOW(B) = FOLLOW(B) U FOLLOW(A)
                    if(rule->rightSide[k] == NULL){ //If beta is empty or all beta have empty
                        GrammarSymbol A = rule->leftSide;
                        for(int m=0; m<MAX_TOKENS; ++m){
                            if(followSet[A][m] != NULL){ //Everything in FOLLOW(A) is in FOLLOW(B)
                                if(followSet[B][m] == NULL){
                                    safeStringCopy(&followSet[B][m], followSet[A][m], "calculateFollowSets");
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

void constructParseTable() {
    // Iterate through productions
    for (int i = 0; grammar[i].rightSideLength != 0; i++) { 
        ProductionRule *rule = &grammar[i];
        GrammarSymbol A = rule->leftSide;

        // Rule 1: For each terminal a in FIRST(alpha), add A -> alpha to M[A, a]
        //Process RHS
        if(strcmp(rule->rightSide[0], "EMPTY") == 0){
            // Rule 2: If ε is in FIRST(α), for each terminal b in FOLLOW(A), add A -> α to M[A, b]
            for(int j = 0; j<MAX_TOKENS; ++j){ //Find FOLLOW(A)
                if(followSet[A][j]!=NULL){
                    int terminalIndex = getTokenIndex(followSet[A][j]);
                    if (terminalIndex == INVALID_LOOKUP) continue; //Skip if invalid index.
                    char ruleString[MAX_NAME_LENGTH] = "";
                    snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                    safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable");
                }
            }
        } else { //Not empty
            int k=0;
            while(rule->rightSide[k] != NULL){
                if(!isNonTerminal(rule->rightSide[k])){ //If terminal
                    int terminalIndex = getTokenIndex(rule->rightSide[k]);
                    if(terminalIndex == INVALID_LOOKUP) break; //invalid terminal
                    char ruleString[MAX_NAME_LENGTH] = "";
                    snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                    safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable"); //Add the production
                    break;
                }
                //If NonTerminal
                GrammarSymbol X = getGrammarSymbol(rule->rightSide[k]);

                for(int j=0; j<MAX_TOKENS; j++){//For each terminal in FIRST(X)
                    if(firstSet[X][j] != NULL && strcmp(firstSet[X][j], "EMPTY")!=0 ){
                        int terminalIndex = getTokenIndex(firstSet[X][j]);
                        if(terminalIndex == INVALID_LOOKUP) continue;
                        char ruleString[MAX_NAME_LENGTH] = "";
                        snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                        safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable");
                    }
                }

                if(firstSet[X][getTokenIndex("EMPTY")] == NULL) break; //If no empty, break
                k++;
                //If all symbols have empty, then use follow set
                if(rule->rightSide[k] == NULL && firstSet[X][getTokenIndex("EMPTY")] != NULL){
                    for(int j = 0; j<MAX_TOKENS; ++j){ //Find FOLLOW(A)
                        if(followSet[A][j]!=NULL){
                            int terminalIndex = getTokenIndex(followSet[A][j]);
                            if (terminalIndex == INVALID_LOOKUP) continue;
                            char ruleString[MAX_NAME_LENGTH] = "";
                            snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                            safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable");
                        }
                    }
                }
            }
        }
    }
}


char* getProductionRuleString(int ruleIndex) {
    if (ruleIndex < 0 || grammar[ruleIndex].rightSideLength == 0) {
        return "Invalid Production"; // Handle invalid index
    }

    ProductionRule *rule = &grammar[ruleIndex];
    static char productionStr[MAX_PRODUCTION_DISPLAY_LENGTH]; // Static buffer to store the string
    char nonTerminalStr[MAX_NAME_LENGTH];

    //Map NonTerminal to String
    if(rule->leftSide == S) strcpy(nonTerminalStr, "S");
    else if (rule->leftSide == A) strcpy(nonTerminalStr, "A");
    else if (rule->leftSide == B) strcpy(nonTerminalStr, "B");
    else {
        strcpy(nonTerminalStr, "UNKNOWN");
    }

    snprintf(productionStr, sizeof(productionStr), "%s -> ", nonTerminalStr);

    for (int i = 0; i < rule->rightSideLength; i++) {
        strncat(productionStr, rule->rightSide[i], sizeof(productionStr) - strlen(productionStr) - 1);
        if (i < rule->rightSideLength - 1) {
            strncat(productionStr, " ", sizeof(productionStr) - strlen(productionStr) - 1);
        }
    }

    return productionStr;
}

void displayParseTable() {
    printf("\nParsing Table:\n");
    printf("----------------------------------------\n");
    printf("%-8s", ""); 

    // Print terminal headers
    for(int j=0; j<MAX_TOKENS - 1; ++j){ 
       if(tokens[j]!=NULL) printf("%-10s", tokens[j]);
    }
    printf("\n");
    printf("----------------------------------------\n"); 


    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        // Print non-terminal label
        if(i == S) printf("%-8s", "S");
        else if (i == A) printf("%-8s", "A");
        else if (i == B) printf("%-8s", "B");


        for (int j = 0; j < MAX_TOKENS - 1; j++) { // Exclude last column
            if (parseTable[i][j] != NULL) {
                int ruleIndex = atoi(parseTable[i][j]);
                printf("%-10s", getProductionRuleString(ruleIndex));
            } else {
                printf("%-10s", "-"); // Indicate error/empty entry
            }
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
}

int getTokenIndex(const char *token) {
    for (int i = 0; tokens[i] != NULL; i++) {
        if (strcmp(token, tokens[i]) == 0) {
            return i;
        }
    }
    return INVALID_LOOKUP; // Not found
}

GrammarSymbol getGrammarSymbol(const char *nonTerminal) {
    if (strcmp(nonTerminal, "S") == 0) return S;
    if (strcmp(nonTerminal, "A") == 0) return A;
    if (strcmp(nonTerminal, "B") == 0) return B;
    fprintf(stderr, "Invalid non-terminal: %s\n", nonTerminal);
    return -1;
}

bool isNonTerminal(const char* symbol){
    if (strcmp(symbol, "S") == 0) return true;
    if (strcmp(symbol, "A") == 0) return true;
    if (strcmp(symbol, "B") == 0) return true;
    return false;
}

TokenIndex getTokenTypeIndex(int tokenType) {
    switch (tokenType) {
        case LOWER_A: return LOWER_A_INDEX;
        case LOWER_B: return LOWER_B_INDEX;
        case END:  return END_INDEX;
        default:         return INVALID_LOOKUP; // Invalid token
    }
}

void stackPush(const char *symbol) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed in stackPush()\n");
        exit(EXIT_FAILURE);
    }
    safeStringCopy(&newNode->symbol, symbol, "stackPush");
    newNode->next = stack;
    stack = newNode;
}

char *stackPop() {
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

void releaseStack() {
    while (!isStackEmpty()) {
        char* temp = stackPop();
        if(temp!=NULL) free(temp);
    }
}

void analyzeInput() {
    numAppliedRules = 0;

    stackPush("END");
    stackPush("S");  

    int nextToken = yylex();  
    int lookahead = getTokenTypeIndex(nextToken); 

    while (!isStackEmpty()) {
        char *top = stackPop();

        if (isNonTerminal(top)) {
            int nonTermIndex = getGrammarSymbol(top);
            if (nonTermIndex == -1) {
                fprintf(stderr, "Invalid NonTerminal index!\n");
                free(top);
                releaseStack();
                return;
            }
            if (lookahead == INVALID_LOOKUP) { //CRITICAL CHECK
                fprintf(stderr, "Invalid lookahead index!\n");
                free(top);
                releaseStack();
                return;
            }

            char *ruleIndexStr = parseTable[nonTermIndex][lookahead];

            if (ruleIndexStr != NULL) {
                int ruleIndex = atoi(ruleIndexStr);
                appliedRules[numAppliedRules++] = ruleIndex; 
                ProductionRule *rule = &grammar[ruleIndex];

                // Push RHS symbols onto stack in reverse order
                for (int i = rule->rightSideLength - 1; i >= 0; i--) {
                    if (strcmp(rule->rightSide[i], "EMPTY") != 0) {
                        stackPush(rule->rightSide[i]);
                    }
                }
                free(top);
            } else {
                printf("Syntax Error: No production for %s with lookahead %s\n", top, tokens[lookahead]);
                free(top);
                releaseStack();
                return;
            }
        } else if (strcmp(top, tokens[lookahead]) == 0) {
            // Matched lookahead, consume token
            if (strcmp(tokens[lookahead], "END") == 0) {
                printf("Parsing successful!\n");
                printAppliedRules();
                free(top);
                releaseStack();
                return;
            }
            free(top);
            nextToken = yylex(); // Get next token *type*
            lookahead = getTokenTypeIndex(nextToken); // Get *index*

        } else {
            printf("Syntax Error: Expected %s, but got %s (%d)\n", top, tokens[lookahead], lookahead);
            free(top);
            releaseStack();
            return;
        }
    }
    printf("Parsing failed (unexpected end of input or stack not empty).\n");
    printAppliedRules();
    releaseStack();
}

void reportError(const char *message) {
    fprintf(stderr, "Error: %s near token %s\n", message, yytext);
}

int resetLexer() {
    parseDoneFlag = 0;
    while (getchar() != '\n');
    return 0;
}

void releaseMemory() {
    for(int i=0; i<NUM_NONTERMINALS; ++i){
        for(int j=0; j<MAX_TOKENS; ++j){
            if(firstSet[i][j] != NULL) free(firstSet[i][j]);
            if(followSet[i][j] != NULL) free(followSet[i][j]);
            if(parseTable[i][j] != NULL) free(parseTable[i][j]);
        }
    }
}

int main() {
    yyparse();
    releaseMemory();
    return 0;
}

void yyerror(const char *s) {
    reportError(s); // Call your reportError
}

void printGrammar() {
    for (int i = 0; grammar[i].rightSideLength != 0 || i == 0; i++) {
        printf("%s\n", getProductionRuleString(i));
    }
}

void printFirstSets() {
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        printf("FIRST(%s): { ", (i == S) ? "S" : ((i == A) ? "A" : "B"));
        for (int j = 0; j < MAX_TOKENS; j++) {
             if (firstSet[i][j] != NULL) {
                printf("%s ", firstSet[i][j]);
            }
        }
        printf("}\n");
    }
}

void printFollowSets() {
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
         printf("FOLLOW(%s): { ", (i == S) ? "S" : ((i == A) ? "A" : "B"));
        for (int j = 0; j < MAX_TOKENS; j++) {
             if (followSet[i][j] != NULL) {
                printf("%s ", followSet[i][j]);
            }
        }
        printf("}\n");
    }
}

void printAppliedRules() {
     printf("\n--- Applied Productions ---\n");
    if (numAppliedRules == 0) {
        printf("No productions applied.\n");
        return;
    }
    for (int i = 0; i < numAppliedRules; i++) {
        printf("%s\n", getProductionRuleString(appliedRules[i]));
    }
}