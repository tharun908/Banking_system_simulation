#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

MYSQL* connectDB() {
    MYSQL *conn = mysql_init(NULL);

    if (mysql_real_connect(
            conn,
            "localhost",
            "bankuser",
            "Bank@1234",
            "banking_system",
            0,
            NULL,
            0) == NULL) {

        printf("Database Connection Failed!\n");
        exit(1);
    }

    return conn;
}
void createAccount(MYSQL *conn) {

    char name[100];
    char password[100];
    float balance;

    printf("\nEnter Name: ");
    scanf("%s", name);

    printf("Enter Password: ");
    scanf("%s", password);

    printf("Enter Initial Deposit: ");
    scanf("%f", &balance);

    char query[500];

    sprintf(query,
            "INSERT INTO customers(name,password,balance) "
            "VALUES('%s','%s',%.2f)",
            name,
            password,
            balance);

    if(mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
    }
    else {
        printf("Account Created Successfully!\n");
    }
}void viewAccounts(MYSQL *conn) {

    MYSQL_RES *result;
    MYSQL_ROW row;

    if(mysql_query(conn, "SELECT * FROM customers")) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    result = mysql_store_result(conn);

    printf("\n-------------------------------------------------\n");
    printf("Acc No\tName\tPassword\tBalance\n");
    printf("-------------------------------------------------\n");

    while((row = mysql_fetch_row(result))) {
        printf("%s\t%s\t%s\t\t%s\n",
               row[0],
               row[1],
               row[2],
               row[3]);
    }

    mysql_free_result(result);
}void deposit(MYSQL *conn) {

    int account_no;
    float amount;

    printf("\nEnter Account Number: ");
    scanf("%d", &account_no);

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    char query[300];

    sprintf(query,
            "UPDATE customers "
            "SET balance = balance + %.2f "
            "WHERE account_no = %d",
            amount,
            account_no);

    if(mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
    }
    else {
        printf("Amount Deposited Successfully!\n");
char transQuery[300];

sprintf(transQuery,
        "INSERT INTO transactions(account_no,type,amount) "
        "VALUES(%d,'DEPOSIT',%.2f)",
        account_no,
        amount);

mysql_query(conn, transQuery);

    }
}
void withdraw(MYSQL *conn) {

    int account_no;
    float amount;
    char query[300];

    printf("\nEnter Account Number: ");
    scanf("%d", &account_no);

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    sprintf(query,
            "SELECT balance FROM customers WHERE account_no=%d",
            account_no);

    if(mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    if(row == NULL) {
        printf("Account Not Found!\n");
        mysql_free_result(result);
        return;
    }

    float currentBalance = atof(row[0]);

    mysql_free_result(result);

    if(amount > currentBalance) {
        printf("Insufficient Balance!\n");
        return;
    }

    sprintf(query,
            "UPDATE customers "
            "SET balance = balance - %.2f "
            "WHERE account_no = %d",
            amount,
            account_no);

    if(mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
    }
    else {
        printf("Amount Withdrawn Successfully!\n");
char transQuery[300];

sprintf(transQuery,
        "INSERT INTO transactions(account_no,type,amount) "
        "VALUES(%d,'WITHDRAW',%.2f)",
        account_no,
        amount);

mysql_query(conn, transQuery);
    }
}

 void checkBalance(MYSQL *conn) {

    int account_no;

    printf("\nEnter Account Number: ");
    scanf("%d", &account_no);

    char query[200];

    sprintf(query,
            "SELECT balance FROM customers WHERE account_no=%d",
            account_no);

    if(mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    if(row) {
        printf("Current Balance: %s\n", row[0]);
    }
    else {
        printf("Account Not Found!\n");
    }

    mysql_free_result(result);
}int login(MYSQL *conn) {

    int account_no;
    char password[100];
    char query[300];

    printf("\nEnter Account Number: ");
    scanf("%d", &account_no);

    printf("Enter Password: ");
    scanf("%s", password);

    sprintf(query,
            "SELECT * FROM customers "
            "WHERE account_no=%d AND password='%s'",
            account_no,
            password);

    if(mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if(mysql_num_rows(result) > 0) {
        printf("Login Successful!\n");
        mysql_free_result(result);
        return 1;
    }

    printf("Invalid Credentials!\n");

    mysql_free_result(result);
    return 0;
}void viewTransactions(MYSQL *conn) {

    int account_no;

    printf("\nEnter Account Number: ");
    scanf("%d", &account_no);

    char query[300];

    sprintf(query,
            "SELECT transaction_id,type,amount,transaction_time "
            "FROM transactions "
            "WHERE account_no=%d",
            account_no);

    if(mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    printf("\n------------------------------------------------------------\n");
    printf("ID\tType\t\tAmount\t\tTime\n");
    printf("------------------------------------------------------------\n");

    while((row = mysql_fetch_row(result))) {
        printf("%s\t%s\t\t%s\t\t%s\n",
               row[0],
               row[1],
               row[2],
               row[3]);
    }

    mysql_free_result(result);
}
int main() {

    MYSQL *conn = connectDB();
    int loggedIn=0;
    int choice;
 
    while(1) {

        printf("\n===== BANKING SYSTEM =====\n");
        printf("\n===== BANKING SYSTEM =====\n");
printf("1. Create Account\n");
printf("2. Login\n");
printf("3. View Accounts\n");
printf("4. Deposit\n");
printf("5. Withdraw\n");
printf("6. Check Balance\n");
printf("7.Transaction History\n");
printf("8. Exit\n");
printf("Enter choice: ");

        scanf("%d", &choice);

        switch(choice) {

            case 1:
    createAccount(conn);
    break;  
            case 2: 
           loggedIn = login(conn);
            break;

            case 3:
              viewAccounts(conn);
              break;
            case 4:
             if(loggedIn)
              deposit(conn);
              else
               printf("Please Login First!\n");
               break;
            case 5:
            if(loggedIn)
             withdraw(conn);
             else
              printf("Please Login First!\n");
               break;
           case 6:
               if(loggedIn)
                checkBalance(conn);
               else 
                printf("please Login First!\n");
                break;
           case 7:
                if(loggedIn)
                   viewTransactions(conn);
                else 
                   printf("please Login First!\n");
            case 8:
                mysql_close(conn);
                printf("Goodbye!\n");
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}
       
