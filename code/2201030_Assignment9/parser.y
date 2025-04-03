%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int line_num;
extern FILE *yyin;
extern int yylex();
void yyerror(const char *s);

// Symbol table structure
typedef struct {
    char *name;
    char *type;
    int scope;
} Symbol;

// Symbol table
Symbol symbol_table[1000];
int symbol_count = 0;

// Three-address code generation
int temp_var_count = 0;
int label_count = 0;
char *current_type;

// Stack for handling nested scopes
int scope_stack[100];
int scope_stack_top = 0;
int current_scope = 0;

// Control flow label stacks
typedef struct {
    int start_label;
    int end_label;
} ControlLabels;

ControlLabels control_stack[100];
int control_stack_top = 0;

// Function prototypes
void enter_scope();
void exit_scope();
int add_symbol(char *name, char *type);
int lookup_symbol(char *name);
char* new_temp();
int new_label();
void emit(char *format, ...);
void push_control(int start, int end);
void pop_control();
ControlLabels top_control();
%}

%union {
    int ival;
    float fval;
    char *str;
    struct {
        char *place;     // Variable holding the value
        int true_label;  // Label for true branch (for boolean expressions)
        int false_label; // Label for false branch (for boolean expressions)
        char *code;      // Accumulated code
    } expr;
}

%token <str> ID
%token <ival> INT_CONST
%token <fval> FLOAT_CONST
%token <str> STRING CHAR_CONST
%token INT FLOAT CHAR VOID
%token IF ELSE WHILE FOR RETURN
%token PLUS MINUS MULT DIV MOD
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token INC DEC
%token EQ NEQ GT LT GTE LTE AND OR NOT ADDR
%token LPAREN RPAREN LBRACE RBRACE LSQUARE RSQUARE
%token SEMI COMMA
%token IFX  /* Token for IF without ELSE precedence */

%type <expr> expr assignment_expr logical_expr relational_expr additive_expr
%type <expr> multiplicative_expr unary_expr postfix_expr primary_expr
%type <expr> statement statement_list compound_statement expr_statement
%type <expr> selection_statement iteration_statement
%type <str> type_specifier

%left OR
%left AND
%left EQ NEQ
%left GT LT GTE LTE
%left PLUS MINUS
%left MULT DIV MOD
%right NOT
%right UMINUS
%left INC DEC
%nonassoc IFX  /* Lower precedence than ELSE */
%nonassoc ELSE

%%

program
    : external_declaration
    | program external_declaration
    ;

external_declaration
    : function_definition
    | declaration
    ;

function_definition
    : type_specifier ID LPAREN parameter_list RPAREN 
      { 
        add_symbol($2, $1);
        emit("FUNCTION_BEGIN %s\n", $2);
        enter_scope(); 
      }
      compound_statement 
      { 
        emit("FUNCTION_END %s\n", $2);
        exit_scope(); 
      }
    | type_specifier ID LPAREN RPAREN 
      { 
        add_symbol($2, $1);
        emit("FUNCTION_BEGIN %s\n", $2);
        enter_scope(); 
      }
      compound_statement 
      { 
        emit("FUNCTION_END %s\n", $2);
        exit_scope(); 
      }
    ;

parameter_list
    : parameter_declaration
    | parameter_list COMMA parameter_declaration
    ;

parameter_declaration
    : type_specifier ID {
        add_symbol($2, $1);
        emit("PARAM %s\n", $2);
    }
    ;

declaration
    : type_specifier 
      { 
        current_type = $1; 
      } 
      declaration_list SEMI
    ;

declaration_list
    : declarator
    | declaration_list COMMA declarator
    ;

declarator
    : ID {
        add_symbol($1, current_type);
        emit("DECLARE %s %s\n", current_type, $1);
    }
    | ID ASSIGN expr {
        add_symbol($1, current_type);
        emit("DECLARE %s %s\n", current_type, $1);
        emit("%s = %s\n", $1, $3.place);
    }
    ;

