#!/bin/bash

# Create SQLite database and initialize it with sample data
sqlite3 student_db.sqlite < create_sqlite_database.sql

echo "SQLite database created successfully!"