//
//  functions.h
//  workWithDB
//
//  Created by Admin on 28.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <string.h>
#include <sqlite3.h>

int userAuthorization(sqlite3 *, char*, char*);
void clientManagment(char*, sqlite3 *, char*, char*);
void administratorManagment(sqlite3 *, char*, char*);
char* getLogin(void);
#endif

