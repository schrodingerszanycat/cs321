-- Create the student database
CREATE DATABASE IF NOT EXISTS student_db;
USE student_db;

-- Create the Student table with required attributes
CREATE TABLE IF NOT EXISTS Student (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100),
  roll INT UNIQUE,
  cpi FLOAT
);

-- Insert sample data for testing
INSERT INTO Student (name, roll, cpi) VALUES
('Alice', 101, 8.5),
('Bob', 102, 7.2),
('Charlie', 103, 9.1),
('Dave', 104, 6.8),
('Eve', 105, 8.9),
('Frank', 106, 7.5),
('Grace', 107, 9.3),
('Heidi', 108, 6.5),
('Ivan', 109, 8.2),
('Judy', 110, 7.9);