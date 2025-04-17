%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int line_number;
extern FILE *yyin;
extern int yylex();
void yyerror(const char *s);
typedef struct {
    char *name;
    char *type;
    int scope;
} Symbol;
Symbol symbol_table[1000];
int symbol_count = 0;
int temp_variable_count = 0;
int label_count = 0;
char *current_type;
int scope_stack[100];
int scope_stack_top = 0;
int current_scope = 0;
typedef struct {
    int start_label;
    int end_label;
} ControlLabels;

ControlLabels control_stack[100];
int control_stack_top = 0;
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
char* concat_code(char* code1, char* code2);

%}
%union {
    int ival;
    float fval;
    char *str;
    struct {
        char *place;
        int true_label;
        int false_label;
        char *code;
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
%type <expr> expr assignment_expr logical_expr relational_expr additive_expr
%type <expr> multiplicative_expr unary_expr postfix_expr primary_expr
%type <expr> statement statement_list compound_statement expr_statement
%type <expr> selection_statement iteration_statement if_statement if_else_statement
%type <str> type_specifier
%type <expr> argument_list
%right SEMI
%left LPAREN RPAREN
%left OR
%left AND
%left EQ NEQ
%left GT LT GTE LTE
%left PLUS MINUS
%left MULT DIV MOD
%right NOT
%right UMINUS
%left INC DEC
%nonassoc IFX
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
        emit("%s", $7.code);
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
        emit("%s", $6.code);
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
        emit("%s", $3.code);
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
    : statement {
        $$.code = $1.code;
    }
    | statement_list statement {
        $$.code = concat_code($1.code, $2.code);
    }
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
        char* temp = (char*)malloc(100 + strlen($2.code));
        sprintf(temp, "%sRETURN %s\n", $2.code, $2.place);
        $$.code = temp;
    }
    | RETURN SEMI {
        $$.code = strdup("RETURN\n");
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
    : if_statement {
        $$.code = $1.code;
    }
    | if_else_statement {
        $$.code = $1.code;
    }
    ;

if_statement
    : IF LPAREN expr RPAREN statement %prec IFX {
        int true_label = new_label();
        int false_label = new_label();

        char* code = (char*)malloc(1000);
        sprintf(code, "%sIF %s GOTO L%d\nGOTO L%d\nLABEL L%d:\n%sLABEL L%d:\n",
                $3.code, $3.place, true_label, false_label,
                true_label, $5.code, false_label);

        $$.code = code;
    }
    ;

if_else_statement
    : IF LPAREN expr RPAREN statement ELSE statement {
        int true_label = new_label();
        int false_label = new_label();
        int end_label = new_label();

        char* code = (char*)malloc(1000);
        sprintf(code, "%sIF %s GOTO L%d\nGOTO L%d\nLABEL L%d:\n%sGOTO L%d\nLABEL L%d:\n%sLABEL L%d:\n",
                $3.code, $3.place, true_label, false_label,
                true_label, $5.code, end_label,
                false_label, $7.code, end_label);

        $$.code = code;
    }
    ;

iteration_statement
    : WHILE LPAREN expr RPAREN statement {
        int loop_start = new_label();
        int loop_body = new_label();
        int loop_end = new_label();

        char* code = (char*)malloc(2000);
        // Use consistent loop_start label
        sprintf(code, "LABEL L%d:\n%st0 = %s != 0\nIF t0 != 0 GOTO L%d\nGOTO L%d\nLABEL L%d:\n%sGOTO L%d\nLABEL L%d:\n",
                loop_start, $3.code, $3.place, loop_body, loop_end,
                loop_body, $5.code, loop_start, loop_end);

        $$.code = code;
    }
    | FOR LPAREN expr_statement expr SEMI expr RPAREN statement {
        int init_label = new_label();
        int cond_label = new_label();
        int body_label = new_label();
        int update_label = new_label();
        int end_label = new_label();

        char* code = (char*)malloc(2000);
        sprintf(code, "LABEL L%d:\n%sLABEL L%d:\n%st0 = %s != 0\nIF t0 != 0 GOTO L%d\nGOTO L%d\nLABEL L%d:\n%sLABEL L%d:\n%sGOTO L%d\nLABEL L%d:\n",
                init_label, $3.code,
                cond_label, $4.code, $4.place, body_label, end_label,
                body_label, $8.code,
                update_label, $6.code, cond_label,
                end_label);

        $$.code = code;
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
        char* code = concat_code($1.code, $3.code);
        char* assign_code = (char*)malloc(100);
        sprintf(assign_code, "%s = %s\n", $1.place, $3.place);
        $$.code = concat_code(code, assign_code);
        free(code);
        free(assign_code);
    }
    | unary_expr PLUS_ASSIGN expr {
        $$.place = $1.place;
        char* temp = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(200);
        sprintf(op_code, "%s = %s + %s\n%s = %s\n", temp, $1.place, $3.place, $1.place, temp);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | unary_expr MINUS_ASSIGN expr {
        $$.place = $1.place;
        char* temp = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(200);
        sprintf(op_code, "%s = %s - %s\n%s = %s\n", temp, $1.place, $3.place, $1.place, temp);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | unary_expr MULT_ASSIGN expr {
        $$.place = $1.place;
        char* temp = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(200);
        sprintf(op_code, "%s = %s * %s\n%s = %s\n", temp, $1.place, $3.place, $1.place, temp);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | unary_expr DIV_ASSIGN expr {
        $$.place = $1.place;
        char* temp = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(200);
        sprintf(op_code, "%s = %s / %s\n%s = %s\n", temp, $1.place, $3.place, $1.place, temp);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | unary_expr MOD_ASSIGN expr {
        $$.place = $1.place;
        char* temp = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(200);
        sprintf(op_code, "%s = %s %% %s\n%s = %s\n", temp, $1.place, $3.place, $1.place, temp);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    ;

logical_expr
    : relational_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | logical_expr AND relational_expr {
        $$.place = new_temp();
        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s && %s\n", $$.place, $1.place, $3.place);
        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | logical_expr OR relational_expr {
        $$.place = new_temp();
        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s || %s\n", $$.place, $1.place, $3.place);
        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    ;

relational_expr
    : additive_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | relational_expr EQ additive_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s == %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | relational_expr NEQ additive_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s != %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | relational_expr GT additive_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s > %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | relational_expr LT additive_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s < %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | relational_expr GTE additive_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s >= %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | relational_expr LTE additive_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s <= %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    ;

additive_expr
    : multiplicative_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | additive_expr PLUS multiplicative_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s + %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | additive_expr MINUS multiplicative_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s - %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    ;

multiplicative_expr
    : unary_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | multiplicative_expr MULT unary_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s * %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | multiplicative_expr DIV unary_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s / %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    | multiplicative_expr MOD unary_expr {
        $$.place = new_temp();

        char* code = concat_code($1.code, $3.code);
        char* op_code = (char*)malloc(100);
        sprintf(op_code, "%s = %s %% %s\n", $$.place, $1.place, $3.place);

        $$.code = concat_code(code, op_code);
        free(code);
        free(op_code);
    }
    ;

unary_expr
    : postfix_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | INC unary_expr {
        $$.place = new_temp();
        char* code = (char*)malloc(200 + strlen($2.code));
        sprintf(code, "%s%s = %s + 1\n%s = %s\n",
                $2.code, $$.place, $2.place, $2.place, $$.place);
        $$.code = code;
    }
    | DEC unary_expr {
        $$.place = new_temp();
        char* code = (char*)malloc(200 + strlen($2.code));
        sprintf(code, "%s%s = %s - 1\n%s = %s\n",
                $2.code, $$.place, $2.place, $2.place, $$.place);
        $$.code = code;
    }
    | MINUS unary_expr %prec UMINUS {
        $$.place = new_temp();
        char* code = (char*)malloc(100 + strlen($2.code));
        sprintf(code, "%s%s = -%s\n", $2.code, $$.place, $2.place);
        $$.code = code;
    }
    | NOT unary_expr {
        $$.place = new_temp();
        char* code = (char*)malloc(100 + strlen($2.code));
        sprintf(code, "%s%s = !%s\n", $2.code, $$.place, $2.place);
        $$.code = code;
    }
    ;

postfix_expr
    : primary_expr {
        $$.place = $1.place;
        $$.code = $1.code;
    }
    | postfix_expr INC {
        $$.place = new_temp();
        char* code = (char*)malloc(200 + strlen($1.code));
        sprintf(code, "%s%s = %s\n%s = %s + 1\n",
                $1.code, $$.place, $1.place, $1.place, $1.place);
        $$.code = code;
    }
    | postfix_expr DEC {
        $$.place = new_temp();
        char* code = (char*)malloc(200 + strlen($1.code));
        sprintf(code, "%s%s = %s\n%s = %s - 1\n",
                $1.code, $$.place, $1.place, $1.place, $1.place);
        $$.code = code;
    }
    | postfix_expr LPAREN argument_list RPAREN {
        $$.place = new_temp();
        // For function calls, include argument list code first
        char* call_code = (char*)malloc(100 + strlen($1.code) + strlen($3.code));
        sprintf(call_code, "%s%s%s = call %s\n",
                $1.code, $3.code, $$.place, $1.place);
        $$.code = call_code;
    }
    | postfix_expr LPAREN RPAREN {
        $$.place = new_temp();
        char* call_code = (char*)malloc(100 + strlen($1.code));
        sprintf(call_code, "%s%s = call %s\n", $1.code, $$.place, $1.place);
        $$.code = call_code;
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
        char* code = (char*)malloc(strlen($1.code) + 100);
        sprintf(code, "%sPARAM %s\n", $1.code, $1.place);
        $$.code = code;
    }
    | argument_list COMMA expr {
        char* code1 = $1.code;
        char* code2 = (char*)malloc(strlen($3.code) + 100);
        sprintf(code2, "%sPARAM %s\n", $3.code, $3.place);
        $$.code = concat_code(code1, code2);
        free(code2);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error on line %d: %s\n", line_number, s);
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
    sprintf(temp, "t%d", temp_variable_count++);
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

// Helper function to concatenate two code strings
char* concat_code(char* code1, char* code2) {
    if (code1 == NULL) return strdup(code2 ? code2 : "");
    if (code2 == NULL) return strdup(code1);

    char* result = (char*)malloc(strlen(code1) + strlen(code2) + 1);
    strcpy(result, code1);
    strcat(result, code2);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "ERROR! Could not open file %s\n", argv[1]);
            return 1;
        }
        yyin = fp;
    }
    printf("Generated Three Address Code:\n");
    printf("--------------------\n");
    yyparse();
    return 0;
}
