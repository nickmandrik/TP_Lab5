//
//  userAuthorization.c
//  BankSystem
//
//  Created by Admin on 01.04.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

int authorization();
char type[2];
char loginK[50];
static char loginClient[50];

int userAuthorization(sqlite3* db, char* sql, char* zErrMsg)
{
    printf("Hello, user! Now login into the system to continue.\n\n");
    int rk = 1;
    while(rk == 1)
    {
        rk = authorization(db, sql, zErrMsg);
        char sel[50];
        while(rk == 1 && (strcmp(sel, "Y") != 0 || strcmp(sel, "N") != 0))
        {
            printf("Try again(Y) or exit program(N): ");
            scanf("%s", sel);
            printf("\n");
            if(strcmp(sel, "N") == 0)
            {
                return -1;
            }
            if(strcmp(sel, "Y") == 0)
            {
                break;
            }
        }
    }
    loginClient[0] = '\0';
    strcat(loginClient, loginK);
    return atoi(type);
}

char passw[50];
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    passw[0] = '\0';
    strcat(passw, argv[1]);
    type[0] = argv[2][0];
    return 0;
}


int authorization(sqlite3* db, char* sql, char* zErrMsg)
{
    char password[50];
    printf ("Enter login: ");
    scanf ("%s", loginK);
    printf ("Enter password: ");
    scanf ("%s", password);
    
    sql = "SELECT * FROM BANK_USERS WHERE LOGIN = '";
    char str[100];
    str[0] = '\0';
    strcat(str, sql);
    strcat(str, loginK);
    strcat(str, "';");
    
    int rc = -1;
    rc = sqlite3_exec(db, str, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK || strcmp(password, passw) != 0)
    {
        printf ("Login or password failed.\n");
        sqlite3_free(zErrMsg);
        return 1;
    }
    return 0;
}

char* getLogin()
{
    return loginClient;
}

