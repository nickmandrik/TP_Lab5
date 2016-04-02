#ifndef functions_h
#define functions_h
#include <sqlite3.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void depositMoney(sqlite3 *, char*, char*);
void moneyTransfer(sqlite3*, char*, char*);
void percentTransfer(sqlite3*, char*, char*);

void doIt(char*, sqlite3*, char*);

static int callback(void *, int, char **, char **);

#endif