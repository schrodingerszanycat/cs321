import ctypes
import os
import sqlite3
import tkinter as tk
from tkinter import messagebox, ttk
from tkinter.scrolledtext import ScrolledText

# Load the shared library
lib_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "libenglishtosql.so")
english_to_sql_lib = ctypes.CDLL(lib_path)

# Define function prototypes
english_to_sql_lib.parse_english.argtypes = [ctypes.c_char_p]
english_to_sql_lib.parse_english.restype = ctypes.c_int
english_to_sql_lib.get_sql_query.restype = ctypes.c_char_p
english_to_sql_lib.is_query_ready.restype = ctypes.c_int

def parse_english_to_sql(english_text):
    """Convert English text to SQL using the C library"""
    result = english_to_sql_lib.parse_english(english_text.encode('utf-8'))
    if result == 0 and english_to_sql_lib.is_query_ready() == 1:
        sql_query = english_to_sql_lib.get_sql_query().decode('utf-8')
        return sql_query
    return None

# Database setup function
def setup_database():
    conn = sqlite3.connect('student_database.db')
    cursor = conn.cursor()

    # Create Student table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS Student (
        student_id INTEGER PRIMARY KEY,
        name TEXT NOT NULL,
        roll INTEGER NOT NULL UNIQUE,
        cpi REAL NOT NULL
    );
    ''')

    # Check if data already exists
    cursor.execute("SELECT COUNT(*) FROM Student")
    if cursor.fetchone()[0] == 0:
        # Insert sample data
        sample_data = [
            (1, 'Alice', 101, 8.5),
            (2, 'Bob', 102, 7.8),
            (3, 'Charlie', 103, 9.2),
            (4, 'Diana', 104, 6.5),
            (5, 'Eve', 105, 8.0)
        ]
        cursor.executemany('INSERT INTO Student (student_id, name, roll, cpi) VALUES (?, ?, ?, ?)', sample_data)

    conn.commit()
    conn.close()

# Function to execute SQL query
def execute_query(query):
    try:
        conn = sqlite3.connect('student_database.db')
        cursor = conn.cursor()
        cursor.execute(query)

        # If SELECT query, fetch results
        if query.strip().upper().startswith("SELECT"):
            results = cursor.fetchall()

            # Get column names
            column_names = [description[0] for description in cursor.description]

            conn.close()
            return True, column_names, results
        else:
            # For non-SELECT queries (UPDATE, INSERT, etc.)
            conn.commit()
            conn.close()
            return True, None, f"Query executed successfully. Rows affected: {cursor.rowcount}"
    except sqlite3.Error as e:
        return False, None, f"Database error: {e}"
    except Exception as e:
        return False, None, f"Error: {e}"

# GUI Application
class EnglishToSQLApp:
    def __init__(self, root):
        self.root = root
        self.root.title("English to SQL Converter")
        self.root.geometry("800x600")

        # Create a main frame
        main_frame = ttk.Frame(root, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)

        # Input section
        input_frame = ttk.LabelFrame(main_frame, text="English Input", padding="5")
        input_frame.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        self.input_text = ScrolledText(input_frame, height=5, width=70, wrap=tk.WORD)
        self.input_text.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        # Button frame
        button_frame = ttk.Frame(main_frame)
        button_frame.pack(fill=tk.X, padx=5, pady=5)

        self.convert_button = ttk.Button(button_frame, text="Convert to SQL", command=self.convert_to_sql)
        self.convert_button.pack(side=tk.LEFT, padx=5)

        self.execute_button = ttk.Button(button_frame, text="Execute SQL", command=self.execute_sql, state=tk.DISABLED)
        self.execute_button.pack(side=tk.LEFT, padx=5)

        self.clear_button = ttk.Button(button_frame, text="Clear All", command=self.clear_all)
        self.clear_button.pack(side=tk.RIGHT, padx=5)

        # SQL output section
        sql_frame = ttk.LabelFrame(main_frame, text="Generated SQL Query", padding="5")
        sql_frame.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        self.sql_text = ScrolledText(sql_frame, height=3, width=70, wrap=tk.WORD)
        self.sql_text.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        # Results section
        results_frame = ttk.LabelFrame(main_frame, text="Query Results", padding="5")
        results_frame.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        # Create a frame for the treeview and scrollbar
        tree_frame = ttk.Frame(results_frame)
        tree_frame.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        # Scrollbars
        vsb = ttk.Scrollbar(tree_frame, orient="vertical")
        hsb = ttk.Scrollbar(tree_frame, orient="horizontal")

        # Treeview for results
        self.results_tree = ttk.Treeview(tree_frame, columns=(), show="headings",
                                         yscrollcommand=vsb.set, xscrollcommand=hsb.set)

        # Configure scrollbars
        vsb.config(command=self.results_tree.yview)
        hsb.config(command=self.results_tree.xview)

        # Grid layout
        self.results_tree.grid(column=0, row=0, sticky='nsew')
        vsb.grid(column=1, row=0, sticky='ns')
        hsb.grid(column=0, row=1, sticky='ew')

        tree_frame.columnconfigure(0, weight=1)
        tree_frame.rowconfigure(0, weight=1)

        # Status bar
        self.status_var = tk.StringVar()
        self.status_var.set("Ready")
        status_bar = ttk.Label(root, textvariable=self.status_var, relief=tk.SUNKEN, anchor=tk.W)
        status_bar.pack(side=tk.BOTTOM, fill=tk.X)

        # Initialize database
        setup_database()

        # Current SQL query
        self.current_sql = None

    def convert_to_sql(self):
        english_text = self.input_text.get("1.0", tk.END).strip()
        if not english_text:
            messagebox.showwarning("Warning", "Please enter an English sentence.")
            return

        # Ensure the sentence ends with a period
        if not english_text.endswith('.'):
            english_text += '.'

        # Parse English to SQL
        sql_query = parse_english_to_sql(english_text)

        if sql_query:
            self.sql_text.delete("1.0", tk.END)
            self.sql_text.insert(tk.END, sql_query)
            self.current_sql = sql_query
            self.execute_button.config(state=tk.NORMAL)
            self.status_var.set("SQL query generated successfully")
        else:
            messagebox.showerror("Error", "Could not parse the English sentence. Please check your input.")
            self.status_var.set("Failed to generate SQL query")

    def execute_sql(self):
        if not self.current_sql:
            messagebox.showwarning("Warning", "No SQL query to execute.")
            return

        # Clear previous results
        for i in self.results_tree.get_children():
            self.results_tree.delete(i)

        # Execute the query
        success, columns, results = execute_query(self.current_sql)

        if success:
            if isinstance(results, str):
                # Non-SELECT query result
                messagebox.showinfo("Success", results)
                self.status_var.set(results)
            else:
                # SELECT query result with data
                # Configure treeview columns
                self.results_tree["columns"] = columns
                for col in columns:
                    self.results_tree.heading(col, text=col)
                    self.results_tree.column(col, width=100, anchor=tk.CENTER)

                # Insert data rows
                for i, row in enumerate(results):
                    self.results_tree.insert("", tk.END, values=row, iid=f"row{i}")

                self.status_var.set(f"Query executed successfully. {len(results)} rows returned.")
        else:
            # Error occurred
            messagebox.showerror("Error", results)
            self.status_var.set(results)

    def clear_all(self):
        self.input_text.delete("1.0", tk.END)
        self.sql_text.delete("1.0", tk.END)
        for i in self.results_tree.get_children():
            self.results_tree.delete(i)
        self.current_sql = None
        self.execute_button.config(state=tk.DISABLED)
        self.status_var.set("Ready")

# Main application
if __name__ == "__main__":
    root = tk.Tk()
    app = EnglishToSQLApp(root)
    root.mainloop()
