#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

sqlite3 *db;
char *zErrMsg = 0;
int rc = 0;
char* sql;

int showHelpList();
int init();
void exitProgram();


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void doIt1(char* str, sqlite3* db, char* errMsg)
{
	printf("%s\n", str);
	int rc = -1;
	rc = sqlite3_exec(db, str, callback, 0, &errMsg);

	if (rc != SQLITE_OK)
	{
		printf("SQL Error!!! %s\n", errMsg);
		sqlite3_free(errMsg);
	}
	else
	{
		printf("Records is successfull printed!");
	}
}

int showHelpList() {
	int choice = 0;
	do {
		system("cls");
		printf( "\t\t\t\tWelcome!\n" );
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
	rc = sqlite3_open("/Users/rubykrong/Desktop/bank3.db", &db);

	if (rc == 1)
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
		return 1;
	}
	else
	{
		printf("Opened database successfully!\n");
		return 0;
	}
}

int main() {
	if (init() == 1)
	{
		printf("\nEmergency closing.\n");
		return 1;
	}

	int buf = 0;
	while (buf != 1)
	{
		int tmp = showHelpList();
		switch (tmp)
		{			
		case 1: depositMoney(db, sql, zErrMsg); 
			break;
		case 2: moneyTransfer(db, sql, zErrMsg); 
			break;
		case 3: percentTransfer(db, sql, zErrMsg); 
			break;
		case 4: exitProgram(); 
			return;
		}
	}

	return 0;
}

void exitProgram()
{
	sqlite3_close(db);
}