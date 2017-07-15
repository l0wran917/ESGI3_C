#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "customer.h"
#include "account.h"
#include "csv.h"

const char *CUSTOMER_FILENAME = "../data/customers.csv";
const char *ACCOUNT_FILENAME = "../data/accounts.csv";
const char *FILENAME_TMP = "../data/tmp.csv";

const char *HISTORY_PATH = "../data/history/";

Customer getCustomer(int id) {
    char *data = getRow(id, CUSTOMER_FILENAME);
    Customer *customer = buildCustomerFromCsv(data);
    free(data);

    return *customer;
}

Account getAccount(int id) {
    char *data = getRow(id, ACCOUNT_FILENAME);

    Account *account = buildAccountFromCsv(data);
    free(data);

    return *account;
}

char *getRow(int id, const char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        return NULL;
    }

    char *row = malloc(sizeof(char) * 512);
    char *rowId;
    while (fgets(row, 255, file)) {
        char rowCopy[512];
        strcpy(row, strtok(row, "\n")); // Remove endline
        strcpy(rowCopy, row);

        rowId = strtok(rowCopy, ";");
        rowId = cleanCsvColumn(rowId);
        if (atoi(rowId) == id) {
            return row;
        }
    }

    fclose(file);
    return NULL;
}


int saveCustomer(Customer *customer) {
    if (customer->id < 0) {
        customer->id = getLastId(CUSTOMER_FILENAME);
    }

    char *data = formatCustomerToCsv(customer);
    saveRow(customer->id, data, CUSTOMER_FILENAME);

    free(data);
    return 1;
}

int saveAccount(Account *account) {
    if (account->id < 0) {
        account->id = getLastId(ACCOUNT_FILENAME);
    }

    char *data = formatAccountToCsv(account);
    saveRow(account->id, data, ACCOUNT_FILENAME);

    free(data);
    return 1;
}

int saveRow(int id, char *data, const char *filename) {
    FILE *file = fopen(filename, "a+");
    FILE *fileTmp = fopen(FILENAME_TMP, "w+");

    if (file == NULL || fileTmp == NULL) {
        return 0;
    }

    char row[512];
    char *rowId;
    int saved = 0;
    while (fgets(row, 255, file)) {
        char rowCopy[512];
        strcpy(row, strtok(row, "\n")); // Remove endline
        strcpy(rowCopy, row);

        rowId = strtok(rowCopy, ";");
        rowId = cleanCsvColumn(rowId);

        if (atoi(rowId) == id) {
            fputs(data, fileTmp);
            saved = 1;
        } else {
            fputs(row, fileTmp);
            fputs("\n", fileTmp);
        }
    }

    if (saved == 0) {
        fputs(data, fileTmp);
    }

    fclose(fileTmp);
    fclose(file);
    remove(filename);
    rename(FILENAME_TMP, filename);

    return 1;
}

int deleteCustomer(int id) {
    return deleteRow(id, CUSTOMER_FILENAME);
}

int deleteAccount(int id) {
    return deleteRow(id, ACCOUNT_FILENAME);
}

int deleteRow(int id, const char *filename) {
    FILE *file = fopen(filename, "a+");
    FILE *fileTmp = fopen(FILENAME_TMP, "w+");

    if (file == NULL || fileTmp == NULL) {
        return 0;
    }

    char row[512];
    char *rowId;

    while (fgets(row, 255, file)) {
        char rowCopy[512];
        strcpy(row, strtok(row, "\n")); // Remove endline
        strcpy(rowCopy, row);

        rowId = strtok(rowCopy, ";");
        rowId = cleanCsvColumn(rowId);

        if (atoi(rowId) != id) {
            fputs(row, fileTmp);
            fputs("\n", fileTmp);
        }
    }

    fclose(fileTmp);
    fclose(file);
    remove(filename);
    rename(FILENAME_TMP, ACCOUNT_FILENAME);

    return 1;
}


int getLastId(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    char row[512];
    char oldRow[512];
    while (fgets(row, 255, file)) {
        strcpy(oldRow, row);
    }

    char *lastId = cleanCsvColumn(strtok(oldRow, ";"));

    return atoi(lastId) + 1;
}

char *cleanCsvColumn(char *string) {
    string += 1; // Remove first "
    string[strlen(string) - 1] = '\0'; // Remove last "

    return string;
}

char *formatCustomerToCsv(Customer *customer) {
    char *data = malloc(sizeof(char) * 2000);

    sprintf(data, "\"%d\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            customer->id,
            customer->lastname,
            customer->firstname,
            customer->profession,
            customer->phone);

    return data;
}

Customer *buildCustomerFromCsv(char *data) {
    char *element = NULL;
    Customer *customer = malloc(sizeof(Customer));

    element = cleanCsvColumn(strtok(data, ";"));
    customer->id = atoi(element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    strcpy(customer->lastname, element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    strcpy(customer->firstname, element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    strcpy(customer->profession, element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    strcpy(customer->phone, element);

    return customer;
}

char *searchAccountsByCustomer(int customerId) {
    char *accountsIds = malloc(sizeof(char) * 512);
    // TODO : check malloc != NULL
    *accountsIds = '\0';

    FILE *file = fopen(ACCOUNT_FILENAME, "r");
    if (file == NULL) {
        return NULL;
    }

    char row[512];
    char *rowId;
    char *rowCustomerId;
    while (fgets(row, 255, file)) {
        char rowCopy[512];
        strcpy(row, strtok(row, "\n")); // Remove endline
        strcpy(rowCopy, row);

        rowId = strtok(rowCopy, ";");
        rowId = cleanCsvColumn(rowId);
        rowCustomerId = strtok(NULL, ";");
        rowCustomerId = cleanCsvColumn(rowCustomerId);

        if (atoi(rowCustomerId) == customerId) {
            strcat(accountsIds, rowId);
            strcat(accountsIds, ",");
        }
    }
    accountsIds[strlen(accountsIds) - 1] = '\0'; // Remove last ,

    return accountsIds;
}

char *formatAccountToCsv(Account *account) {
    char *data = malloc(sizeof(char) * 2000);

    sprintf(data, "\"%d\";\"%d\";\"%f\";\"%f\";\"%d\"\n",
            account->id,
            account->customerId,
            account->balance,
            account->rate,
            account->minimalTime);

    return data;
}

Account *buildAccountFromCsv(char *data) {
    char *element = NULL;
    Account *account = malloc(sizeof(Account));

    element = cleanCsvColumn(strtok(data, ";"));
    account->id = atoi(element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    account->customerId = atoi(element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    account->balance = (float) atof(element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    account->rate = (float) atof(element);

    element = cleanCsvColumn(strtok(NULL, ";"));
    account->minimalTime = atoi(element);


    return account;
}

void addHistory(int customerId, int accountId, char *label, float amount) {
    char *filename = getHistoryFilename();

    FILE *file = fopen(filename, "a+");
    if (file != NULL) {
        int id = getLastId(filename);

        fprintf(file, "\"%d\";\"%d\";\"%d\";\"%s\";\"%f\"\n", id, customerId, accountId, label, amount);

        fclose(file);
    } else {
        exit(4);
    }

    free(filename);
}

char *getHistoryFilename() {
    char *filename = malloc(sizeof(char) * 255);
    *filename = '\0';

    time_t now;
    time(&now);
    struct tm *now_tm;
    now_tm = localtime(&now);

    char date[50];
    strftime(date, 50, "%Y%m%d", now_tm);

    strcat(filename, HISTORY_PATH);
    strcat(filename, date);
    strcat(filename, ".csv");

    return filename;
}