%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
void yyerror(char *);
int yylex(void);
extern int yylineno; // Make line number accessible
extern char *yytext; // Make matched text accessible

// --- Symbol Table ---
struct symbol {
    char *name;
    char *type; // "var", "func", "param"
    int scope;
};
struct symbol symbol_table[100];
int symbol_count = 0;
// Simple lookup
int lookup_symbol(char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Not found
}
// Add symbol with basic check
void add_symbol(char *name, char *type) {
    if (symbol_count >= 100) {
        fprintf(stderr, "Error: Symbol table overflow\n");
        exit(1);
    }
    symbol_table[symbol_count].name = strdup(name);
    if (!symbol_table[symbol_count].name) { yyerror("strdup failed for symbol name"); exit(1); }
    symbol_table[symbol_count].type = strdup(type);
    if (!symbol_table[symbol_count].type) { yyerror("strdup failed for symbol type"); exit(1); }
    symbol_count++;
}


// --- Three Address Code ---
typedef struct {
    char *op;
    char *arg1;
    char *arg2;
    char *result;
} quad;
quad code[1000];
int next_quad = 0;
int temp_count = 0;


// --- Backpatching Lists ---
struct list {
    int quad_index;
    struct list *next;
};

// --- Attribute Structure ---
typedef struct attr {
    char *place;
    struct list *true_list;
    struct list *false_list;
    struct list *next_list;
    int quad;
} attr;

// --- Utility Functions ---
void emit(char *op, char *arg1, char *arg2, char *result);
char* new_temp(void);
char* int_to_string(int);
struct list* make_list(int);
struct list* merge(struct list*, struct list*);
void backpatch(struct list*, int);
void print_three_address_code(); // Declaration
void ensure_boolean_lists(attr* expr_attr); // Declaration for helper


// Helper to create attribute, reduces malloc/init repetition
attr* create_attr() {
    attr* new_attr = (attr*)malloc(sizeof(attr));
    if (!new_attr) { yyerror("Memory allocation failed for attribute"); exit(1); }
    new_attr->place = NULL;
    new_attr->true_list = NULL;
    new_attr->false_list = NULL;
    new_attr->next_list = NULL;
    new_attr->quad = next_quad; // Default quad value
    return new_attr;
}


%}

// --- YACC Declarations ---
%union {
    int num;
    float fnum;
    char *id;
    struct attr *attr;
}

%token IF ELSE WHILE INT FLOAT VOID RETURN
%token EQ NE LE GE LT GT AND OR
%token <num> NUMBER
%token <fnum> FLOAT_NUM
%token <id> ID

%type <attr> program declaration_list declaration var_decl func_decl
%type <attr> type_specifier params param_list param compound_stmt
%type <attr> local_declarations local_declaration
%type <attr> stmt_list stmt expr_stmt if_stmt while_stmt return_stmt
%type <attr> expr assign_expr log_or_expr log_and_expr rel_expr add_expr mult_expr
%type <attr> factor primary var call args arg_list M N

%start program

%%

// --- Grammar Rules ---

program : declaration_list
    { /* End of program */ }
    ;

declaration_list : declaration_list declaration { /* Chain */ }
                 | /* empty */
                 ;

declaration : var_decl | func_decl ;

var_decl : type_specifier ID ';'
    {
        add_symbol($2, "var");
        free($2); // Free ID from lexer
        $$ = NULL; // No attribute needed here
    }
    ;

type_specifier : INT   { }
               | FLOAT { }
               | VOID  { }
               ;

func_decl : type_specifier ID '(' params ')'
    {
        if (!$2) { yyerror("Internal error: NULL ID in func_decl"); exit(1); }
        add_symbol($2, "func");
        emit("func_begin", $2, NULL, NULL); // Emit label BEFORE compound_stmt
    }
    compound_stmt
    {
        if (!$2 || !$7) { yyerror("Internal error: NULL attr in func_decl"); exit(1); }
         
        if ($7 && $7->next_list) {
            backpatch($7->next_list, next_quad); // Patch exits from body
        }

        emit("func_end", $2, NULL, NULL); // Emit label at end
        free($2); // Free ID
        if ($7) free($7); // Free compound_stmt attribute
        $$ = NULL;
    }
    ;


