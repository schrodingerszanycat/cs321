#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY_LEN 2048
#define MAX_FIELD_LEN 256
#define MAX_RESULT_LEN 4096

// Database connection config
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "as8_student_db"

// Function to execute a SQL query and return results as a string
char* execute_query(const char* sql_query) {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    static char output[MAX_RESULT_LEN];
    unsigned int num_fields;
    unsigned int i;
    
    // Clear the output buffer
    memset(output, 0, MAX_RESULT_LEN);
    
    // Initialize the MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        sprintf(output, "Error initializing MySQL connection: %s\n", mysql_error(conn));
        return output;
    }
    
    // Connect to the database
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        sprintf(output, "Error connecting to database: %s\n", mysql_error(conn));
        mysql_close(conn);
        return output;
    }
    
    // Execute the query
    if (mysql_query(conn, sql_query) != 0) {
        sprintf(output, "Error executing query: %s\n", mysql_error(conn));
        mysql_close(conn);
        return output;
    }
    
    // Check if this is a SELECT query (which returns results)
    if (strncasecmp(sql_query, "SELECT", 6) == 0 || 
        strncasecmp(sql_query, "SHOW", 4) == 0 ||
        strncasecmp(sql_query, "DESCRIBE", 8) == 0) {
        
        // Get the result set
        result = mysql_store_result(conn);
        if (result == NULL) {
            sprintf(output, "Error retrieving result set: %s\n", mysql_error(conn));
            mysql_close(conn);
            return output;
        }
        
        // Get field count
        num_fields = mysql_num_fields(result);
        
        // Append column headers
        strcat(output, "+");
        for (i = 0; i < num_fields; i++) {
            field = mysql_fetch_field_direct(result, i);
            strcat(output, "----------------+");
        }
        strcat(output, "\n| ");
        
        // Column names
        for (i = 0; i < num_fields; i++) {
            field = mysql_fetch_field_direct(result, i);
            sprintf(output + strlen(output), "%-14s | ", field->name);
        }
        strcat(output, "\n+");
        
        // Header divider
        for (i = 0; i < num_fields; i++) {
            strcat(output, "----------------+");
        }
        strcat(output, "\n");
        
        // Fetch and process each row
        while ((row = mysql_fetch_row(result))) {
            strcat(output, "| ");
            for (i = 0; i < num_fields; i++) {
                sprintf(output + strlen(output), "%-14s | ", row[i] ? row[i] : "NULL");
            }
            strcat(output, "\n");
        }
        
        // Bottom border
        strcat(output, "+");
        for (i = 0; i < num_fields; i++) {
            strcat(output, "----------------+");
        }
        strcat(output, "\n");
        
        // Add row count
        sprintf(output + strlen(output), "%lu rows in set\n", 
                (unsigned long)mysql_num_rows(result));
        
        // Free the result set
        mysql_free_result(result);
    } 
    else {
        // For non-SELECT queries, return affected rows
        sprintf(output, "Query OK, %lu row(s) affected\n", 
                (unsigned long)mysql_affected_rows(conn));
    }
    
    // Close the connection
    mysql_close(conn);
    
    return output;
}