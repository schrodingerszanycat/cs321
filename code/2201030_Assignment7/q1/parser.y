%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ValueType {
    VALUE_TYPE_INTEGER,
    VALUE_TYPE_OPERATION
};

enum Operator {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};

typedef struct ExprNode {
    enum ValueType type;
    union {
        int value;          
        struct {            
            enum Operator op;
            struct ExprNode* left;
            struct ExprNode* right;
        } operation;
    } data;
} ExprNode;

ExprNode* createInteger(int value);
ExprNode* createOperation(enum Operator op, ExprNode* left, ExprNode* right);
void printParseStep(char* rule, void* value);
void printAST(ExprNode* node, int indent);
void cleanupAST(ExprNode* node);

int yylex(void);
int yyerror(char* s);
%}

%token INTEGER ADD SUBTRACT MULTIPLY DIVIDE OPEN_PAREN CLOSE_PAREN

%union {
    int value;
    struct ExprNode* node;
}

%type <value> INTEGER
%type <node> expression term factor

%%

program  : expression       { 
                              printf("\n Abstract Syntax Tree Visualization:-\n");
                              printAST($1, 0);
                              cleanupAST($1);
                            }
        ;

expression : expression ADD term    { 
                              printParseStep("expression -> expression + term", NULL);
                              $$ = createOperation(ADDITION, $1, $3);
                            }
        | expression SUBTRACT term   { 
                              printParseStep("expression -> expression - term", NULL);
                              $$ = createOperation(SUBTRACTION, $1, $3);
                            }
        | term              { 
                              printParseStep("expression -> term", NULL);
                              $$ = $1;
                            }
        ;

term    : term MULTIPLY factor { 
                              printParseStep("term -> term * factor", NULL);
                              $$ = createOperation(MULTIPLICATION, $1, $3);
                            }
        | term DIVIDE factor { 
                              printParseStep("term -> term / factor", NULL);
                              $$ = createOperation(DIVISION, $1, $3);
                            }
        | factor            { 
                              printParseStep("term -> factor", NULL);
                              $$ = $1;
                            }
        ;

factor  : INTEGER           { 
                              printParseStep("factor -> INTEGER", &$1);
                              $$ = createInteger($1);
                            }
        | OPEN_PAREN expression CLOSE_PAREN { 
                              printParseStep("factor -> ( expression )", NULL);
                              $$ = $2;
                            }
        ;

%%

ExprNode* createInteger(int value) {
    ExprNode* node = (ExprNode*)malloc(sizeof(ExprNode));
    node->type = VALUE_TYPE_INTEGER;
    node->data.value = value;
    return node;
}

ExprNode* createOperation(enum Operator op, ExprNode* left, ExprNode* right) {
    ExprNode* node = (ExprNode*)malloc(sizeof(ExprNode));
    node->type = VALUE_TYPE_OPERATION;
    node->data.operation.op = op;
    node->data.operation.left = left;
    node->data.operation.right = right;
    return node;
}

void printParseStep(char* rule, void* value) {
    static int depth = 0;
    static int initialized = 0;
    
    if (!initialized) {
        printf("Concrete Parse Tree Construction:-\n");
        initialized = 1;
    }
    
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    printf("%s", rule);
    
    if (strstr(rule, "INTEGER") && value) {
        printf(" (value: %d)", *(int*)value);
    }
    
    printf("\n");
    depth++;
}

void printAST(ExprNode* node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    
    if (node->type == VALUE_TYPE_INTEGER) {
        printf("VALUE: %d\n", node->data.value);
    } else if (node->type == VALUE_TYPE_OPERATION) {
        char symbol;
        switch (node->data.operation.op) {
            case ADDITION: symbol = '+'; break;
            case SUBTRACTION: symbol = '-'; break;
            case MULTIPLICATION: symbol = '*'; break;
            case DIVISION: symbol = '/'; break;
        }
        printf("OPERATION: %c\n", symbol);
        printAST(node->data.operation.left, indent + 1);
        printAST(node->data.operation.right, indent + 1);
    }
}

void cleanupAST(ExprNode* node) {
    if (!node) return;
    
    if (node->type == VALUE_TYPE_OPERATION) {
        cleanupAST(node->data.operation.left);
        cleanupAST(node->data.operation.right);
    }
    
    free(node);
}

int yyerror(char* s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int main() {
    printf("Enter an arithmetic expression (examples: 5+3*2, (4+2)*3, 8/2-1):\n");
    yyparse();
    return 0;
}
