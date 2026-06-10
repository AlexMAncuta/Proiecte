

CREATE DATABASE IF NOT EXISTS store_management;
USE store_management;

    CREATE TABLE categories (
                            category_id INT AUTO_INCREMENT PRIMARY KEY,
                            name VARCHAR(100) NOT NULL
    );

    CREATE TABLE products (
                          product_id INT AUTO_INCREMENT PRIMARY KEY,
                          name VARCHAR(150) NOT NULL,
                          category_id INT NOT NULL,
                          price DECIMAL(10, 2) NOT NULL,
                          stock INT NOT NULL DEFAULT 0,
                          FOREIGN KEY (category_id) REFERENCES categories(category_id)
    );

    CREATE TABLE employees (
                           employee_id INT AUTO_INCREMENT PRIMARY KEY,
                           first_name VARCHAR(80) NOT NULL,
                           last_name VARCHAR(80) NOT NULL,
                           department VARCHAR(80) NOT NULL,
                           salary DECIMAL(10, 2) NOT NULL
    );

    CREATE TABLE customers (
                           customer_id INT AUTO_INCREMENT PRIMARY KEY,
                           first_name VARCHAR(80) NOT NULL,
                           last_name VARCHAR(80) NOT NULL,
                           email VARCHAR(100) UNIQUE
    );

    CREATE TABLE sales (
                       sale_id INT AUTO_INCREMENT PRIMARY KEY,
                       customer_id INT NOT NULL,
                       employee_id INT NOT NULL,
                       sale_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                       FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
                       FOREIGN KEY (employee_id) REFERENCES employees(employee_id)
    );

    CREATE TABLE sale_items (
                            item_id INT AUTO_INCREMENT PRIMARY KEY,
                            sale_id INT NOT NULL,
                            product_id INT NOT NULL,
                            quantity INT NOT NULL,
                            unit_price DECIMAL(10, 2) NOT NULL,
                            FOREIGN KEY (sale_id) REFERENCES sales(sale_id),
                            FOREIGN KEY (product_id) REFERENCES products(product_id)
    );

INSERT INTO categories (name) VALUES
                                  ('Electronics'), ('Clothing'), ('Food');

INSERT INTO products (name, category_id, price, stock) VALUES
                                                           ('Laptop 15"', 1, 3299.99, 25),
                                                           ('Wireless Mouse', 1, 149.99, 80),
                                                           ('Winter Jacket', 2, 449.99, 10),
                                                           ('Mineral Water 6x1L', 3, 12.99, 300);

INSERT INTO employees (first_name, last_name, department, salary) VALUES
                                                                      ('Ion', 'Popescu', 'Sales', 4500.00),
                                                                      ('Maria', 'Ionescu', 'Sales', 4200.00);

INSERT INTO customers (first_name, last_name, email) VALUES
                                                         ('Mihai', 'Dumitrescu', 'mihai.d@gmail.com'),
                                                         ('Ana', 'Stancu', 'ana.stancu@yahoo.com');

INSERT INTO sales (customer_id, employee_id) VALUES
                                                 (1, 1),
                                                 (2, 2); 

INSERT INTO sale_items (sale_id, product_id, quantity, unit_price) VALUES
                                                                    (1, 1, 1, 3299.99), 
                                                                    (1, 2, 2, 149.99),  
                                                                    (2, 3, 1, 449.99);  

    SELECT p.name AS Product, 
    c.name AS Category, 
    p.price, p.stock

FROM products p
         JOIN categories c ON p.category_id = c.category_id;

    SELECT c.name AS Category, 
    SUM(p.stock) AS Total_Items, 
    SUM(p.stock * p.price) AS Total_Stock_Value

FROM products p
         JOIN categories c ON p.category_id = c.category_id
GROUP BY c.category_id;

SELECT s.sale_id, c.first_name AS Customer, 
e.first_name AS Employee, 
SUM(si.quantity * si.unit_price) AS Total_Amount

FROM sales s
         JOIN customers c ON s.customer_id = c.customer_id
         JOIN employees e ON s.employee_id = e.employee_id
         JOIN sale_items si ON s.sale_id = si.sale_id
GROUP BY s.sale_id;

UPDATE employees
SET salary = 4800.00
WHERE employee_id = 1;

INSERT INTO customers (first_name, last_name, email) 
    VALUES ('Client', 'DeSters', 'delete.me@test.ro');

DELETE FROM customers
WHERE email = 'delete.me@test.ro';
