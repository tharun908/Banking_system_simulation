# Banking System Simulation

## Overview

A console-based Banking System developed using C and MySQL. The project simulates basic banking operations such as account creation, login authentication, deposits, withdrawals, balance inquiry, and transaction history management.

## Features

* Create New Bank Account
* User Login Authentication
* Deposit Money
* Withdraw Money
* Check Account Balance
* View All Accounts
* Transaction History Tracking
* Insufficient Balance Validation
* MySQL Database Integration

## Technologies Used

* C Programming Language
* MySQL Database
* MySQL C API
* Ubuntu Linux
* GCC Compiler

## Database Schema

### Customers Table

* account_no (Primary Key)
* name
* password
* balance

### Transactions Table

* transaction_id (Primary Key)
* account_no
* type
* amount
* transaction_time

## How to Compile

```bash
gcc main.c -o banking $(mysql_config --cflags --libs)
```

## How to Run

```bash
./banking
```

## Functionalities Implemented

1. Account Creation
2. Login Authentication
3. View Accounts
4. Deposit Money
5. Withdraw Money
6. Balance Inquiry
7. Transaction History
8. Insufficient Balance Check

## Future Improvements

* Password Hashing
* Money Transfer Between Accounts
* Admin Dashboard
* GUI Interface
* Multi-file Project Structure

## Author

Tharun Kanna
