#include "functions.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


void percentTransfer(sqlite3* db, char* sql, char* zErrMsg) {
	int number = 0;
	int fee = 0;

	printf("Enter the number of current account\n"); // получаем ID текущего счёта
	scanf("%d", &number);
	/*присваиваем перемменной fee значение FEE текущего счёта, его затем обнуляем */



	printf("Enter the number of saving account\n"); // получаем ID сберегательного счёта
	scanf("%d", &number);
	UPDATE BANK_ACCOUNTS SET FEE += fee WHERE ID = number; // переводим проценты с текущего счёта на сберегательный

	int rc = -1;
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
}