params : param_list { }
       | VOID       { }
       | /* empty */ { }
       ;

param_list : param_list ',' param { }
           | param
           ;

param : type_specifier ID
    {
        add_symbol($2, "param");
        free($2); // Free ID
    }
    ;

compound_stmt : '{' local_declarations stmt_list '}'
    {
        $$ = $3; // Pass stmt_list attribute up
    }
    ;

local_declarations : local_declarations local_declaration { }
                  | /* empty */
                  ;

local_declaration : var_decl { } ;

stmt_list : stmt_list M stmt
    {
        if (!$1 || !$2 || !$3) { yyerror("Internal error: NULL attr in stmt_list"); exit(1); }
        backpatch($1->next_list, $2->quad);
        $$ = create_attr();
        $$->next_list = $3->next_list;
        $$->quad = $1->quad;
        free($2); // M always allocated
    }
    | /* empty */
    {
        $$ = create_attr(); // Base case
    }
    ;

M : /* empty */ { $$ = create_attr(); $$->quad = next_quad; } ;

N : /* empty */
    {
        $$ = create_attr();
        emit("goto", NULL, NULL, "0");
        $$->next_list = make_list(next_quad - 1);
    }
    ;

stmt : expr_stmt      { $$ = $1; }
     | compound_stmt  { $$ = $1; }
     | if_stmt        { $$ = $1; }
     | while_stmt     { $$ = $1; }
     | return_stmt    { $$ = $1; }
     | local_declaration { $$ = create_attr(); } // Add handling for local declarations as statements
     ;

expr_stmt : expr ';'
    {
        $$ = create_attr();
    }
    | ';' { $$ = create_attr(); }
    ;

if_stmt : IF '(' expr ')' M stmt N ELSE M stmt  // IF-ELSE
    {
        if (!$3 || !$5 || !$6 || !$7 || !$9 || !$10) { yyerror("Internal error: NULL attr in if-else"); exit(1); }

        // Ensure expr ($3) has boolean lists
        ensure_boolean_lists($3);

        backpatch($3->true_list, $5->quad);
        backpatch($3->false_list, $9->quad);
        $$ = create_attr();
        struct list *if_exits = ($6 && $6->next_list) ? $6->next_list : NULL;
        struct list *else_exits = ($10 && $10->next_list) ? $10->next_list : NULL;
        $$->next_list = merge(if_exits, $7->next_list);
        $$->next_list = merge($$->next_list, else_exits);
        $$->quad = $3->quad;
    }
    | IF '(' expr ')' M stmt  // IF without ELSE
    {
        if (!$3 || !$5 || !$6) { yyerror("Internal error: NULL attr in if"); exit(1); }

        // Ensure expr ($3) has boolean lists
        ensure_boolean_lists($3);

        backpatch($3->true_list, $5->quad);
        $$ = create_attr();
        struct list *if_exits = ($6 && $6->next_list) ? $6->next_list : NULL;
        $$->next_list = merge($3->false_list, if_exits);
        $$->quad = $3->quad;
    }
    ;


while_stmt : WHILE M '(' expr ')' M stmt
    {
        if (!$2 || !$4 || !$6 || !$7) { yyerror("Internal error: NULL attr in while"); exit(1); }

        // Ensure expr ($4) has boolean lists
        ensure_boolean_lists($4);

        backpatch($4->true_list, $6->quad); // True jumps to body start (M2)
        if ($7 && $7->next_list) {
             backpatch($7->next_list, $2->quad); // Body exits jump to loop start (M1)
        }
        // Create string for target quad index *before* passing to emit
        char *loop_start_target = int_to_string($2->quad);
        emit("goto", NULL, NULL, loop_start_target); // loop back unconditionally
        free(loop_start_target); // Free the string created by int_to_string

        $$ = create_attr();
        $$->next_list = $4->false_list; // Exiting the loop follows the condition's false list
        $$->quad = $2->quad;
    }
    ;


