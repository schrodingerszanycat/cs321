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
    NONTERMINAL_SENTINEL, // Start symbol
    TOTAL_NONTERMINALS  
} SymbolCategory;

typedef struct GrammarRule {  
    int head; // Left-hand side 
    char* body[10]; // Right-hand side (RHS)
    int body_length; 
} GrammarRule;

GrammarRule *grammar_rules = NULL; 
int rule_count = 0;
int rule_capacity = 0;

#define MAX_TERMINALS 10 
#define MAX_DERIVATION_DEPTH 100 

char *predictive_parsing_table[MAX_DERIVATION_DEPTH][MAX_TERMINALS]; 

char **terminal_symbols = NULL; 
int terminal_count = 0;
int terminal_capacity = 0;

char ***first_sets; 
char ***follow_sets; 
char** nonterminal_symbols = NULL; 
int nonterminal_count = 0;


typedef struct TokenNode {  
    char *data;
    struct TokenNode *next_node;  
} TokenNode;

TokenNode *parse_stack = NULL;  

void stack_push(const char *symbol) {  
    TokenNode *new_node = (TokenNode *)malloc(sizeof(TokenNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failure in stack_push()\n");
        exit(1);
    }
    new_node->data = strdup(symbol);
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation error (strdup)!\n");
        exit(1);
    }
    new_node->next_node = parse_stack;
    parse_stack = new_node;
}

char *stack_pop() {
    if (parse_stack == NULL) {
        return NULL;
    }
    TokenNode *temp = parse_stack;
    parse_stack = parse_stack->next_node;
    char *symbol = temp->data;
    free(temp);
    return symbol;
}

bool is_stack_empty() {
    return parse_stack == NULL;
}

void free_stack() {  
    while (!is_stack_empty()) {
        char* temp = stack_pop();
        if (temp != NULL) free(temp);
    }
}

void calculate_first_sets();
void calculate_follow_sets();
void construct_parsing_table();
void display_parsing_table();
int retrieve_terminal_index(const char *terminal);
int retrieve_nonterminal_index(const char *nonTerminal);
int retrieve_rule_index(int head, const char** body, int body_length);
bool is_nonterminal(const char* symbol);
void perform_parse();
void report_syntax_error(const char *message);
int get_token_index(const char* token);
char* rule_to_string(int rule_index);
void display_first_sets();
void display_follow_sets();
char* nonterminal_to_string(int nt);
void show_derivation(int derivation[], int derivation_length);
void load_grammar();
void insert_terminal(const char* terminal);
void insert_nonterminal(const char* nonTerminal);
void insert_rule(int head, char** body, int body_length);
void release_memory();
void yyerror(const char *s);

#ifdef __cplusplus
extern "C" int yylex(void);
#endif

int parsing_complete = 0; 

int reset_lexer() {  
    parsing_complete = 0;
    return 0;
}
%}

%union {
    char *string; 
    int   token_code;
}

%token <string> TERMINAL  
%token ADD MULTIPLY LEFT_PAREN RIGHT_PAREN END_OF_STREAM 
%token END_OF_INPUT

%start compilation_unit 

%%

compilation_unit 
    :   {
            load_grammar();
            calculate_first_sets();
            calculate_follow_sets();
            construct_parsing_table();
            display_first_sets();
            display_follow_sets();
            display_parsing_table();

            printf("Terminals: ");
            for (int i = 0; i < terminal_count; i++) {
                printf("%s ", terminal_symbols[i]);
            }
            printf("\n");

            char input_buffer[1000];
            printf("Enter input string (or 'quit' to exit):\n");
            while (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                input_buffer[strcspn(input_buffer, "\n")] = 0; // Remove trailing newline

                if (strcmp(input_buffer, "quit") == 0) {
                    break;
                }

                if (strlen(input_buffer) > 0) {
                    YY_BUFFER_STATE buffer = yy_scan_string(input_buffer);
                    perform_parse();
                    yy_delete_buffer(buffer);
                    reset_lexer();
                } else {
                    printf("Please enter a non-empty string.\n");
                }
                printf("Enter input string (or 'quit' to exit):\n");
            }
            release_memory();
        }
    ;

%%

