CREATE DATABASE banking_system;

USE banking_system;

CREATE TABLE customers (
    account_no INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    password VARCHAR(100) NOT NULL,
    balance DECIMAL(12,2) DEFAULT 0.00
);

CREATE TABLE transactions (
    transaction_id INT AUTO_INCREMENT PRIMARY KEY,
    account_no INT,
    type VARCHAR(20),
    amount DECIMAL(10,2),
    transaction_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
