%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n_operator = 0;
int n_operand = 0l;
int valid = 1;
int top = -1;
int l = 0;
int j = 0;
char opnd[10][10];
char oprt[10][10];
char stack[100];
int expect_operand = 1; 

%}

%x check_negative

%%
"(" { top++; stack[top] = '('; } 
"{" { top++; stack[top] = '{'; } 
"[" { top++; stack[top] = '['; } 

")" { 
	if (top == -1 || stack[top] != '(') valid = 0;	 
	else { top--; } 
} 

"}" { 
	if (top == -1 || stack[top] != '{') valid = 0;	 
	else { top--; } 
} 

"]" { 
	if (top == -1 || stack[top] != '[') valid = 0; 
	else { top--; } 
} 
"-" {
    if (expect_operand) BEGIN(check_negative);
    else {
        n_operator++;
        strcpy(oprt[l], yytext);
        l++;
        expect_operand = 1; 
    }
}
<check_negative>[0-9]+ {
    n_operand++;
    sprintf(opnd[j], "-%s", yytext);
    j++;
    expect_operand = 0; 
    BEGIN(INITIAL);
}
"+"|"*"|"/" {
    n_operator++;
    strcpy(oprt[l], yytext);
    l++;
    expect_operand = 1; 
}
[0-9]+|[a-zA-Z][a-zA-Z0-9_]* {
    n_operand++;
    strcpy(opnd[j], yytext);
    j++;
    expect_operand = 0;
}
[ \t\n] ;
%%

int main() {
    int k;
    printf("Enter the arithmetic expression and press Ctrl+D: ");
    yylex();

    if (valid == 1 && top == -1 && (n_operand - n_operator) == 1) {
        printf("\nValid expression\n");

        printf("The operators are\n");
        for (k = 0; k < l; k++)
            printf("%s \n", oprt[k]);

        printf("The operands are\n");
        for (k = 0; k < j; k++)
            printf("%s \n", opnd[k]);
    }
    else
        printf("The expression is invalid\n");
    return 0;
}

int yywrap()
{
    return 1;
}