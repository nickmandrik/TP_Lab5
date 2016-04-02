//
//  clientManagment.c
//  BankSystem
//
//  Created by Admin on 30.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

void showMenu();
char loginClient[50];
void clientManagment(char* loginCl, sqlite3* db, char* sql, char* zErrMsg)
{
    loginClient[0] = '\0';
    strcat(loginClient, loginCl);
    showMenu(db, sql, zErrMsg);
}

void exitManage(sqlite3* db)
{
    sqlite3_close(db);
}
void creditMoney(sqlite3*, char*, char*);
void debitMoney(sqlite3*, char*, char*);
void checkBalance(sqlite3*, char*, char*);
void getOverdraft(sqlite3*, char*, char*);
void payForFee(sqlite3*, char*, char*);

void showMenu(sqlite3* db, char* sql, char* zErrMsg)
{
    char choice = ' ';
    
    while (choice == ' ')
    {
        printf("\n\n        Menu\n______________________\n");
        printf("1. Credit money\n");
        printf("2. Debit money\n");
        printf("3. Check balance\n");
        printf("4. Get overdraft\n");
        printf("5. Pay for fee\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", &choice);
        
        switch (choice)
        {
            case '0':
                exitManage(db);
                return;
            case '1':
                creditMoney(db, sql, zErrMsg);
                break;
            case '2':
                debitMoney(db, sql, zErrMsg);
                break;
            case '3':
                checkBalance(db, sql, zErrMsg);
                break;
            case '4':
                break;
            case '5':
                break;
            default:
                printf("Invalid parameter.");
                break;
                
        }
        
        choice = ' ';
    }

}

char account[50];
char moneyOnID[50];
static int callback1(void *NotUsed, int argc, char **argv, char **azColName)
{
    account[0] = '\0';
    strcat(account, argv[2]);
    moneyOnID[0] = '\0';
    strcat(moneyOnID, argv[1]);
    return 0;
}

void creditMoney(sqlite3* db, char* sql, char* zErrMsg)
{
    char id[50];
    printf("Enter the ID you want to credit money: ");
    scanf("%s", id);
    
    sql = "SELECT * FROM BANK_ACCOUNTS WHERE ID = '";
    char str[100];
    str[0] = '\0';
    strcat(str, sql);
    strcat(str, id);
    strcat(str, "';");
    
    int rc = -1;
    rc = sqlite3_exec(db, str, callback1, 0, &zErrMsg);
    if (rc != SQLITE_OK || strcmp(account, "") == 0)
    {
        printf ("ID didn't exist.\n");
        sqlite3_free(zErrMsg);
        return;
    }

    char choice[50];
    int money;
    char stk[50];
    printf("Enter amount of money you want to credit: ");
    scanf("%s", stk);
    money = atoi(stk);
    choice[0] = ' ';
    while(strcmp(choice, "N") != 0 || strcmp(choice, "Y") != 0)
    {
        printf("Do you want to credit %d$ on login %s?(Y/N) ", money, account);
        scanf("%s", choice);
        if(strcmp(choice, "N") == 0)
        {
            printf("Operation cancled.\n");
            return;
        }
        if(strcmp(choice, "Y") == 0)
        {
            break;
        }

    }

    sql = "UPDATE BANK_ACCOUNTS SET BALANCE=";
    char stq[100];
    stq[0] = '\0';
    strcat(stq, sql);
    int mon = atoi(moneyOnID);
    char moN[50];
    sprintf(moN, "%d", mon + money);
    strcat(stq, moN);
    strcat(stq, " WHERE ID = '");
    strcat(stq, id);
    strcat(stq, "';");
    printf("%s\n", stq);
    rc = -1;
    rc = sqlite3_exec(db, str, callback1, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf ("Problem with system. Please connect with our administrator.\n");
        sqlite3_free(zErrMsg);
        return;
    }
    printf("Operation successful!\n");
}

char logi[50];
static int callback2(void *NotUsed, int argc, char **argv, char **azColName){
    logi[0] = '\0';
    strcat(logi, argv[2]);
    return 0;
}


void debitMoney(sqlite3* db, char* sql, char* zErrMsg)
{
    char id[50];
    printf("Enter the ID you want to debit money: ");
    scanf("%s", id);
    
    sql = "SELECT * FROM BANK_ACCOUNTS WHERE ID = '";
    char str[100];
    str[0] = '\0';
    strcat(str, sql);
    strcat(str, id);
    strcat(str, "';");
    
    int rc = -1;
    rc = sqlite3_exec(db, str, callback2, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf ("ID didn't exist.\n");
        return;
    }
    if (strcmp(logi, loginClient) != 0)
    {
        printf ("This is not your ID.\n");
        return;
    }

    
    char choice[50];
    int money;
    char stkb[50];
    printf("Enter amount of money you want to debit: ");
    scanf("%s", stkb);
    money = atoi(stkb);
    choice[0] = ' ';
    int mon = atoi(moneyOnID);
    if(mon - money < 0)
    {
        printf("No such money on the account.\n");
        return;
    }
    while(strcmp(choice, "N") != 0 || strcmp(choice, "Y") != 0)
    {
        printf("Do you want to debit %d$ for ID %s?(Y/N) ", money, id);
        scanf("%s", choice);
        if(strcmp(choice, "N") == 0)
        {
            printf("Operation cancled.\n");
            return;
        }
        if(strcmp(choice, "Y") == 0)
        {
            break;
        }
        
    }
    
    sql = "UPDATE BANK_ACCOUNTS SET BALANCE=";
    char stq[100];
    stq[0] = '\0';
    strcat(stq, sql);
    char moN[50];
    sprintf(moN, "%d", mon - money);
    strcat(stq, moN);
    strcat(stq, " WHERE ID =");
    strcat(stq, id);
    strcat(stq, ";");
    rc = -1;
    rc = sqlite3_exec(db, str, callback1, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf ("Problem with system. Please connect with our administrator.\n");
        return;
    }
    printf("Operation successful!\n");
}

static int callback3(void *NotUsed, int argc, char **argv, char **azColName){
    printf("ID: %s, balance = %s.\n", argv[0], argv[1]);
    printf("\n");
    return 0;
}

void checkBalance(sqlite3* db, char* sql, char* zErrMsg)
{
    sql = "SELECT * FROM BANK_ACCOUNTS WHERE LOGIN = '";
    char stq[100];
    stq[0] = '\0';
    strcat(stq, sql);
    strcat(stq, loginClient);
    strcat(stq, "';");
    int rq = -1;
    rq = sqlite3_exec(db, stq, callback3, 0, &zErrMsg);
    if (rq != SQLITE_OK)
    {
        printf ("Problem with system. Please connect with our administrator.\n");
        sqlite3_free(zErrMsg);
        return;
    }
    printf("Operation successful!\n");

}
