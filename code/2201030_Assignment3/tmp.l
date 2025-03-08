%{ 
#include <stdio.h> 
#include <string.h> 

int operators_count = 0;
int operands_count = 0;
int valid = 1;
int top = -1;
int l = 0;
int j = 0; 
char operands[10][10];
char operators[10][10];
char stack[100]; 
%} 

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

[+-]?[0-9]+ { 
	operands_count++; 
	strcpy(operands[j], yytext); 
	j++; 
} 

"+"|"-"|"*"|"/" { 
	if (yytext[0] == '-' && (j == 0 || stack[top] == '(' || stack[top] == '{' || stack[top] == '[')) {
		operators_count++; 
		strcpy(operators[l], yytext); 
		l++; 
	} 
    else {
		operators_count++; 
		strcpy(operators[l], yytext); 
		l++; 
	}
}

[ \t\n]                 ; 
.                       { valid = 0; } 

%%  

int main() { 
	int k; 
	printf("Enter the arithmetic expression and press Ctrl+D: "); 
	yylex(); 

	if (valid == 1 && top == -1) { 
		printf("\nValid Expression.\n"); 
		printf("The operators are: \n"); 
		for (k = 0; k < l; k++) printf("%s\n", operators[k]); 

		printf("The identifiers are: \n"); 
		for (k = 0; k < j; k++) printf("%s\n", operands[k]); 
	} 
	else 
		printf("\nInvalid Expression.\n"); 

	return 0; 
} 

int yywrap() {
    return 1;
}