void insert_terminal(const char* terminal) {  
    // Check if terminal already exists to avoid duplicates
    for (int i = 0; i < terminal_count; i++) {
        if (strcmp(terminal_symbols[i], terminal) == 0) {
            return; // Terminal already exists, no need to add
        }
    }

    if (terminal_count == terminal_capacity) {
        terminal_capacity = (terminal_capacity == 0) ? 1 : terminal_capacity * 2; // Initial or Double
        terminal_symbols = (char**)realloc(terminal_symbols, terminal_capacity * sizeof(char*));
        if (!terminal_symbols) {
            fprintf(stderr, "Memory allocation error for terminal_symbols.\n");
            exit(1);
        }
    }

    terminal_symbols[terminal_count++] = strdup(terminal);
    if (!terminal_symbols[terminal_count-1]) {
        fprintf(stderr, "Memory allocation error for strdup.\n");
        exit(1);
    }
}

void insert_nonterminal(const char* nonTerminal) {  
    if (nonterminal_count == 0 || retrieve_nonterminal_index(nonTerminal) == -1)
    {
        nonterminal_count++;
        nonterminal_symbols = (char**)realloc(nonterminal_symbols, nonterminal_count * sizeof(char*));
         if (!nonterminal_symbols) {
             fprintf(stderr, "Memory allocation error for Non-Terminals.\n");
             exit(1);
         }
        nonterminal_symbols[nonterminal_count-1] = strdup(nonTerminal);
        if (!nonterminal_symbols[nonterminal_count-1]) {
           fprintf(stderr, "Memory allocation error for strdup.\n");
           exit(1);
        }
    }
}

void insert_rule(int head, char** body, int body_length) { 
    if (rule_count == rule_capacity) {
        rule_capacity = (rule_capacity == 0) ? 1 : rule_capacity * 2;
        grammar_rules = (GrammarRule*)realloc(grammar_rules, rule_capacity * sizeof(GrammarRule));
         if (!grammar_rules) {
           fprintf(stderr, "Memory allocation error for Grammar.\n");
           exit(1);
         }
    }

    grammar_rules[rule_count].head = head;
    grammar_rules[rule_count].body_length = body_length;
    for (int i = 0; i < body_length; i++) {
        grammar_rules[rule_count].body[i] = strdup(body[i]);
        if (!grammar_rules[rule_count].body[i]) {
            fprintf(stderr, "Memory allocation error for strdup.\n");
            exit(1);
        }
    }
    grammar_rules[rule_count].body[body_length] = NULL;

    rule_count++;
}

void load_grammar() {  
    char input_buffer[1000];
    int num_grammar_rules;

    printf("Enter the number of productions: ");
    fgets(input_buffer, sizeof(input_buffer), stdin);
    sscanf(input_buffer, "%d", &num_grammar_rules);

    insert_terminal("END_OF_STREAM");
    insert_terminal("EPS");

    printf("Enter the productions (e.g., E -> T E'  |  EPS):\n");

    for (int i = 0; i < num_grammar_rules; i++) {
        printf("Production %d: ", i + 1);
        fgets(input_buffer, sizeof(input_buffer), stdin);
        input_buffer[strcspn(input_buffer, "\n")] = 0;

        char lhs_str[100];
        char rhs_str[1000];
        if (sscanf(input_buffer, "%s -> %[^\n]", lhs_str, rhs_str) != 2) {
            fprintf(stderr, "Invalid production format.\n");
            exit(1);
        }

        insert_nonterminal(lhs_str);
        int head = retrieve_nonterminal_index(lhs_str);

        char *rhs_tokens[10]; // Maximum 10 tokens on the RHS
        int body_token_count = 0;
        char *token = strtok(rhs_str, " ");
        while (token != NULL) {
            if (strcmp(token, "|") != 0) {
                if (!is_nonterminal(token)) {
                    insert_terminal(token);
                } else {
                    insert_nonterminal(token);
                }
                rhs_tokens[body_token_count++] = token;
            }
            token = strtok(NULL, " ");
        }

        insert_rule(head, rhs_tokens, body_token_count);
    }

    if (rule_count == rule_capacity) {
        rule_capacity += 1;
        grammar_rules = (GrammarRule*)realloc(grammar_rules, rule_capacity * sizeof(GrammarRule));
         if (!grammar_rules) {
           fprintf(stderr, "Memory allocation error for Grammar.\n");
           exit(1);
         }
    }
    grammar_rules[rule_count].head = -1; 
    grammar_rules[rule_count].body_length = 0;
    rule_count++;
}

