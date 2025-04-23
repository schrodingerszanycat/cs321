%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern int yylex();
void yyerror(const char *s);

extern char decimal_str[];

void decimalToBinary(double num);
void printIntegerBinary(int n);
void printFractionBinary(double frac);

%}

%token DECIMAL

%%

input:
    DECIMAL {
        double num = atof(decimal_str);
        printf("Binary Equivalent: ");
        decimalToBinary(num);
        printf("\n");
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

void printIntegerBinary(int n) {
    if (n == 0) {
        printf("0");
        return;
    }

    char bin[64];
    int i = 0;
    while (n > 0) {
        bin[i++] = (n % 2) + '0';
        n /= 2;
    }
    for (int j = i - 1; j >= 0; j--) {
        putchar(bin[j]);
    }
}

void printFractionBinary(double frac) {
    int precision = 10;  // print up to 10 fractional bits
    while (precision-- > 0 && frac > 0) {
        frac *= 2;
        if (frac >= 1) {
            putchar('1');
            frac -= 1;
        } else {
            putchar('0');
        }
    }
}

void decimalToBinary(double num) {
    int integerPart = (int)num;
    double fractionPart = num - integerPart;

    printIntegerBinary(integerPart);
    if (fractionPart > 0) {
        putchar('.');
        printFractionBinary(fractionPart);
    }
}

int main() {
    printf("Enter a decimal number: ");
    yyparse();
    return 0;
}
