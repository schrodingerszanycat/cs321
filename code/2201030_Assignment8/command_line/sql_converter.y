/* sql_converter.y */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declare lexer function */
extern int yylex(void);
/* Declare the buffer management function from lex */
#ifdef __cplusplus // Handle C++ linkage if needed, though unlikely here
extern "C" {
#endif
    struct yy_buffer_state; // Forward declare the opaque type
    typedef struct yy_buffer_state *YY_BUFFER_STATE;
    extern YY_BUFFER_STATE yy_scan_string(const char * str);
    extern void yy_delete_buffer(YY_BUFFER_STATE);
#ifdef __cplusplus
}
#endif


/* Error reporting function */
void yyerror(const char *s); // Use const char* for yyerror standard

/* Global variables to store the result */
char sql_query[1000];
int query_ready = 0;

/* Function prototypes for external access (optional, could use extern in main.c) */
const char* get_sql_query(); // Return const char* as we shouldn't modify it outside
void reset_query_status();
int is_query_ready();

%}

%union {
    int num;
    char *str;
}

/* Define tokens */
%token PLEASE SHOW ME THE OF ALL INFORMATION STUDENT WHOSE HAVING
%token NUMBER IS TO MORE_THAN LESS_THAN AND OR NO DOT COMMA UPDATE DELETE
%token WITH ORDERED BY DESC ASC

/* Define tokens with associated types from the union */
%token <num> INTEGER
%token <str> NAME ROLL CPI STRING

/* Define the start symbol */
%start statement

%%

statement: query DOT { query_ready = 1; /* $$ = $1; // No return value needed here */ } ;

query: select_query | update_query | delete_query ;

select_query:
      PLEASE SHOW ME THE ROLL NUMBER OF THE STUDENT
      { strcpy(sql_query, "SELECT roll FROM Student"); }
    | PLEASE SHOW ME ALL THE INFORMATION OF THE STUDENT
      { strcpy(sql_query, "SELECT * FROM Student"); }
    | PLEASE SHOW ME THE NAME AND ROLL NUMBER OF THE STUDENT WHOSE CPI IS MORE_THAN INTEGER
      { snprintf(sql_query, sizeof(sql_query), "SELECT name, roll FROM Student WHERE cpi > %d", $16); } // Use snprintf
    | PLEASE SHOW ME THE STUDENT WHOSE NAME IS STRING
      { snprintf(sql_query, sizeof(sql_query), "SELECT * FROM Student WHERE name = '%s'", $9); free($9); /* Free strdup'd string */ }
    | PLEASE SHOW ME THE STUDENT WHOSE CPI IS MORE_THAN INTEGER AND LESS_THAN INTEGER
      { snprintf(sql_query, sizeof(sql_query), "SELECT * FROM Student WHERE cpi > %d AND cpi < %d", $10, $13); }
    | PLEASE SHOW ME THE STUDENT WITH ROLL NUMBER INTEGER
      { snprintf(sql_query, sizeof(sql_query), "SELECT * FROM Student WHERE roll = %d", $9); }
    | PLEASE SHOW ME ALL STUDENT ORDERED BY CPI DESC
      { strcpy(sql_query, "SELECT * FROM Student ORDER BY cpi DESC"); }
    | PLEASE SHOW ME ALL STUDENT ORDERED BY CPI ASC
      { strcpy(sql_query, "SELECT * FROM Student ORDER BY cpi ASC"); }
    ;

update_query:
      PLEASE UPDATE THE CPI OF THE STUDENT HAVING ROLL NO INTEGER TO INTEGER
      { snprintf(sql_query, sizeof(sql_query), "UPDATE Student SET cpi=%d WHERE roll=%d", $13, $11); }
    ;

delete_query:
      PLEASE DELETE THE STUDENT WITH ROLL NUMBER INTEGER
      { snprintf(sql_query, sizeof(sql_query), "DELETE FROM Student WHERE roll = %d", $8); }
    ;

%%

/* Error reporting function definition */
void yyerror(const char *s) {
  fprintf(stderr, "Syntax Error: %s\n", s);
}

/* Accessor functions */
const char* get_sql_query() {
    return sql_query;
}

void reset_query_status() {
    query_ready = 0;
    sql_query[0] = '\0'; // Also clear the query buffer
}

int is_query_ready() {
    return query_ready;
}

/*
 * We remove parse_english. The main function will handle
 * setting up the input buffer now.
 */
/*
int parse_english(char* sentence) {
    reset_query_status();
    YY_BUFFER_STATE buffer = yy_scan_string(sentence);
    int result = yyparse();
    yy_delete_buffer(buffer);
    // Need to free strings allocated by strdup in the lexer actions
    // This is tricky here, better to free them in the parser rules
    // right after they are used.
    return result;
}
*/

/* Add freeing for unused string tokens if parsing fails or rule doesn't use them.
   This requires more complex error handling using %destructor if desired,
   or careful freeing within rules as done for STRING.
   For simple cases, freeing used strings like in the STRING rule is okay. */