type_specifier
    : INT { $$ = "int"; }
    | FLOAT { $$ = "float"; }
    | CHAR { $$ = "char"; }
    | VOID { $$ = "void"; }
    ;

compound_statement
    : LBRACE { enter_scope(); } statement_list RBRACE {
        exit_scope();
        $$.code = $3.code;
    }
    | LBRACE RBRACE {
        $$.code = strdup(""); /* Return a string value */
    }
    ;

statement_list
    : statement
    | statement_list statement
    ;

statement
    : compound_statement {
        $$.code = $1.code;
    }
    | expr_statement {
        $$.code = $1.code;
    }
    | selection_statement {
        $$.code = $1.code;
    }
    | iteration_statement {
        $$.code = $1.code;
    }
    | declaration {
        $$.code = strdup("");
    }
    | RETURN expr SEMI {
        emit("RETURN %s\n", $2.place);
        $$.code = strdup("");
    }
    | RETURN SEMI {
        emit("RETURN\n");
        $$.code = strdup("");
    }
    ;

expr_statement
    : expr SEMI {
        $$.code = $1.code;
    }
    | SEMI {
        $$.code = strdup("");
    }
    ;

selection_statement
    : IF LPAREN expr RPAREN statement %prec IFX {
        int true_label = new_label();
        int false_label = new_label();
        emit("%s", $3.code);  // Emit condition code
        emit("IF %s GOTO L%d\n", $3.place, true_label);
        emit("GOTO L%d\n", false_label);
        emit("LABEL L%d:\n", true_label);
        emit("%s", $5.code);
        emit("LABEL L%d:\n", false_label);
        $$.code = strdup("");
    }
    | IF LPAREN expr RPAREN statement ELSE statement {
        int true_label = new_label();
        int false_label = new_label();
        int end_label = new_label();
        emit("%s", $3.code);  // Emit condition code
        emit("IF %s GOTO L%d\n", $3.place, true_label);
        emit("GOTO L%d\n", false_label);
        emit("LABEL L%d:\n", true_label);
        emit("%s", $5.code);
        emit("GOTO L%d\n", end_label);
        emit("LABEL L%d:\n", false_label);
        emit("%s", $7.code);
        emit("LABEL L%d:\n", end_label);
        $$.code = strdup("");
    }
    ;

iteration_statement
    : WHILE {
        int start_label = new_label(); 
        emit("LABEL L%d:\n", start_label);
        $<ival>$ = start_label;
    } LPAREN expr RPAREN statement {
        int true_label = new_label();
        int end_label = new_label();
        
        // Emit condition code
        emit("%s", $4.code);
        emit("IF %s GOTO L%d\n", $4.place, true_label);
        emit("GOTO L%d\n", end_label);
        
        emit("LABEL L%d:\n", true_label);
        emit("%s", $6.code);
        emit("GOTO L%d\n", $<ival>1);
        emit("LABEL L%d:\n", end_label);
        $$.code = strdup("");
    }
    | FOR LPAREN expr_statement {
        // Initialize labels
        int cond_label = new_label();
        int body_label = new_label();
        int update_label = new_label();
        int end_label = new_label();
        
        // Execute initialization
        emit("%s", $3.code);
        
        // Jump to condition
        emit("LABEL L%d:\n", cond_label);
        
        // Save labels for later use
        $<ival>$ = cond_label;
        $<ival>1 = body_label;
        $<ival>2 = update_label;
        $<ival>3 = end_label;
    } expr SEMI {
        // If condition is true, go to body, else exit loop
        emit("IF %s GOTO L%d\n", $5.place, $<ival>1);
        emit("GOTO L%d\n", $<ival>3);
        
        // Body label
        emit("LABEL L%d:\n", $<ival>1);
    } expr RPAREN statement {
        // After body, go to update
        emit("GOTO L%d:\n", $<ival>2);
        
        // Update label
        emit("LABEL L%d:\n", $<ival>2);
        emit("%s", $8.code);
        
        // Go back to condition
        emit("GOTO L%d\n", $<ival>4);
        
        // End label
        emit("LABEL L%d:\n", $<ival>3);
        $$.code = strdup("");
    }
    ;