return_stmt : RETURN expr ';'
    {
        if (!$2 || !$2->place) { yyerror("Internal error: NULL attr/place in return expr"); exit(1); }
        emit("return", $2->place, NULL, NULL);
        $$ = create_attr();
    }
    | RETURN ';'
    {
        emit("return", NULL, NULL, NULL);
        $$ = create_attr();
    }
    ;

expr : assign_expr { $$ = $1; } ;

assign_expr : var '=' expr
    {
        if (!$1 || !$3 || !$1->place || !$3->place) { yyerror("Internal error: NULL attr/place in assign"); exit(1); }
        emit("=", $3->place, NULL, $1->place);
        $$ = $1; // Pass var attribute up
        $$->true_list = $$->false_list = $$->next_list = NULL; // Clear lists
    }
    | log_or_expr { $$ = $1; }
    ;

log_or_expr : log_or_expr OR M log_and_expr
    {
        if (!$1 || !$3 || !$4 || !$1->place || !$4->place) { yyerror("Internal error: NULL attr/place in OR"); exit(1); }
        backpatch($1->false_list, $3->quad);
        $$ = create_attr();
        $$->place = new_temp();
        emit("||", $1->place, $4->place, $$->place);
        $$->true_list = merge($1->true_list, $4->true_list);
        $$->false_list = $4->false_list;
        $$->quad = $1->quad;
    }
    | log_and_expr { $$ = $1; }
    ;

log_and_expr : log_and_expr AND M rel_expr
    {
        if (!$1 || !$3 || !$4 || !$1->place || !$4->place) { yyerror("Internal error: NULL attr/place in AND"); exit(1); }
        backpatch($1->true_list, $3->quad);
        $$ = create_attr();
        $$->place = new_temp();
        emit("&&", $1->place, $4->place, $$->place);
        $$->true_list = $4->true_list;
        $$->false_list = merge($1->false_list, $4->false_list);
        $$->quad = $1->quad;
    }
    | rel_expr { $$ = $1; }
    ;

// Updated Relational Expressions rule for better 3-address code generation
rel_expr : add_expr EQ add_expr 
    { 
        if(!$1||!$3||!$1->place||!$3->place){yyerror("Null attr/place"); exit(1);} 
        $$ = create_attr(); 
        $$->place = new_temp(); 
        // Generate direct conditional jump
        emit("==", $1->place, $3->place, $$->place);
        emit("if==", $1->place, $3->place, "0"); 
        $$->true_list = make_list(next_quad-1); 
        emit("goto", NULL, NULL, "0"); 
        $$->false_list = make_list(next_quad-1);
        $$->quad = $1->quad;
    }
    | add_expr NE add_expr 
    { 
        if(!$1||!$3||!$1->place||!$3->place){yyerror("Null attr/place"); exit(1);} 
        $$ = create_attr(); 
        $$->place = new_temp(); 
        emit("!=", $1->place, $3->place, $$->place);
        emit("if!=", $1->place, $3->place, "0"); 
        $$->true_list = make_list(next_quad-1); 
        emit("goto", NULL, NULL, "0"); 
        $$->false_list = make_list(next_quad-1);
        $$->quad = $1->quad;
    }
    | add_expr LT add_expr 
    { 
        if(!$1||!$3||!$1->place||!$3->place){yyerror("Null attr/place"); exit(1);} 
        $$ = create_attr(); 
        $$->place = new_temp(); 
        emit("<", $1->place, $3->place, $$->place);
        emit("if<", $1->place, $3->place, "0"); 
        $$->true_list = make_list(next_quad-1); 
        emit("goto", NULL, NULL, "0"); 
        $$->false_list = make_list(next_quad-1);
        $$->quad = $1->quad;
    }
    | add_expr GT add_expr 
    { 
        if(!$1||!$3||!$1->place||!$3->place){yyerror("Null attr/place"); exit(1);} 
        $$ = create_attr(); 
        $$->place = new_temp(); 
        emit(">", $1->place, $3->place, $$->place);
        emit("if>", $1->place, $3->place, "0"); 
        $$->true_list = make_list(next_quad-1); 
        emit("goto", NULL, NULL, "0"); 
        $$->false_list = make_list(next_quad-1);
        $$->quad = $1->quad;
    }
    | add_expr LE add_expr 
    { 
        if(!$1||!$3||!$1->place||!$3->place){yyerror("Null attr/place"); exit(1);} 
        $$ = create_attr(); 
        $$->place = new_temp(); 
        emit("<=", $1->place, $3->place, $$->place);
        emit("if<=", $1->place, $3->place, "0"); 
        $$->true_list = make_list(next_quad-1); 
        emit("goto", NULL, NULL, "0"); 
        $$->false_list = make_list(next_quad-1);
        $$->quad = $1->quad;
    }
    | add_expr GE add_expr 
    { 
        if(!$1||!$3||!$1->place||!$3->place){yyerror("Null attr/place"); exit(1);} 
        $$ = create_attr(); 
        $$->place = new_temp(); 
        emit(">=", $1->place, $3->place, $$->place);
        emit("if>=", $1->place, $3->place, "0"); 
        $$->true_list = make_list(next_quad-1); 
        emit("goto", NULL, NULL, "0"); 
        $$->false_list = make_list(next_quad-1);
        $$->quad = $1->quad;
    }
    | add_expr
    {
        $$ = $1;
        if ($$) {
            $$->true_list = NULL;
            $$->false_list = NULL;
        } else {
            $$ = create_attr();
        }
    }
    ;

