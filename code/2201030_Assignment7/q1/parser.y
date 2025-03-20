%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_CONSTANT,
    NODE_IDENTIFIER,
    NODE_OPERATOR,
    NODE_IF,
    NODE_ASSIGN,
    NODE_SEQUENCE
} NodeType;

/* Abstract Syntax Tree node structure */
typedef struct ASTNode {
    NodeType type;
    union {
        int value;              /* For constants */
        char *name;             /* For identifiers */
        struct {
            char op;            /* For operators: +, -, *, / */
            struct ASTNode *left;
            struct ASTNode *right;
        } op;
        struct {
            struct ASTNode *condition;
            struct ASTNode *thenBranch;
            struct ASTNode *elseBranch;
        } ifStmt;
        struct {
            char *id;
            struct ASTNode *expr;
        } assign;
        struct {
            struct ASTNode *first;
            struct ASTNode *second;
        } seq;
    } data;
} ASTNode;

ASTNode* createConstantNode(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_CONSTANT;
    node->data.value = value;
    return node;
}

ASTNode* createIdentifierNode(char *name) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->data.name = strdup(name);
    return node;
}

ASTNode* createOperatorNode(char op, ASTNode *left, ASTNode *right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_OPERATOR;
    node->data.op.op = op;
    node->data.op.left = left;
    node->data.op.right = right;
    return node;
}

/* Function to create an if-statement node in our AST */
ASTNode* createIfNode(ASTNode *condition, ASTNode *thenBranch, ASTNode *elseBranch) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->data.ifStmt.condition = condition;
    node->data.ifStmt.thenBranch = thenBranch;
    node->data.ifStmt.elseBranch = elseBranch;
    return node;
}

ASTNode* createAssignNode(char *id, ASTNode *expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.id = strdup(id);
    node->data.assign.expr = expr;
    return node;
}

ASTNode* createSequenceNode(ASTNode *first, ASTNode *second) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_SEQUENCE;
    node->data.seq.first = first;
    node->data.seq.second = second;
    return node;
}

void printAST(ASTNode *node, int indent) {
    if (node == NULL) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    
    switch (node->type) {
        case NODE_CONSTANT:
            printf("CONSTANT: %d\n", node->data.value);
            break;
        case NODE_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->data.name);
            break;
        case NODE_OPERATOR:
            printf("OPERATOR: %c\n", node->data.op.op);
            printAST(node->data.op.left, indent + 1);
            printAST(node->data.op.right, indent + 1);
            break;
        case NODE_IF:
            printf("IF\n");
            for (int i = 0; i < indent; i++) printf("  ");
            printf("CONDITION:\n");
            printAST(node->data.ifStmt.condition, indent + 1);
            for (int i = 0; i < indent; i++) printf("  ");
            printf("THEN:\n");
            printAST(node->data.ifStmt.thenBranch, indent + 1);
            if (node->data.ifStmt.elseBranch) {
                for (int i = 0; i < indent; i++) printf("  ");
                printf("ELSE:\n");
                printAST(node->data.ifStmt.elseBranch, indent + 1);
            }
            break;
        case NODE_ASSIGN:
            printf("ASSIGN: %s\n", node->data.assign.id);
            printAST(node->data.assign.expr, indent + 1);
            break;
        case NODE_SEQUENCE:
            printf("SEQUENCE\n");
            printAST(node->data.seq.first, indent + 1);
            printAST(node->data.seq.second, indent + 1);
            break;
    }
}

void freeAST(ASTNode *node) {
    if (node == NULL) return;
    
    switch (node->type) {
        case NODE_CONSTANT:
            break;
        case NODE_IDENTIFIER:
            free(node->data.name);
            break;
        case NODE_OPERATOR:
            freeAST(node->data.op.left);
            freeAST(node->data.op.right);
            break;
        case NODE_IF:
            freeAST(node->data.ifStmt.condition);
            freeAST(node->data.ifStmt.thenBranch);
            if (node->data.ifStmt.elseBranch)
                freeAST(node->data.ifStmt.elseBranch);
            break;
        case NODE_ASSIGN:
            free(node->data.assign.id);
            freeAST(node->data.assign.expr);
            break;
        case NODE_SEQUENCE:
            freeAST(node->data.seq.first);
            freeAST(node->data.seq.second);
            break;
    }
    
    free(node);
}

ASTNode *root = NULL;

extern int yylex();
void yyerror(const char *s);
%}

%union {
    int iValue;              /* For integer constants */
    char *sValue;            /* For identifiers */
    struct ASTNode *nPtr;    /* For AST nodes */
}

%token <iValue> INTEGER
%token <sValue> IDENTIFIER
%token IF ELSE WHILE
%token ASSIGN
%token END_OF_FILE

%left '+' '-'
%left '*' '/'
%right UMINUS

%type <nPtr> expr stmt stmt_list program

%%

/* Grammar rules with semantic actions */

program:
    stmt_list END_OF_FILE   { root = $1; return 0; }
    ;

stmt_list:
    stmt                    { $$ = $1; }
    | stmt ';' stmt_list    { $$ = createSequenceNode($1, $3); }
    ;

stmt:
    IDENTIFIER ASSIGN expr  { $$ = createAssignNode($1, $3); free($1); }
    | IF '(' expr ')' stmt  { $$ = createIfNode($3, $5, NULL); }
    | IF '(' expr ')' stmt ELSE stmt  
                            { $$ = createIfNode($3, $5, $7); }
    | '{' stmt_list '}'     { $$ = $2; }
    | expr                  { $$ = $1; }
    ;

expr:
    INTEGER                 { $$ = createConstantNode($1); }
    | IDENTIFIER            { $$ = createIdentifierNode($1); free($1); }
    | expr '+' expr         { $$ = createOperatorNode('+', $1, $3); }
    | expr '-' expr         { $$ = createOperatorNode('-', $1, $3); }
    | expr '*' expr         { $$ = createOperatorNode('*', $1, $3); }
    | expr '/' expr         { $$ = createOperatorNode('/', $1, $3); }
    | '(' expr ')'          { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = createOperatorNode('u', createConstantNode(0), $2); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}

int main(void) {
    yyparse();
    
    printf("Abstract Syntax Tree:\n");
    printAST(root, 0);
    
    freeAST(root);
    return 0;
}