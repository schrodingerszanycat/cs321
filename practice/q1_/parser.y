%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum NumType {
    NUM_TYPE_NUMBER,
    NUM_TYPE_OPERATOR
};

enum Op {
    ADD,
    SUB,
    MUL,
    DIV
};

typedef struct Node {
    enum NumType type;
    union {
        int val;          /* For NUMBER */
        struct {          /* For OPERATOR */
            enum Op op;
            struct Node* l;
            struct Node* r;
        } bop;
    } data;
} Node;

Node* makeNumber(int val);
Node* makeOperator(enum Op op, Node* l, Node* r);
void print_Concrete(char* rule, void* val);
void print_AST(Node* n, int ind);
void freeAST(Node* n);

int yylex(void);
int yyerror(char* s);
%}

%token NUMBER PLUS MINUS TIMES DIVIDE LPAREN RPAREN

%union {
    int num;
    struct Node* node;
}

%type <num> NUMBER
%type <node> expr term factor

%%

start   : expr              { 
                              printf("\n=== Abstract Syntax Tree ===\n");
                              print_AST($1, 0);
                              freeAST($1);
                            }
        ;

expr    : expr PLUS term    { 
                              print_Concrete("expr -> expr + term", NULL);
                              $$ = makeOperator(ADD, $1, $3);
                            }
        | expr MINUS term   { 
                              print_Concrete("expr -> expr - term", NULL);
                              $$ = makeOperator(SUB, $1, $3);
                            }
        | term              { 
                              print_Concrete("expr -> term", NULL);
                              $$ = $1;
                            }
        ;

term    : term TIMES factor { 
                              print_Concrete("term -> term * factor", NULL);
                              $$ = makeOperator(MUL, $1, $3);
                            }
        | term DIVIDE factor { 
                              print_Concrete("term -> term / factor", NULL);
                              $$ = makeOperator(DIV, $1, $3);
                            }
        | factor            { 
                              print_Concrete("term -> factor", NULL);
                              $$ = $1;
                            }
        ;

factor  : NUMBER            { 
                              print_Concrete("factor -> NUMBER", &$1);
                              $$ = makeNumber($1);
                            }
        | LPAREN expr RPAREN { 
                              print_Concrete("factor -> ( expr )", NULL);
                              $$ = $2;
                            }
        ;

%%

Node* makeNumber(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = NUM_TYPE_NUMBER;
    n->data.val = val;
    return n;
}

Node* makeOperator(enum Op op, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = NUM_TYPE_OPERATOR;
    n->data.bop.op = op;
    n->data.bop.l = l;
    n->data.bop.r = r;
    return n;
}

void print_Concrete(char* rule, void* val) {
    static int depth = 0;
    static int first = 1;
    
    if (first) {
        printf("=== Concrete Parse Tree ===\n");
        first = 0;
    }
    
    int i;
    for (i = 0; i < depth; i++) {
        printf("  ");
    }
    
    printf("%s", rule);
    
    if (strstr(rule, "NUMBER") && val) {
        printf(" (value: %d)", *(int*)val);
    }
    
    printf("\n");
    depth++;
}

void print_AST(Node* n, int ind) {
    if (!n) return;
    
    int i;
    for (i = 0; i < ind; i++) {
        printf("  ");
    }
    
    if (n->type == NUM_TYPE_NUMBER) {
        printf("NUM: %d\n", n->data.val);
    } else if (n->type == NUM_TYPE_OPERATOR) {
        char op;
        switch (n->data.bop.op) {
            case ADD: op = '+'; break;
            case SUB: op = '-'; break;
            case MUL: op = '*'; break;
            case DIV: op = '/'; break;
        }
        printf("OP: %c\n", op);
        print_AST(n->data.bop.l, ind + 1);
        print_AST(n->data.bop.r, ind + 1);
    }
}

void freeAST(Node* n) {
    if (!n) return;
    
    if (n->type == NUM_TYPE_OPERATOR) {
        freeAST(n->data.bop.l);
        freeAST(n->data.bop.r);
    }
    
    free(n);
}

int yyerror(char* s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int main() {
    printf("Enter an arithmetic expression (e.g., 2+3*4):\n");
    yyparse();
    return 0;
}