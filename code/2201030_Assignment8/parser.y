%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int yylex();
void yyerror(const char *s);

// Declare flex buffer functions and types
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

// Variables to build the SQL query
char columns[1000] = "";
char table_name[100] = "Student";  // Default table
char where_clause[1000] = "";
char set_clause[1000] = "";
char update_col[100] = "";
int has_where = 0;
int is_update = 0;

// Helper function to append to column list
void append_column(const char *col) {
    if (strlen(columns) > 0 && strcmp(columns, "*") != 0) {
        strcat(columns, ", ");
    }
    if (strcmp(columns, "*") != 0) {
        strcat(columns, col);
    }
}

// Helper function to build where clause
void build_where(const char *col, const char *op, const char *val) {
    if (strlen(where_clause) > 0) {
        strcat(where_clause, " AND ");
    }
    
    strcat(where_clause, col);
    strcat(where_clause, " ");
    strcat(where_clause, op);
    strcat(where_clause, " ");
    strcat(where_clause, val);
}

// Helper to build set clause
void build_set(const char *col, const char *val) {
    strcpy(update_col, col);
    sprintf(set_clause, "%s=%s", col, val);
}

void reset_query() {
    strcpy(columns, "");
    strcpy(where_clause, "");
    strcpy(set_clause, "");
    strcpy(update_col, "");
    has_where = 0;
    is_update = 0;
}
%}

%union {
    int intval;
    double floatval;
    char *strval;
}

%token <strval> GIVE SHOW UPDATE TABLE_KEYWORD SET TO
%token <strval> ALL INFORMATION TABLE COLUMN
%token <strval> HAVING WHOSE WHERE
%token <strval> COMP_OP AND OR NO
%token <intval> NUMBER
%token <floatval> FLOAT
%token <strval> IDENTIFIER
%token COMMA

%%

input: 
    /* empty */
    | input query
    ;

query:
    select_query             { 
        if (!is_update) {
            printf("select %s from %s", columns, table_name);
            if (has_where) {
                printf(" where %s", where_clause);
            }
            printf("\n");
        }
        reset_query();
    }
    | update_query           {
        printf("update table %s set %s", table_name, set_clause);
        if (has_where) {
            printf(" where %s", where_clause);
        }
        printf("\n");
        reset_query();
    }
    ;

select_query:
    GIVE select_columns
    | SHOW select_columns
    ;

select_columns:
    ALL INFORMATION          { strcpy(columns, "*"); }
    | column_list            
    | column_list where_clause { has_where = 1; }
    ;

column_list:
    COLUMN                   { 
        strcpy(columns, ""); 
        append_column($1); 
    }
    | column_list COMMA COLUMN {
        append_column($3);
    }
    | column_list AND COLUMN {
        append_column($3);
    }
    ;

where_clause:
    WHOSE condition          
    | HAVING condition       
    | WHERE condition        
    ;

condition:
    COLUMN COMP_OP NUMBER    {
        char num_str[20];
        sprintf(num_str, "%d", $3);
        build_where($1, $2, num_str);
    }
    | COLUMN COMP_OP FLOAT   {
        char float_str[20];
        sprintf(float_str, "%.1f", $3);
        build_where($1, $2, float_str);
    }
    | COLUMN COMP_OP COLUMN  {
        build_where($1, $2, $3);
    }
    | COLUMN NUMBER          {
        char num_str[20];
        sprintf(num_str, "%d", $2);
        build_where($1, "=", num_str);
    }
    ;

update_query:
    UPDATE COLUMN TO NUMBER student_roll_condition {
        is_update = 1;
        char num_str[20];
        sprintf(num_str, "%d", $4);
        build_set($2, num_str);
    }
    | UPDATE COLUMN TO FLOAT student_roll_condition {
        is_update = 1;
        char float_str[20];
        sprintf(float_str, "%.1f", $4);
        build_set($2, float_str);
    }
    ;

student_roll_condition:
    HAVING COLUMN NO NUMBER  {
        char num_str[20];
        sprintf(num_str, "%d", $4);
        build_where($2, "=", num_str);
        has_where = 1;
    }
    | HAVING COLUMN NUMBER   {
        char num_str[20];
        sprintf(num_str, "%d", $3);
        build_where($2, "=", num_str);
        has_where = 1;
    }
    | WHOSE COLUMN NO NUMBER {
        char num_str[20];
        sprintf(num_str, "%d", $4);
        build_where($2, "=", num_str);
        has_where = 1;
    }
    | WHOSE COLUMN NUMBER    {
        char num_str[20];
        sprintf(num_str, "%d", $3);
        build_where($2, "=", num_str);
        has_where = 1;
    }
    | WHERE COLUMN NO NUMBER {
        char num_str[20];
        sprintf(num_str, "%d", $4);
        build_where($2, "=", num_str);
        has_where = 1;
    }
    | WHERE COLUMN NUMBER    {
        char num_str[20];
        sprintf(num_str, "%d", $3);
        build_where($2, "=", num_str);
        has_where = 1;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

// Rename to parser_main to avoid conflict with GUI's main function
int parser_main() {
    printf("English to SQL Converter\n");
    printf("Enter your query (or 'quit' to exit): ");
    
    char line[1024];
    while(fgets(line, sizeof(line), stdin)) {
        if(strncmp(line, "quit", 4) == 0) {
            break;
        }
        
        // Add input to lex
        YY_BUFFER_STATE buffer = yy_scan_string(line);
        yyparse();
        yy_delete_buffer(buffer);
        
        printf("\nEnter your query (or 'quit' to exit): ");
    }
    
    return 0;
}

// Add a function to parse a single string and return the generated SQL
char* parse_english_query(const char* query) {
    // Reset the query state before parsing
    reset_query();
    
    // Parse the query
    YY_BUFFER_STATE buffer = yy_scan_string(query);
    yyparse();
    yy_delete_buffer(buffer);
    
    // Return the result (this is simplified - you'd need to modify to return the actual SQL)
    static char result[1024];
    sprintf(result, "select %s from %s", columns, table_name);
    if (has_where) {
        sprintf(result + strlen(result), " where %s", where_clause);
    }
    
    return result;
}