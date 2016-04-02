//
//  main.c
//  BankSystem
//
//  Created by Admin on 30.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <stdio.h>
#include "functions.h"

sqlite3 *db;
char *zErrMsg = 0;
int rc = 0;
char* sql;

int authorization();
int init();
void exitProgram();


int main(int argc, const char * argv[])
{
    if (init() == 1)
    {
        printf("Application closing.\n");
        return 1;
    }
    
    int sel = -1;
    sel = userAuthorization(db, sql, zErrMsg);
    if(sel != -1)
    {
        printf("\nSuccess! You entered into the system as ");
    }
    switch (sel)
    {
        case 0:
            printf("Administrator.\n\n");
            administratorManagment(db, sql, zErrMsg);
            break;
        case 1:
            printf("Client Suppoter.\n\n");
            break;
        case 2:
            printf("Client.\n\n");
            clientManagment(getLogin(), db, sql, zErrMsg);
            break;
        default:
            printf("Unsuccess. The login failed =(\n\n");
    }
    exitProgram();
    return 0;
}

void exitProgram()
{
    sqlite3_close(db);
    return;
}

int init()
{
    // open database
    rc = sqlite3_open("/Users/admin/lab5/bank.db", &db);;
    if (rc == SQLITE_OK)
    {
        return 0;
    }
    else
    {
        printf("Can't open database bank.db: %s\n", sqlite3_errmsg(db));
        return 1;
    }
}
