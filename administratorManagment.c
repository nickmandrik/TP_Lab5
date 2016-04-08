//
//  administratorManagment.c
//  BankSystem
//
//  Created by RubyKrong on 01.04.16.
//  Copyright © 2016 RubyKrong. All rights reserved.
//

#include <stdio.h>
#include "functions.h"

void insertInTable(sqlite3 *, char*, char*);
void selectFromTable(sqlite3 *, char*, char*);
void deleteFromTable(sqlite3*, char*, char*);
void doIt(char*, sqlite3*, char*);
void changeOverdraft (sqlite3*, char*, char*);
static int callback(void *, int , char **, char **);

void administratorManagment(sqlite3 *db, char* sql, char* zErrMsg)
{
    int choice = -1;
    
    while (choice < 0 || choice > 4)
    {
        printf("\n==========\nMAIN MENU\n==========\n");
        printf("1. Add client\n");
        printf("2. Print info about client\n");
        printf("3. Remove client\n");
        printf("4. Change available overdraft\n");
        printf("0. Exit\n");
        printf("Enter pount: ");
        scanf("%d", &choice);
        
        
        switch (choice)
        {
            case 0:
                break;
            case 1:
                insertInTable(db, sql, zErrMsg);
                break;
            case 2:
                selectFromTable(db, sql, zErrMsg);
                break;
            case 3:
                deleteFromTable(db, sql, zErrMsg);
                break;
            case 4:
                changeOverdraft(db, sql, zErrMsg);
                break;
            default:
                printf("Invalid parameter.");
                break;
        }
        
        choice = -1;
    }
}


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void changeOverdraft(sqlite3* db, char* sql, char* zErrMsg)
{
    
    
    
    printf("Enter login of change overdraft:\n");
    
    
    
    
    
    char ide[15];
    
    scanf("%s", ide);
    int ch = -1;
    printf("Available overdraft:\n");
    printf("1. True\n");
    printf("2. False\n");
    scanf("%d", &ch);
    
    switch(ch){
        case 1:
            
            
            
            sql = " UPDATE BANK_ACCOUNTS SET AVAILABLE_OVERDRAFT='true' WHERE LOGIN =  ";
            char str[100];
            str[0] = '\0';
            strcat(str, sql);
            strcat(str, "'");
            strcat(str, ide);
            strcat(str, "'");
            strcat(str, ";");
            doIt(str, db, zErrMsg);
            break;
        case 2:
            
            
            
            sql = " UPDATE BANK_ACCOUNTS SET AVAILABLE_OVERDRAFT='false' WHERE LOGIN =  ";
            char str1[100];
            str1[0] = '\0';
            strcat(str1, sql);
            strcat(str1, "'");
            strcat(str1, ide);
            strcat(str1, "'");
            strcat(str1, ";");
            doIt(str1, db, zErrMsg);
            break;
            
        default:
            printf("Invalid parameter.\n");
            break;
            
            
    }
    
    int rc = -1;
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
}


