%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.yy.h"

void yyerror(char *);
int yylex(void);

char sql_query[1000];
int query_ready = 0;

char* get_sql_query() {
    return sql_query;
}

void reset_query_status() {
    query_ready = 0;
}

int is_query_ready() {
    return query_ready;
}
%}

%union {
    int num;
    char *str;
}

%token PLEASE SHOW ME THE OF ALL INFORMATION STUDENT WHOSE HAVING
%token NUMBER IS TO MORE_THAN LESS_THAN AND OR NO DOT COMMA UPDATE

%token <num> INTEGER
%token <str> NAME ROLL CPI

%%

statement: query DOT {
             query_ready = 1;
         }
         ;

query: select_query
     | update_query
     ;

select_query: PLEASE SHOW ME THE ROLL NUMBER OF THE STUDENT {
                strcpy(sql_query, "SELECT roll FROM Student");
            }
            | PLEASE SHOW ME ALL THE INFORMATION OF THE STUDENT {
                strcpy(sql_query, "SELECT * FROM Student");
            }
            | PLEASE SHOW ME THE NAME AND ROLL NUMBER OF THE STUDENT WHOSE CPI IS MORE_THAN INTEGER {
                sprintf(sql_query, "SELECT name, roll FROM Student WHERE cpi > %d", $16);
            }
            | PLEASE SHOW THE NAME AND ROLL NUMBER OF THE STUDENT WHOSE CPI IS MORE_THAN INTEGER {
                sprintf(sql_query, "SELECT name, roll FROM Student WHERE cpi > %d", $15);
            }
            ;

update_query: PLEASE UPDATE THE CPI OF THE STUDENT HAVING ROLL NO INTEGER TO INTEGER {
                sprintf(sql_query, "UPDATE Student SET cpi=%d WHERE roll=%d", $13, $11);
            }
            ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int parse_english(char* sentence) {
    reset_query_status();

    YY_BUFFER_STATE buffer = yy_scan_string(sentence);

    int result = yyparse();

    yy_delete_buffer(buffer);

    return result;
}
