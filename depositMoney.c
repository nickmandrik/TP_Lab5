#include "functions.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


/* Пользователь вводит номер счёта и сумму, которую хочет прибавить к балансу данного счёта*/
void depositMoney(sqlite3* db, char* sql, char* zErrMsg) {
	int number = 0;
	int money = 0;

	printf("Enter account number\n");
	scanf("%d", &number);
	printf("Enter credited amount\n");
	scanf("%d", &money);
	UPDATE BANK_ACCOUNTS SET BALANCE += money WHERE ID = number;

	int rc = -1;
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
}