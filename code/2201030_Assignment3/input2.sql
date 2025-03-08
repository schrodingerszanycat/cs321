CREATE TABLE employees (
    id INT,
    name VARCHAR(50),
    position VARCHAR(50)
);

INSERT INTO employees (id, name, position) VALUES (1, ' CREATE ', 'Manager');
INSERT INTO employees (id, name, position) VALUES (2, 'Bob', 'Engineer');
INSERT INTO employees (id, name, position) VALUES (3, 'Charlie', 'Analyst');

UPDATE employees SET position = 'Senior Manager' WHERE name = 'Alice';

DELETE FROM employees WHERE id = 3;

CREATE TABLE departments (
    id INT,
    name VARCHAR(50)
);

INSERT INTO departments (id, name) VALUES (1, 'HR');
INSERT INTO departments (id, name) VALUES (2, 'Engineering');

DROP TABLE employees;