expr
    : assignment_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    ;

assignment_expr
    : logical_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | unary_expr ASSIGN expr {
        $$.place = $1.place;
        emit("%s = %s\n", $1.place, $3.place);
        $$.code = $3.code;
    }
    | unary_expr PLUS_ASSIGN expr {
        $$.place = $1.place;
        char *temp = new_temp();
        emit("%s = %s + %s\n", temp, $1.place, $3.place);
        emit("%s = %s\n", $1.place, temp);
        $$.code = $3.code;
    }
    | unary_expr MINUS_ASSIGN expr {
        $$.place = $1.place;
        char *temp = new_temp();
        emit("%s = %s - %s\n", temp, $1.place, $3.place);
        emit("%s = %s\n", $1.place, temp);
        $$.code = $3.code;
    }
    | unary_expr MULT_ASSIGN expr {
        $$.place = $1.place;
        char *temp = new_temp();
        emit("%s = %s * %s\n", temp, $1.place, $3.place);
        emit("%s = %s\n", $1.place, temp);
        $$.code = $3.code;
    }
    | unary_expr DIV_ASSIGN expr {
        $$.place = $1.place;
        char *temp = new_temp();
        emit("%s = %s / %s\n", temp, $1.place, $3.place);
        emit("%s = %s\n", $1.place, temp);
        $$.code = $3.code;
    }
    | unary_expr MOD_ASSIGN expr {
        $$.place = $1.place;
        char *temp = new_temp();
        emit("%s = %s %% %s\n", temp, $1.place, $3.place);
        emit("%s = %s\n", $1.place, temp);
        $$.code = $3.code;
    }
    ;