// Arithmetic expressions
add_expr : add_expr '+' mult_expr
    {
        if (!$1 || !$3 || !$1->place || !$3->place) { yyerror("Internal error: NULL attr/place in '+'"); exit(1); }
        $$ = create_attr();
        $$->place = new_temp();
        emit("+", $1->place, $3->place, $$->place);
        $$->quad = $1->quad;
    }
    | add_expr '-' mult_expr
    {
        if (!$1 || !$3 || !$1->place || !$3->place) { yyerror("Internal error: NULL attr/place in '-'"); exit(1); }
        $$ = create_attr();
        $$->place = new_temp();
        emit("-", $1->place, $3->place, $$->place);
        $$->quad = $1->quad;
    }
    | mult_expr { $$ = $1; }
    ;

mult_expr : mult_expr '*' factor
    {
        if (!$1 || !$3 || !$1->place || !$3->place) { yyerror("Internal error: NULL attr/place in '*'"); exit(1); }
        $$ = create_attr();
        $$->place = new_temp();
        emit("*", $1->place, $3->place, $$->place);
        $$->quad = $1->quad;
    }
    | mult_expr '/' factor
    {
        if (!$1 || !$3 || !$1->place || !$3->place) { yyerror("Internal error: NULL attr/place in '/'"); exit(1); }
        $$ = create_attr();
        $$->place = new_temp();
        emit("/", $1->place, $3->place, $$->place);
        $$->quad = $1->quad;
    }
     | mult_expr '%' factor
    {
        if (!$1 || !$3 || !$1->place || !$3->place) { yyerror("Internal error: NULL attr/place in '%'"); exit(1); }
        $$ = create_attr();
        $$->place = new_temp();
        emit("%", $1->place, $3->place, $$->place);
         $$->quad = $1->quad;
    }
    | factor { $$ = $1; }
    ;

factor : primary { $$ = $1; } ;

primary : '(' expr ')' { $$ = $2; }
    | var { $$ = $1; }
    | call { $$ = $1; }
    | NUMBER { $$ = create_attr(); $$->place = int_to_string($1); }
    | FLOAT_NUM
    {
        $$ = create_attr();
        char fnum_str[50];
        sprintf(fnum_str, "%f", $1);
        $$->place = strdup(fnum_str);
        if (!$$->place) { yyerror("strdup failed for float"); exit(1); }
    }
    ;

var : ID
    {
        $$ = create_attr();
        $$->place = strdup($1);
        if (!$$->place) { yyerror("strdup failed for var ID"); exit(1); }
        free($1); // Free original lexer string
    }
    ;

