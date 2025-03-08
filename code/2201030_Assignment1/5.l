%{
#include <stdio.h>
#include <stdlib.h>  
int date_validity = 0;
int check(char *);
%}

date   0[1-9]|[1-2][0-9]|3[0-1] 
month  0[1-9]|1[0-2]
year   [0-9]{4}

%%

^({date}"/"{month}"/"{year})$ { date_validity = check(yytext); }
[ \t\n]+ ;  
(.)+ ;  

%%

int check(char* str) {
    char* date = str;
    char* month = str+3;
    char* year = str+6;

    /*checking for months with 31 days*/
    if (date[0] == '3' && date[1] == '1') {
        if (month[0] == '0') {
            if (month[1] == '2' || month[1] == '4' || month[1] == '6' || month[1] == '9') {
                return 0;
            }
        }
        if (month[0] == '1') {
            if (month[1] == '1')
                return 0;
        }
    } 

    int year_ = atoi(year);
    printf("year in int: %d\n", year_);

    /*checking if february has 30 or 31 in leap-year*/
    if((year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0)) {
        if (month[0] == '0' && month[1] == '2') {
            if ((date[0] == '3' && date[1] == '0') || (date[0] == '3' && date[1] == '1'))
                return 0;
        }
    }
    else { /*checking if february has 29, 30 or 31 days in non-leap year*/
        if (month[0] == '0' && month[1] == '2') {
            if ((date[0] == '2' && date[1] == '9') || (date[0] == '3' && date[1] == '0') || (date[0] == '3' && date[1] == '1'))
                return 0;
        }
    }

    /*checking for valid year*/
    if (year_ < 1000 || year_ > 3000)
        return 0;

    return 1;
}

int main(){
    printf("Enter input: \n");
    yylex();  
    if (date_validity == 1) {
        printf("Valid.");
    }
    else {
        printf("Invalid.");
    }
    return 0;
}

int yywrap() {                                         
    return 1;
}