logical_expr
    : relational_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | logical_expr AND relational_expr {
        $$.place = new_temp();
        emit("%s = %s && %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | logical_expr OR relational_expr {
        $$.place = new_temp();
        emit("%s = %s || %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    ;

relational_expr
    : additive_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | relational_expr EQ additive_expr {
        $$.place = new_temp();
        emit("%s = %s == %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | relational_expr NEQ additive_expr {
        $$.place = new_temp();
        emit("%s = %s != %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | relational_expr GT additive_expr {
        $$.place = new_temp();
        emit("%s = %s > %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | relational_expr LT additive_expr {
        $$.place = new_temp();
        emit("%s = %s < %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | relational_expr GTE additive_expr {
        $$.place = new_temp();
        emit("%s = %s >= %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | relational_expr LTE additive_expr {
        $$.place = new_temp();
        emit("%s = %s <= %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    ;

additive_expr
    : multiplicative_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | additive_expr PLUS multiplicative_expr {
        $$.place = new_temp();
        emit("%s = %s + %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | additive_expr MINUS multiplicative_expr {
        $$.place = new_temp();
        emit("%s = %s - %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    ;

multiplicative_expr
    : unary_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | multiplicative_expr MULT unary_expr {
        $$.place = new_temp();
        emit("%s = %s * %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | multiplicative_expr DIV unary_expr {
        $$.place = new_temp();
        emit("%s = %s / %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    | multiplicative_expr MOD unary_expr {
        $$.place = new_temp();
        emit("%s = %s %% %s\n", $$.place, $1.place, $3.place);
        $$.code = $1.code;
    }
    ;

unary_expr
    : postfix_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | INC unary_expr {
        $$.place = new_temp();
        emit("%s = %s + 1\n", $$.place, $2.place);
        emit("%s = %s\n", $2.place, $$.place);
        $$.code = $2.code;
    }
    | DEC unary_expr {
        $$.place = new_temp();
        emit("%s = %s - 1\n", $$.place, $2.place);
        emit("%s = %s\n", $2.place, $$.place);
        $$.code = $2.code;
    }
    | MINUS unary_expr %prec UMINUS {
        $$.place = new_temp();
        emit("%s = -%s\n", $$.place, $2.place);
        $$.code = $2.code;
    }
    | NOT unary_expr {
        $$.place = new_temp();
        emit("%s = !%s\n", $$.place, $2.place);
        $$.code = $2.code;
    }
    ;

postfix_expr
    : primary_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | postfix_expr INC {
        $$.place = new_temp();
        emit("%s = %s\n", $$.place, $1.place);
        emit("%s = %s + 1\n", $1.place, $1.place);
        $$.code = $1.code;
    }
    | postfix_expr DEC {
        $$.place = new_temp();
        emit("%s = %s\n", $$.place, $1.place);
        emit("%s = %s - 1\n", $1.place, $1.place);
        $$.code = $1.code;
    }
    | postfix_expr LPAREN argument_list RPAREN {
        $$.place = new_temp();
        emit("%s = call %s\n", $$.place, $1.place);
        $$.code = $1.code;
    }
    | postfix_expr LPAREN RPAREN {
        $$.place = new_temp();
        emit("%s = call %s\n", $$.place, $1.place);
        $$.code = $1.code;
    }
    ;

primary_expr
    : ID {
        int idx = lookup_symbol($1);
        if (idx == -1) {
            yyerror("Undeclared variable");
        }
        $$.place = $1;
        $$.code = strdup("");
    }
    | INT_CONST {
        char temp[20];
        sprintf(temp, "%d", $1);
        $$.place = strdup(temp);
        $$.code = strdup("");
    }
    | FLOAT_CONST {
        char temp[20];
        sprintf(temp, "%f", $1);
        $$.place = strdup(temp);
        $$.code = strdup("");
    }
    | STRING {
        $$.place = $1;
        $$.code = strdup("");
    }
    | CHAR_CONST {
        $$.place = $1;
        $$.code = strdup("");
    }
    | LPAREN expr RPAREN {
        $$.place = $2.place;
        $$.code = $2.code;
    }
    ;

argument_list
    : expr {
        emit("PARAM %s\n", $1.place);
    }
    | argument_list COMMA expr {
        emit("PARAM %s\n", $3.place);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error on line %d: %s\n", line_num, s);
}

void enter_scope() {
    scope_stack[scope_stack_top++] = current_scope;
    current_scope++;
}

void exit_scope() {
    if (scope_stack_top > 0) {
        current_scope = scope_stack[--scope_stack_top];
    }
}

int add_symbol(char *name, char *type) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0 && symbol_table[i].scope == current_scope) {
            return i; // Symbol already exists in current scope
        }
    }
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].type = strdup(type);
    symbol_table[symbol_count].scope = current_scope;
    return symbol_count++;
}

int lookup_symbol(char *name) {
    for (int scope = current_scope; scope >= 0; scope--) {
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i].name, name) == 0 && symbol_table[i].scope <= scope) {
                return i;
            }
        }
    }
    return -1; // Symbol not found
}

char* new_temp() {
    char *temp = (char *)malloc(10);
    sprintf(temp, "t%d", temp_var_count++);
    return temp;
}

int new_label() {
    return label_count++;
}

void emit(char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void push_control(int start, int end) {
    control_stack[control_stack_top].start_label = start;
    control_stack[control_stack_top].end_label = end;
    control_stack_top++;
}

void pop_control() {
    if (control_stack_top > 0) {
        control_stack_top--;
    }
}

ControlLabels top_control() {
    if (control_stack_top > 0) {
        return control_stack[control_stack_top - 1];
    }
    ControlLabels default_labels = {-1, -1};
    return default_labels;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    printf("Three Address Code:\n");
    printf("--------------------\n");
    yyparse();
    return 0;
}