call : ID '(' args ')'
    {
        if (!$1) { yyerror("Internal error: NULL function ID"); exit(1); }
        $$ = create_attr();
        $$->place = new_temp();
        emit("call", $1, NULL, $$->place);
        $$->quad = next_quad - 1;
        free($1);
    }
    ;

args : arg_list { }
     | /* empty */ { }
     ;

arg_list : arg_list ',' expr
    {
        if (!$3 || !$3->place) { yyerror("Internal error: NULL attr/place in arg list"); exit(1); }
        emit("param", $3->place, NULL, NULL);
    }
    | expr
    {
        if (!$1 || !$1->place) { yyerror("Internal error: NULL attr/place in arg list base"); exit(1); }
        emit("param", $1->place, NULL, NULL);
    }
    ;

%%

// --- C Code Section ---

void emit(char *op, char *arg1, char *arg2, char *result) {
    if (next_quad >= 1000) { fprintf(stderr, "Error: Code array overflow\n"); exit(1); }
    char* op_copy = op ? strdup(op) : NULL;
    char* arg1_copy = arg1 ? strdup(arg1) : NULL;
    char* arg2_copy = arg2 ? strdup(arg2) : NULL;
    char* result_copy = result ? strdup(result) : NULL;
    if ((op && !op_copy) || (arg1 && !arg1_copy) || (arg2 && !arg2_copy) || (result && !result_copy)) {
        yyerror("strdup failed in emit"); free(op_copy); free(arg1_copy); free(arg2_copy); free(result_copy); exit(1);
    }
    code[next_quad].op = op_copy; code[next_quad].arg1 = arg1_copy; code[next_quad].arg2 = arg2_copy; code[next_quad].result = result_copy;
    next_quad++;
}

char* new_temp(void) {
    char temp[20]; sprintf(temp, "t%d", temp_count++); char* temp_copy = strdup(temp);
    if (!temp_copy) { yyerror("strdup failed for new_temp"); exit(1); } return temp_copy;
}

char* int_to_string(int value) {
    char temp[20]; sprintf(temp, "%d", value); char* value_copy = strdup(temp);
    if (!value_copy) { yyerror("strdup failed for int_to_string"); exit(1); } return value_copy;
}

struct list* make_list(int quad_index) {
    struct list *l = (struct list*)malloc(sizeof(struct list)); if (!l) { yyerror("malloc failed in make_list"); exit(1); }
    l->quad_index = quad_index; l->next = NULL; return l;
}

struct list* merge(struct list *l1, struct list *l2) {
    if (!l1) return l2; if (!l2) return l1; struct list *temp = l1; while (temp->next) temp = temp->next;
    temp->next = l2; return l1;
}

// Helper function to generate boolean jumps if an attribute lacks them
void ensure_boolean_lists(attr* expr_attr) {
    if (!expr_attr) { yyerror("Internal error: NULL expression attribute"); exit(1); }
    if (expr_attr->true_list == NULL && expr_attr->false_list == NULL) {
        if (!expr_attr->place) {
             yyerror("Internal error: Expression used as condition has no 'place'");
             expr_attr->place = strdup("error_placeholder"); // Prevent crash, indicates prior error
             if (!expr_attr->place) exit(1); // Failed even to allocate placeholder
        }
        char *zero_str = strdup("0"); // Need an allocated "0" for emit
        if (!zero_str) { yyerror("strdup failed for '0'"); exit(1); }
        expr_attr->true_list = make_list(next_quad);
        emit("if!=", expr_attr->place, zero_str, "0"); // Compare with "0"
        expr_attr->false_list = make_list(next_quad);
        emit("goto", NULL, NULL, "0");
        free(zero_str); // Free the allocated "0" string
    } else if (expr_attr->true_list == NULL || expr_attr->false_list == NULL) {
        yyerror("Internal error: Inconsistent boolean lists in expression"); exit(1);
    }
}

