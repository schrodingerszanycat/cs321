#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

// External functions from parser
extern char* parse_english_query(const char* query);
extern char* execute_query(const char* sql_query);

// Forward declarations for GTK callback functions
static void activate(GtkApplication* app, gpointer user_data);
static void on_convert_clicked(GtkWidget *widget, gpointer data);
static void on_execute_clicked(GtkWidget *widget, gpointer data);
static void on_clear_clicked(GtkWidget *widget, gpointer data);

// Global GTK widgets (accessible from callbacks)
GtkWidget *input_text;
GtkWidget *sql_text;
GtkWidget *result_text;
GtkWidget *status_bar;
guint status_context_id;

// Buffer for SQL query
char sql_query_buffer[2048];

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.englishsql", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

// Function to create the GUI
static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *convert_button;
    GtkWidget *execute_button;
    GtkWidget *clear_button;
    GtkWidget *scrolled_win1, *scrolled_win2, *scrolled_win3;
    GtkWidget *label1, *label2, *label3;

    // Create the main window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "English to SQL Converter");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Create a grid layout
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create labels
    label1 = gtk_label_new("Enter English Query:");
    label2 = gtk_label_new("Generated SQL:");
    label3 = gtk_label_new("Query Results:");
    
    gtk_widget_set_halign(label1, GTK_ALIGN_START);
    gtk_widget_set_halign(label2, GTK_ALIGN_START);
    gtk_widget_set_halign(label3, GTK_ALIGN_START);

    // Create text entry widgets with scrolling
    input_text = gtk_text_view_new();
    sql_text = gtk_text_view_new();
    result_text = gtk_text_view_new();
    
    // Make SQL and result text views read-only
    gtk_text_view_set_editable(GTK_TEXT_VIEW(sql_text), FALSE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(result_text), FALSE);
    
    // Set monospace font for SQL and results
    PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 10");
    gtk_widget_override_font(sql_text, font_desc);
    gtk_widget_override_font(result_text, font_desc);
    pango_font_description_free(font_desc);
    
    // Add scrollbars to text views
    scrolled_win1 = gtk_scrolled_window_new(NULL, NULL);
    scrolled_win2 = gtk_scrolled_window_new(NULL, NULL);
    scrolled_win3 = gtk_scrolled_window_new(NULL, NULL);
    
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_win1),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_win2),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_win3),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    gtk_container_add(GTK_CONTAINER(scrolled_win1), input_text);
    gtk_container_add(GTK_CONTAINER(scrolled_win2), sql_text);
    gtk_container_add(GTK_CONTAINER(scrolled_win3), result_text);
    
    gtk_widget_set_size_request(scrolled_win1, -1, 100);
    gtk_widget_set_size_request(scrolled_win2, -1, 100);
    gtk_widget_set_size_request(scrolled_win3, -1, 200);
    
    // Create buttons
    convert_button = gtk_button_new_with_label("Convert to SQL");
    execute_button = gtk_button_new_with_label("Execute SQL");
    clear_button = gtk_button_new_with_label("Clear All");
    
    // Create status bar
    status_bar = gtk_statusbar_new();
    status_context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(status_bar), "info");
    gtk_statusbar_push(GTK_STATUSBAR(status_bar), status_context_id, "Ready");

    // Connect signals for button clicks
    g_signal_connect(convert_button, "clicked", G_CALLBACK(on_convert_clicked), NULL);
    g_signal_connect(execute_button, "clicked", G_CALLBACK(on_execute_clicked), NULL);
    g_signal_connect(clear_button, "clicked", G_CALLBACK(on_clear_clicked), NULL);

    // Lay out the widgets in the grid
    // First row: English input
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), scrolled_win1, 0, 1, 3, 1);
    
    // Second row: SQL output
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 2, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), scrolled_win2, 0, 3, 3, 1);
    
    // Third row: buttons
    gtk_grid_attach(GTK_GRID(grid), convert_button, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), execute_button, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), clear_button, 2, 4, 1, 1);
    
    // Fourth row: query results
    gtk_grid_attach(GTK_GRID(grid), label3, 0, 5, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), scrolled_win3, 0, 6, 3, 2);
    
    // Status bar at bottom
    gtk_grid_attach(GTK_GRID(grid), status_bar, 0, 8, 3, 1);

    // Show all widgets
    gtk_widget_show_all(window);
}

// Callback for Convert button
static void on_convert_clicked(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *input_buffer;
    GtkTextBuffer *sql_buffer;
    GtkTextIter start, end;
    char *english_text;
    
    // Get the English query text
    input_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(input_text));
    gtk_text_buffer_get_bounds(input_buffer, &start, &end);
    english_text = gtk_text_buffer_get_text(input_buffer, &start, &end, FALSE);
    
    if (strlen(english_text) == 0) {
        gtk_statusbar_push(GTK_STATUSBAR(status_bar), status_context_id, 
                          "Error: Please enter an English query");
        g_free(english_text);
        return;
    }
    
    // Reset the SQL query buffer
    memset(sql_query_buffer, 0, sizeof(sql_query_buffer));
    
    // Call the parser to convert English to SQL
    char* sql_result = parse_english_query(english_text);
    
    // Copy the result to our buffer
    snprintf(sql_query_buffer, sizeof(sql_query_buffer), "%s", sql_result);
    
    // Display the SQL query in the second text view
    sql_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sql_text));
    gtk_text_buffer_set_text(sql_buffer, sql_query_buffer, -1);
    
    gtk_statusbar_push(GTK_STATUSBAR(status_bar), status_context_id, 
                      "English query converted to SQL");
    
    g_free(english_text);
}

// Callback for Execute button
static void on_execute_clicked(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *result_buffer;
    GtkTextBuffer *sql_buffer;
    GtkTextIter start, end;
    char *sql_text_str;
    char *result_str;
    
    // Get the SQL query
    sql_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sql_text));
    gtk_text_buffer_get_bounds(sql_buffer, &start, &end);
    sql_text_str = gtk_text_buffer_get_text(sql_buffer, &start, &end, FALSE);
    
    if (strlen(sql_text_str) == 0) {
        gtk_statusbar_push(GTK_STATUSBAR(status_bar), status_context_id, 
                          "Error: No SQL query to execute");
        g_free(sql_text_str);
        return;
    }
    
    // Execute the SQL query
    result_str = execute_query(sql_text_str);
    
    // Display the results
    result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(result_text));
    gtk_text_buffer_set_text(result_buffer, result_str, -1);
    
    gtk_statusbar_push(GTK_STATUSBAR(status_bar), status_context_id, 
                      "SQL query executed");
    
    g_free(sql_text_str);
}

// Callback for Clear button
static void on_clear_clicked(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *input_buffer, *sql_buffer, *result_buffer;
    
    // Clear all text views
    input_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(input_text));
    sql_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sql_text));
    result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(result_text));
    
    gtk_text_buffer_set_text(input_buffer, "", -1);
    gtk_text_buffer_set_text(sql_buffer, "", -1);
    gtk_text_buffer_set_text(result_buffer, "", -1);
    
    gtk_statusbar_push(GTK_STATUSBAR(status_bar), status_context_id, 
                      "All fields cleared");
}