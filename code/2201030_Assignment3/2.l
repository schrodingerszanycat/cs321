%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int identifier_count = 0;
char* unique_id[100];

void print_unique_id() {
    for (int i = 0; i < identifier_count; i++) {
        if (unique_id[i]) {
            printf("id: %s\n", unique_id[i]);
        }
    }
}

int found(char* yytext) {
    for(int i = 0; i < identifier_count; i++) {
        if (strcmp(unique_id[i], yytext) == 0) {
            return 1;
        }
    }
    return 0;
}
FILE* yyin;

%}

keyword "auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"|"_Bool"|"_Complex"|"_Imaginary"|"inline"|"restrict"|"_Alignas"|"_Alignof"|"_Atomic"|"_Generic"|"_Noreturn"|"_Static_assert"|"_Thread_local"
identifier [a-zA-Z_][a-zA-Z0-9_]*
comment "//"[^\n]*|"/*"([^*]|"*"[^/])*"*/"
operator "+"|"-"|"*"|"/"|"%"|"++"|"--"|"=="|"!="|">"|"<"|">="|"<="|"&&"|"||"|"!"|"&"|"|"|"^"|"~"|"<<"|">>"|"="|"+="|"-="|"*="|"/="|"%="|"&="|"|="|"^="|"<<="|">>="|"->"|"."|"?"|":"|","
special ";"|"{"|"}"|"["|"]"|"("|")"|"#"|"\\"|"'"|"\""|"."|","|":"|"?"|"!"
integer_constant [0-9]+|0[0-7]*|0[xX][0-9a-fA-F]+
float_constant [0-9]+\.[0-9]*([eE][+-]?[0-9]+)?
char_constant '([^'\\]|\\.)'
string_literal \"([^"\\]|\\.)*\"
preprocessor #(include|define|ifdef|ifndef|endif|if|else|elif|line|error|pragma)
header_file "<"[^>]+">"|"\"[^\"]+\""
macro_define #define[ \t]+[a-zA-Z_][a-zA-Z0-9_]*([ \t]+[^ \t\n]+)?
whitespace [ \t\n]+

%%

{keyword}|{operator}|{special}|{integer_constant}|{float_constant}|{char_constant}|{string_literal}|{comment}|{whitespace}|{preprocessor}|{header_file}|{macro_define}  ;
{identifier} {  
    if (identifier_count < 100) {
        int isPresent = found(yytext);
        if (isPresent == 0) {
            unique_id[identifier_count] = strdup(yytext);
            identifier_count++;
        }        
    }
}
. ;

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file) {
            yyin = file;
            yylex();
            fclose(file);
        } 
        else {
            fprintf(stderr, "Error opening input file.\n");
            return 1;
        }
    } 
    else {
        fprintf(stderr, "Usage: %s <input-file>.c\n", argv[0]);
        return 1;
    }
    
    printf("Number of identifiers: %d\n", identifier_count);
    print_unique_id();
    
    for (int i = 0; i < identifier_count; i++) {
        free(unique_id[i]);
    }
    
    return 0;
}

int yywrap() {
    return 1;
}