// Backpatching function
void backpatch(struct list *l, int target_quad) {
    if (!l) return;
    char *target_str = int_to_string(target_quad);
    struct list *current = l;
    struct list *next_node = NULL;
    while (current) {
        int quad_idx = current->quad_index;
        if (quad_idx >= 0 && quad_idx < next_quad) {
            char* old_result = code[quad_idx].result;
            code[quad_idx].result = strdup(target_str);
            if (!code[quad_idx].result) { yyerror("strdup failed in backpatch"); exit(1); }
            if (old_result) { free(old_result); }
        } else { fprintf(stderr, "Warning: Invalid quad index %d encountered during backpatching.\n", quad_idx); }
        next_node = current->next;
        free(current);
        current = next_node;
    }
    free(target_str);
}

void yyerror(char *s) {
    fprintf(stderr, "\nSyntax error: %s at line %d near '%s'\n", s, yylineno, yytext); exit(1);
}

// Updated print_three_address_code function for better output formatting
void print_three_address_code() {
    printf("\n----- THREE ADDRESS CODE -----\n");
    for (int i = 0; i < next_quad; i++) {
        printf("L%d:\t", i);
        if (!code[i].op) { printf("(empty)\n"); continue; }
        
        if (strcmp(code[i].op, "=") == 0) { 
            printf("%s = %s\n", code[i].result ? code[i].result : "?", code[i].arg1 ? code[i].arg1 : "?"); 
        }
        else if (strncmp(code[i].op, "if", 2) == 0) {
            // Format conditional jumps cleanly by removing the "if" prefix
            printf("if %s %s %s goto L%s\n", 
                  code[i].arg1 ? code[i].arg1 : "?", 
                  &code[i].op[2], // Skip the "if" prefix to get just the operator
                  code[i].arg2 ? code[i].arg2 : "?", 
                  code[i].result ? code[i].result : "?");
        }
        else if (strcmp(code[i].op, "goto") == 0) { 
            printf("goto L%s\n", code[i].result ? code[i].result : "?"); 
        }
        else if (strcmp(code[i].op, "param") == 0) { 
            printf("param %s\n", code[i].arg1 ? code[i].arg1 : "?"); 
        }
        else if (strcmp(code[i].op, "call") == 0) { 
            printf("%s = call %s\n", code[i].result ? code[i].result : "?", code[i].arg1 ? code[i].arg1 : "?"); 
        }
        else if (strcmp(code[i].op, "return") == 0) { 
            if (code[i].arg1) 
                printf("return %s\n", code[i].arg1); 
            else 
                printf("return\n"); 
        }
        else if (strcmp(code[i].op, "func_begin") == 0 || strcmp(code[i].op, "func_end") == 0) { 
            printf("%s %s\n", code[i].op, code[i].arg1 ? code[i].arg1 : "?"); 
        }
        else if (code[i].arg2) { 
            // Binary operations (e.g., a + b)
            printf("%s = %s %s %s\n", 
                   code[i].result ? code[i].result : "?", 
                   code[i].arg1 ? code[i].arg1 : "?", 
                   code[i].op, 
                   code[i].arg2 ? code[i].arg2 : "?"); 
        }
        else if (code[i].arg1) { 
            // Unary operations
            printf("%s = %s %s\n", 
                   code[i].result ? code[i].result : "?", 
                   code[i].op, 
                   code[i].arg1 ? code[i].arg1 : "?"); 
        }
        else { 
            printf("%s\n", code[i].op); 
        }
    }
    printf("---------------------------\n");
}

// main function
int main() {
    if (yyparse() == 0) { 
        print_three_address_code(); 
    } else { 
        printf("Parsing failed.\n"); 
    }
    
    // Clean up all allocated memory
    for(int i=0; i< symbol_count; ++i) { 
        if (symbol_table[i].name) free(symbol_table[i].name); 
        if (symbol_table[i].type) free(symbol_table[i].type); 
        symbol_table[i].name = NULL; 
        symbol_table[i].type = NULL; 
    }
    
    for (int i = 0; i < next_quad; i++) { 
        if(code[i].op) free(code[i].op); 
        if(code[i].arg1) free(code[i].arg1); 
        if(code[i].arg2) free(code[i].arg2); 
        if(code[i].result) free(code[i].result); 
        code[i].op = code[i].arg1 = code[i].arg2 = code[i].result = NULL; 
    }
    
    return 0;
}