void insertInTable(sqlite3 * db, char* sql, char* zErrMsg)
{
    
    
    char firstname[15], lastname[15], login[15], NoPassport[15];
    printf ("\n=======INSERT=======\n");
    printf ("Enter 0 for cancel\n");
    
    printf ("Enter firstname: ");
    scanf ("%s", firstname);
    if (strcmp(firstname, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    
    printf ("Enter lastname: ");
    scanf ("%s", lastname);
    if (strcmp(lastname, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    
    printf ("Enter login: ");
    scanf ("%s", login);
    if (strcmp(login, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    
    printf ("Enter your № Passport: ");
    scanf ("%s", NoPassport);
    if (strcmp(NoPassport, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    
    
    
    sql = "INSERT INTO BANK_CLIENTS(firstName, lastName, login, NoPassport, numberAccounts) VALUES(";
    
    
    char str[300];
    strcat(str, sql);
    strcat(str, "'");
    strcat(str, firstname);
    strcat(str, "','");
    strcat(str, lastname);
    strcat(str, "','");
    strcat(str, login);
    strcat(str, "','");
    strcat(str, NoPassport);
    strcat(str, "','");
    strcat(str, "0");
    strcat(str, "');");
    printf("%s", str);
    
    
    int rc = -1;
    rc = sqlite3_exec(db, str, callback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK)
    {
        printf ("\nSQL Error!!! %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        
    }
    else
    {
        printf ("\nRecords is successfull add!\n");
        
    }
    
    
}


void selectFromTable(sqlite3* db, char* sql, char* zErrMsg)
{
    
    
    int choice = -1;
    
    printf("Choise a parameter of print:\n");
    printf("1. Login\n");
    printf("2. Firstname\n");
    printf("3. Lastname\n");
    printf("0. Cancel\n");
    scanf("%d", &choice);
    
    
    
    char ide[15];
    switch (choice) {
        case 1:
            printf("Enter Login: ");
            scanf("%s", ide);
            sql = "SELECT * FROM BANK_CLIENTS WHERE login = ";
            char str[100];
            str[0] = '\0';
            strcat(str, sql);
            strcat(str, "'");
            strcat(str, ide);
            strcat(str, "'");
            strcat(str, ";");
            doIt(str, db, zErrMsg);
            break;
            
        case 2:
            printf("Enter firstname: ");
            scanf("%s", ide);
            sql = "SELECT * FROM BANK_CLIENTS WHERE firstName = ";
            char str1[100];
            str1[0] = '\0';
            strcat(str1, sql);
            strcat(str1, "'");
            strcat(str1, ide);
            strcat(str1, "'");
            strcat(str1, ";");
            doIt(str1, db, zErrMsg);
            break;
            
        case 3:
            printf("Enter lastname: ");
            scanf("%s", ide);
            sql = "SELECT * FROM BANK_CLIENTS WHERE lastName = ";
            char str2[100];
            str2[0] = '\0';
            strcat(str2, sql);
            strcat(str2, "'");
            strcat(str2, ide);
            strcat(str2, "'");
            strcat(str2, ";");
            doIt(str2, db, zErrMsg);
            break;
            
            
        default:
            printf("Invalid parameter.\n");
            break;
    }
    
    
    
    
    int rc = -1;
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    
    
}


void deleteFromTable(sqlite3* db, char* sql, char* zErrMsg)
{
    int choice = -1;
    
    printf("Choise a parameter of deleting:\n");
    printf("1. Login\n");
    printf("2. Firstname\n");
    printf("3. Lastname\n");
    printf("0. Cancel\n");
    scanf("%d", &choice);
    
    
    
    char ide[15];
    switch (choice) {
            
        case 0:
            return;
            break;
        case 1:
            printf("Enter Login: ");
            scanf("%s", ide);
            sql = "DELETE FROM BANK_CLIENTS WHERE login = ";
            char str[100];
            str[0] = '\0';
            strcat(str, sql);
            strcat(str, ide);
            strcat(str, ";");
            doIt(str, db, zErrMsg);
            break;
            
        case 2:
            printf("Enter firstname: ");
            scanf("%s", ide);
            sql = "DELETE FROM BANK_CLIENTS WHERE firstName = ";
            char str1[100];
            str1[0] = '\0';
            strcat(str1, sql);
            strcat(str1, "'");
            strcat(str1, ide);
            strcat(str1, "'");
            strcat(str1, ";");
            doIt(str1, db, zErrMsg);
            break;
            
        case 3:
            printf("Enter lastname: ");
            scanf("%s", ide);
            sql = "DELETE FROM BANK_CLIENTS WHERE lastName = ";
            char str2[100];
            str2[0] = '\0';
            strcat(str2, sql);
            strcat(str2, "'");
            strcat(str2, ide);
            strcat(str2, "'");
            strcat(str2, ";");
            doIt(str2, db, zErrMsg);
            break;
            
            
        default:
            printf("Invalid parameter.\n");
            break;
            
            
    }
    
    
}

void doIt(char* str, sqlite3* db, char* zErrMsg)
{
    printf("%s\n", str);
    int rc = -1;
    rc = sqlite3_exec(db, str, callback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK)
    {
        printf ("SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        
    }
    else
    {
        printf ("Successfull");
        
    }
    
    
}
