#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LEN 2048
#define MAX_FIELD_LEN 256
#define MAX_RESULT_LEN 4096

// Database file path
#define DB_PATH "student_db.sqlite"

// Static variable to track row count in result_callback
static int row_count = 0;

// Callback function for SQLite query results
static int result_callback(void *output_ptr, int num_cols, char **col_values, char **col_names) {
    char *output = (char *)output_ptr;
    int i;
    
    // First row: Print headers
    if (row_count == 0) {
        // Top border
        strcat(output, "+");
        for (i = 0; i < num_cols; i++) {
            strcat(output, "----------------+");
        }
        strcat(output, "\n| ");
        
        // Column names
        for (i = 0; i < num_cols; i++) {
            sprintf(output + strlen(output), "%-14s | ", col_names[i]);
        }
        strcat(output, "\n+");
        
        // Header divider
        for (i = 0; i < num_cols; i++) {
            strcat(output, "----------------+");
        }
        strcat(output, "\n");
    }
    
    // Print row data
    strcat(output, "| ");
    for (i = 0; i < num_cols; i++) {
        sprintf(output + strlen(output), "%-14s | ", col_values[i] ? col_values[i] : "NULL");
    }
    strcat(output, "\n");
    
    row_count++;
    return 0;  // Continue processing
}

// Function to execute a SQL query and return results as a string
char* execute_query(const char* sql_query) {
    sqlite3 *db;
    char *err_msg = NULL;
    static char output[MAX_RESULT_LEN];
    int rc;
    int is_select = 0;
    
    // Reset row count for new query
    row_count = 0;
    
    // Clear the output buffer
    memset(output, 0, MAX_RESULT_LEN);
    
    // Check if this is a SELECT query
    if (strncasecmp(sql_query, "SELECT", 6) == 0 || 
        strncasecmp(sql_query, "SHOW", 4) == 0 ||
        strncasecmp(sql_query, "PRAGMA", 6) == 0) {
        is_select = 1;
    }
    
    // Open database connection
    rc = sqlite3_open(DB_PATH, &db);
    if (rc != SQLITE_OK) {
        sprintf(output, "Error opening SQLite database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return output;
    }
    
    // Execute the query
    if (is_select) {
        // For SELECT queries, use the callback to format results
        rc = sqlite3_exec(db, sql_query, result_callback, output, &err_msg);
        
        if (rc != SQLITE_OK) {
            sprintf(output, "Error executing query: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else {
            // Add row count to the end
            char *row_count_sql = sqlite3_mprintf("SELECT changes()");
            char row_count[32];
            
            // Add bottom border
            strcat(output, "+");
            int num_cols = 0;
            
            // Estimate number of columns by counting | characters in the first line
            char *line = strstr(output, "\n");
            if (line) {
                char *c;
                for (c = output; c < line; c++) {
                    if (*c == '|') num_cols++;
                }
                num_cols--; // Adjust for the first |
                
                for (int i = 0; i < num_cols; i++) {
                    strcat(output, "----------------+");
                }
                strcat(output, "\n");
            }
            
            // Add row count
            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT changes()", -1, &stmt, NULL);
            if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
                sprintf(row_count, "%d", sqlite3_column_int(stmt, 0));
                sprintf(output + strlen(output), "%s rows in set\n", row_count);
            }
            sqlite3_finalize(stmt);
        }
    } else {
        // For non-SELECT queries (UPDATE, INSERT, etc.)
        rc = sqlite3_exec(db, sql_query, NULL, NULL, &err_msg);
        
        if (rc != SQLITE_OK) {
            sprintf(output, "Error executing query: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else {
            // Show affected rows
            sprintf(output, "Query OK, %d row(s) affected\n", sqlite3_changes(db));
        }
    }
    
    // Close database connection
    sqlite3_close(db);
    
    return output;
}