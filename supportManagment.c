#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include <sqlite3.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

sqlite3 *db;
char *zErrMsg = 0;
int rc = 0;
char* sql;


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int showHelpList() {
	int choice = 0;
	do {
		system("cls");
		printf( "  Select action:\n" );
		printf( "1.Deposit money\n" );
		printf( "2.Transfer of fixed assets from current to savings account\n" );
		printf( "3.Transfer of accrued interest\n" );
		printf( "4.Exit\n" );
		printf( "Your choice: " );
		scanf( "%d", &choice );
		if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
			return choice;
		printf( "Error! Repeat enter\n" );
		system("pause");
	} while (choice < 0 || choice > 4);
}

int init()
{
	// open database
	//rc = sqlite3_open("/Users/Aleksey/Desktop/bank3.db", &db);

	if (rc == 1)
	{
	//	printf("Can't open database: %s\n", sqlite3_errmsg(db));
		return 1;
	}
	else
	{
		printf("Opened database successfully!\n");
		return 0;
	}
}
void moneyTransfer() {
	int number = 0;
	int money = 0;

	printf("Enter the number of savings account\n"); // получаем ID сберегательного счёта
	scanf("%d", &number);

	printf("Enter the sum for transfer\n"); 
	scanf("%d", &money);
	//sql = "UPDATE BANK_ACCOUNTS SET BALANCE += money WHERE ID = number"; 
	//int rc = -1;
	//rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

}

void percentTransfer() {
	int number = 0;
	int fee = 0;

	printf("Enter the number of current account\n"); // получаем ID текущего счёта
	scanf("%d", &number);

	printf("Enter the number of saving account\n"); // получаем ID сберегательного счёта
	scanf("%d", &number);
	//sql = "UPDATE BANK_ACCOUNTS SET FEE += fee WHERE ID = number";
	//int rc = -1;
	//rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
}

void depositMoney() {
	int number = 0;
	int money = 0;

	printf("Enter account number\n");
	scanf("%d", &number);
	printf("Enter credited amount\n");
	scanf("%d", &money);
	//sql = "UPDATE BANK_ACCOUNTS SET BALANCE += money WHERE ID = number";
	//int rc = -1;
	//rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
}

void supportManagment() {
	int buf = 0;
	while (buf != 1)
	{
		int tmp = showHelpList();
		switch (tmp)
		{			
		case 1: depositMoney(); 
			break;
		case 2: moneyTransfer(); 
			break;
		case 3: percentTransfer(); 
			break;
		case 4: 
			return;
		}
	}

	return 0;
}