void calculate_first_sets() { 
    first_sets = (char***)malloc(nonterminal_count * sizeof(char**));
    if (!first_sets) {
        fprintf(stderr, "Memory allocation error for first_sets.\n");
        exit(1);
    }
    for (int i = 0; i < nonterminal_count; i++) {
        first_sets[i] = (char**)malloc(terminal_count * sizeof(char*));
        if (!first_sets[i]) {
            fprintf(stderr, "Memory allocation error for first_sets.\n");
            exit(1);
        }
        for (int j = 0; j < terminal_count; j++) {
            first_sets[i][j] = NULL;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < rule_count && grammar_rules[i].body_length != 0; i++) {
            GrammarRule *rule = &grammar_rules[i];
            if (!is_nonterminal(rule->body[0])) {
                if (first_sets[rule->head][retrieve_terminal_index(rule->body[0])] == NULL) {
                    first_sets[rule->head][retrieve_terminal_index(rule->body[0])] = strdup(rule->body[0]);
                    if (first_sets[rule->head][retrieve_terminal_index(rule->body[0])] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                        exit(1);
                    }
                    changed = true;
                }
            } else {
                if (strcmp(rule->body[0], "EPS") == 0) {
                    if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                        first_sets[rule->head][retrieve_terminal_index("EPS")] = strdup("EPS");
                        if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                            exit(1);
                        }
                        changed = true;
                    }
                } else {
                    int k = 0;
                    while (rule->body[k] != NULL) {
                        if (!is_nonterminal(rule->body[k])) {
                            if (first_sets[rule->head][retrieve_terminal_index(rule->body[k])] == NULL) {
                                first_sets[rule->head][retrieve_terminal_index(rule->body[k])] = strdup(rule->body[k]);
                                if (first_sets[rule->head][retrieve_terminal_index(rule->body[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                            break;
                        }
                        int Y = retrieve_nonterminal_index(rule->body[k]);
                        for (int j = 0; j < terminal_count; ++j) {
                            if (first_sets[Y][j] != NULL && strcmp(first_sets[Y][j], "EPS") != 0) {
                                if (first_sets[rule->head][j] == NULL) {
                                    first_sets[rule->head][j] = strdup(first_sets[Y][j]);
                                    if (first_sets[rule->head][j] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                                        exit(1);
                                    }
                                    changed = true;
                                }
                            }
                        }
                        if (first_sets[Y][retrieve_terminal_index("EPS")] == NULL) break;
                        k++;
                        if (rule->body[k] == NULL && first_sets[Y][retrieve_terminal_index("EPS")] != NULL) {
                            if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                                first_sets[rule->head][retrieve_terminal_index("EPS")] = strdup("EPS");
                                if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
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

void calculate_follow_sets() { 
    follow_sets = (char***)malloc(nonterminal_count * sizeof(char**));
    if (!follow_sets) {
        fprintf(stderr, "Memory allocation error for follow_sets.\n");
        exit(1);
    }
    for (int i = 0; i < nonterminal_count; i++) {
        follow_sets[i] = (char**)malloc(terminal_count * sizeof(char*));
        if (!follow_sets[i]) {
            fprintf(stderr, "Memory allocation error for follow_sets.\n");
            exit(1);
        }
        for (int j = 0; j < terminal_count; j++) {
            follow_sets[i][j] = NULL;
        }
    }

    follow_sets[0][retrieve_terminal_index("END_OF_STREAM")] = strdup("END_OF_STREAM");
    if (follow_sets[0][retrieve_terminal_index("END_OF_STREAM")] == NULL) {
        fprintf(stderr, "Memory allocation error (strdup).\n");
        exit(1);
    }
    bool changed = true;
    while (changed) {
        changed = false;

        for (int i = 0; i < rule_count && grammar_rules[i].body_length != 0; ++i) {
            GrammarRule* rule = &grammar_rules[i];

            for (int j = 0; j < rule->body_length; ++j) {
                if (is_nonterminal(rule->body[j])) {
                    int B = retrieve_nonterminal_index(rule->body[j]);

                    int k = j + 1;
                    while (rule->body[k] != NULL) {
                        if (!is_nonterminal(rule->body[k])) {
                            if (follow_sets[B][retrieve_terminal_index(rule->body[k])] == NULL) {
                                follow_sets[B][retrieve_terminal_index(rule->body[k])] = strdup(rule->body[k]);
                                if (follow_sets[B][retrieve_terminal_index(rule->body[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup).\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                            break;
                        }

                        int beta = retrieve_nonterminal_index(rule->body[k]);

                        for (int m = 0; m < terminal_count; ++m) {
                            if (first_sets[beta][m] != NULL && strcmp(first_sets[beta][m], "EPS") != 0) {
                                if (follow_sets[B][m] == NULL) {
                                    follow_sets[B][m] = strdup(first_sets[beta][m]);
                                    if (follow_sets[B][m] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup).\n");
                                        exit(1);
                                    }
                                    changed = true;
                                }
                            }
                        }
                        if (first_sets[beta][retrieve_terminal_index("EPS")] == NULL) break;
                        k++;
                    }

                    if (rule->body[k] == NULL) {
                        int A = rule->head;
                        for (int m = 0; m < terminal_count; ++m) {
                            if (follow_sets[A][m] != NULL) {
                                if (follow_sets[B][m] == NULL) {
                                    follow_sets[B][m] = strdup(follow_sets[A][m]);
                                    if (follow_sets[B][m] == NULL) {
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

void construct_parsing_table() {  
    for (int i = 0; i < nonterminal_count; ++i) {
        for (int j = 0; j < terminal_count; ++j) {
            predictive_parsing_table[i][j] = NULL;
        }
    }

    for (int i = 0; i < rule_count && grammar_rules[i].body_length != 0; i++) {
        GrammarRule *rule = &grammar_rules[i];
        int A = rule->head;

        if (strcmp(rule->body[0], "EPS") == 0) {
            for (int j = 0; j < terminal_count; ++j) {
                if (follow_sets[A][j] != NULL) {
                    int terminal_index = retrieve_terminal_index(follow_sets[A][j]);
                    if (terminal_index == -1) continue;
                    char rule_str[50] = "";
                    sprintf(rule_str, "%d", i);
                    predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                    if (predictive_parsing_table[A][terminal_index] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup).\n");
                        exit(1);
                    }
                }
            }
        } else {
            int k = 0;
            while (rule->body[k] != NULL) {
                if (!is_nonterminal(rule->body[k])) {
                    int terminal_index = retrieve_terminal_index(rule->body[k]);
                    if (terminal_index == -1) break;
                    char rule_str[50] = "";
                    sprintf(rule_str, "%d", i);
                    predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                    if (predictive_parsing_table[A][terminal_index] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup).\n");
                        exit(1);
                    }
                    break;
                }
                int X = retrieve_nonterminal_index(rule->body[k]);

                for (int j = 0; j < terminal_count; j++) {
                    if (first_sets[X][j] != NULL && strcmp(first_sets[X][j], "EPS") != 0) {
                        int terminal_index = retrieve_terminal_index(first_sets[X][j]);
                        if (terminal_index == -1) continue;
                        char rule_str[50] = "";
                        sprintf(rule_str, "%d", i);
                        predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                        if (predictive_parsing_table[A][terminal_index] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup).\n");
                            exit(1);
                        }
                    }
                }

                if (first_sets[X][retrieve_terminal_index("EPS")] == NULL) break;
                k++;
                if (rule->body[k] == NULL && first_sets[X][retrieve_terminal_index("EPS")] != NULL) {
                    for (int j = 0; j < terminal_count; ++j) {
                        if (follow_sets[A][j] != NULL) {
                            int terminal_index = retrieve_terminal_index(follow_sets[A][j]);
                            if (terminal_index == -1) continue;
                            char rule_str[50] = "";
                            sprintf(rule_str, "%d", i);
                            predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                            if (predictive_parsing_table[A][terminal_index] == NULL) {
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

char* rule_to_string(int rule_index) { 
    if (rule_index < 0 || rule_index >= rule_count || grammar_rules[rule_index].body_length == 0) {
        return "Invalid Production";
    }

    GrammarRule *rule = &grammar_rules[rule_index];
    static char rule_string[100];
    char* nonTerminalStr = nonterminal_to_string(rule->head);

    snprintf(rule_string, sizeof(rule_string), "%s -> ", nonTerminalStr);

    for (int i = 0; i < rule->body_length; i++) {
        strncat(rule_string, rule->body[i], sizeof(rule_string) - strlen(rule_string) - 1);
        if (i < rule->body_length - 1) {
            strncat(rule_string, " ", sizeof(rule_string) - strlen(rule_string) - 1);
        }
    }

    return rule_string;
}

void display_parsing_table() { 
    printf("\nParsing Table:\n");
    printf("------------------------------------------------------------\n");
    printf("%-15s", ""); // Empty space for row labels

    // Print column headers (only terminals)
    for (int j = 0; j < terminal_count; j++) {
        if (!is_nonterminal(terminal_symbols[j]) && strcmp(terminal_symbols[j], "EPS") != 0) {
            printf("%-20s", terminal_symbols[j]);
        }
    }
    printf("\n");

    // Print table rows
    for (int i = 0; i < nonterminal_count; i++) {
        printf("%-15s", nonterminal_to_string(i));

        // Print table entries (only for terminals, excluding EPS)
        for (int j = 0; j < terminal_count; j++) {
            if (!is_nonterminal(terminal_symbols[j]) && strcmp(terminal_symbols[j], "EPS") != 0) {
                if (predictive_parsing_table[i][j] != NULL) {
                    int rule_index = atoi(predictive_parsing_table[i][j]);
                    printf("%-20s", rule_to_string(rule_index));
                } else {
                    printf("%-20s", "-");
                }
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------------------\n");
}

int retrieve_terminal_index(const char *terminal) { 
    for (int i = 0; i < terminal_count; i++) {
        if (strcmp(terminal_symbols[i], terminal) == 0) {
            return i;
        }
    }
    return -1;
}

int retrieve_nonterminal_index(const char *nonTerminal) {
    for (int i = 0; i < nonterminal_count; ++i) {
        if (strcmp(nonterminal_symbols[i], nonTerminal) == 0) return i;
    }
    return -1;
}

bool is_nonterminal(const char* symbol) {  
    for (int i = 0; i < nonterminal_count; ++i) {
        if (strcmp(nonterminal_symbols[i], symbol) == 0) return true;
    }
    return false;
}

int retrieve_rule_index(int head, const char** body, int body_length) {  
    for (int i = 0; i < rule_count; i++) {
        if (grammar_rules[i].head == head && grammar_rules[i].body_length == body_length) {
            bool match = true;
            for (int j = 0; j < body_length; j++) {
                if (strcmp(grammar_rules[i].body[j], body[j]) != 0) {
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

int get_token_index(const char* token) { 
    for (int i = 0; i < terminal_count; ++i) {
        if (strcmp(terminal_symbols[i], token) == 0) return i;
    }
    return -1;
}

void perform_parse() {  
    stack_push("END_OF_STREAM");
    stack_push(nonterminal_symbols[0]);

    int lookahead_token = yylex();

    int derivation[MAX_DERIVATION_DEPTH];
    int derivation_length = 0;

    while (!is_stack_empty()) {
        char *top = stack_pop();

        // Debug: Print current state
        printf("Stack top: %s, Lookahead: %s\n", top, yytext);

        if (is_nonterminal(top)) {
            int nonterm_index = retrieve_nonterminal_index(top);
            if (nonterm_index == -1) {
                fprintf(stderr, "Invalid NonTerminal index!\n");
                free(top);
                free_stack();
                return;
            }

            int lookahead = get_token_index(yytext);
            if (lookahead == -1) {
                fprintf(stderr, "Invalid lookahead index! Token '%s' not in terminals.\n", yytext);
                free(top);
                free_stack();
                return;
            }

            char *rule_index_str = predictive_parsing_table[nonterm_index][lookahead];
            if (rule_index_str != NULL) {
                int rule_index = atoi(rule_index_str);
                GrammarRule *rule = &grammar_rules[rule_index];

                if (derivation_length < MAX_DERIVATION_DEPTH) {
                    derivation[derivation_length++] = rule_index;
                } else {
                    fprintf(stderr, "Derivation too long!\n");
                    free(top);
                    free_stack();
                    return;
                }

                for (int i = rule->body_length - 1; i >= 0; i--) {
                    if (strcmp(rule->body[i], "EPS") != 0) {
                        stack_push(rule->body[i]);
                    }
                }
                free(top);
            } else {
                printf("Syntax Error: No production for %s with lookahead %s\n", top, yytext);
                free(top);
                free_stack();
                return;
            }
        } else {
            // Special handling for END_OF_STREAM
            if (strcmp(top, "END_OF_STREAM") == 0) {
                if (strcmp(yytext, "$") == 0 || yytext[0] == '\0') {
                    printf("Parsing successful!\n");
                    show_derivation(derivation, derivation_length);
                    free(top);
                    free_stack();
                    return;
                } else {
                    printf("Syntax Error: Expected END_OF_STREAM, but got %s\n", yytext);
                    free(top);
                    free_stack();
                    return;
                }
            } else if (strcmp(top, yytext) == 0) {
                free(top);
                lookahead_token = yylex();
            } else {
                printf("Syntax Error: Expected %s, but got %s\n", top, yytext);
                free(top);
                free_stack();
                return;
            }
        }
    }
    printf("Parsing failed (unexpected end of input or stack not empty).\n");
    free_stack();
}

void show_derivation(int derivation[], int derivation_length) { 
    printf("Derivation:\n");
    if (derivation_length > 0) {
        printf("%s", nonterminal_symbols[0]);
        for (int i = 0; i < derivation_length; ++i) {
            printf(" => %s", rule_to_string(derivation[i]));
        }
        printf("\n");
    }
}

void display_first_sets() { 
    printf("\nFIRST Sets:\n");
    printf("---------------------\n");
    for (int i = 0; i < nonterminal_count; i++) {
        printf("FIRST(%s) = { ", nonterminal_to_string(i));
        for (int j = 0; j < terminal_count; j++) {
            if (first_sets[i][j] != NULL) {
                printf("%s", first_sets[i][j]);
                int k = j + 1;
                while (k < terminal_count && first_sets[i][k] == NULL) {
                    k++;
                }
                if (k < terminal_count && first_sets[i][k] != NULL) {
                    printf(", ");
                }
            }
        }
        printf(" }\n");
    }
    printf("---------------------\n");
}

void display_follow_sets() { 
    printf("\nFOLLOW Sets:\n");
    printf("---------------------\n");
    for (int i = 0; i < nonterminal_count; i++) {
        printf("FOLLOW(%s) = { ", nonterminal_to_string(i));
        for (int j = 0; j < terminal_count; j++) {
            if (follow_sets[i][j] != NULL) {
                printf("%s", follow_sets[i][j]);
                int k = j + 1;
                while (k < terminal_count && follow_sets[i][k] == NULL) {
                    k++;
                }
                if (k < terminal_count && follow_sets[i][k] != NULL) {
                    printf(", ");
                }
            }
        }
        printf(" }\n");
    }
    printf("---------------------\n");
}

char* nonterminal_to_string(int nt) {  
    return nonterminal_symbols[nt];
}

void report_syntax_error(const char *message) { 
    fprintf(stderr, "Error: %s near token %s\n", message, yytext);
    release_memory();
    exit(1);
}

void release_memory() { 
    for (int i = 0; i < terminal_count; ++i) {
        if (terminal_symbols[i] != NULL) free(terminal_symbols[i]);
    }
    if (terminal_symbols != NULL) free(terminal_symbols);

    for (int i = 0; i < nonterminal_count; ++i) {
        if (nonterminal_symbols[i] != NULL) free(nonterminal_symbols[i]);
    }
    if (nonterminal_symbols != NULL) free(nonterminal_symbols);

    for (int i = 0; i < rule_count; ++i) {
        for (int j = 0; j < grammar_rules[i].body_length; ++j) {
            if (grammar_rules[i].body[j] != NULL) free(grammar_rules[i].body[j]);
        }
    }
    if (grammar_rules != NULL) free(grammar_rules);

    if (first_sets) {
        for (int i = 0; i < nonterminal_count; i++) {
            for (int j = 0; j < terminal_count; j++) {
                if (first_sets[i][j] != NULL) {
                    free(first_sets[i][j]);
                }
            }
            free(first_sets[i]);
        }
        free(first_sets);
    }

    if (follow_sets) {
        for (int i = 0; i < nonterminal_count; i++) {
            for (int j = 0; j < terminal_count; j++) {
                if (follow_sets[i][j] != NULL) {
                    free(follow_sets[i][j]);
                }
            }
            free(follow_sets[i]);
        }
        free(follow_sets);
    }

    for (int i = 0; i < nonterminal_count; ++i) {
        for (int j = 0; j < terminal_count; ++j) {
            if (predictive_parsing_table[i][j] != NULL) free(predictive_parsing_table[i][j]);
        }
    }

    free_stack();
}

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s near token %s\n", s, yytext);
    release_memory();
    exit(1);
}