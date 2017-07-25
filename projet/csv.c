#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "customer.h"
#include "account.h"
#include "csv.h"

const char *CUSTOMER_FILENAME = "data/customers.csv";
const char *ACCOUNT_FILENAME = "data/accounts.csv";
const char *FILENAME_TMP = "data/tmp.csv";

const char *HISTORY_PATH = "data/history/";
const char *BACKUP_PATH = "data/backup/";

Customer getCustomer(int id) {
    char *data = getRow(id, CUSTOMER_FILENAME);

    if (data == NULL) {
        Customer customer;
        customer.id = -1;
        return customer;
    }

    Customer *customer = buildCustomerFromCsv(data);
    free(data);

    return *customer;
}

Account getAccount(int id) {
    char *data = getRow(id, ACCOUNT_FILENAME);

    if (data == NULL) {
        Account account;
        account.id = -1;
        return account;
    }

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
    if(row == NULL){
        exit(EXIT_FAILURE);
    }

    char *rowId;
    while (fgets(row, 255, file)) {
        char rowCopy[512];
        strcpy(row, strtok(row, "\n")); // Remove endline
        strcpy(rowCopy, row);

        rowId = strtok(rowCopy, ";");
        rowId = cleanCsvColumn(rowId);
        if (atoi(rowId) == id) {
            fclose(file);
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
        if (row[strlen(row) - 1] == 10) {
            row[strlen(row) - 1] = '\0';
        }

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
    rename(FILENAME_TMP, filename);

    return 1;
}


int getLastId(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char row[512];
    char oldRow[512];
    while (fgets(row, 255, file)) {
        strcpy(oldRow, row);
    }

    if (strlen(oldRow) == 0) {
        fclose(file);
        return 0;
    }
    char *lastId = cleanCsvColumn(strtok(oldRow, ";"));

    fclose(file);
    return atoi(lastId) + 1;
}

char *cleanCsvColumn(char *string) {
    if (string[strlen(string) - 1] == 10) {
        string[strlen(string) - 2] = '\0'; // Remove last "
    } else {
        string[strlen(string) - 1] = '\0'; // Remove last "
    }
    string += 1; // Remove first "

    return string;
}

char *formatCustomerToCsv(Customer *customer) {
    char *data = malloc(sizeof(char) * 2000);
    if(data == NULL){
        exit(EXIT_FAILURE);
    }


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
    if(customer == NULL){
        exit(EXIT_FAILURE);
    }

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
    return searchRowsBySecondId(customerId, (char *) ACCOUNT_FILENAME);
}

char *searchHistoriesByCustomer(int customerId) {
    return searchRowsBySecondId(customerId, getHistoryFilename());
}

char *searchRowsBySecondId(int id, char *filename) {
    char *accountsIds = malloc(sizeof(char) * 512);
    if(accountsIds == NULL){
        exit(EXIT_FAILURE);
    }

    *accountsIds = '\0';

    FILE *file = fopen(filename, "r");
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

        if (atoi(rowCustomerId) == id) {
            strcat(accountsIds, rowId);
            strcat(accountsIds, ",");
        }
    }
    accountsIds[strlen(accountsIds) - 1] = '\0'; // Remove last ,

    fclose(file);
    return accountsIds;
}

char *formatAccountToCsv(Account *account) {
    char *data = malloc(sizeof(char) * 2000);
    if(data == NULL){
        exit(EXIT_FAILURE);
    }

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
    if(account == NULL){
        exit(EXIT_FAILURE);
    }

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
    if(filename == NULL){
        exit(EXIT_FAILURE);
    }

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

void displayHistory(int historyId) {
    char *data = getRow(historyId, getHistoryFilename());
    char *element;
    char *labels[] = {"History Id", "Customer Id", "Account Id", "Operation", "Montant"};
    int current = 0;

    element = strtok(data, ";");
    while (element != NULL) {
        printf("%s : %s\t\t | ", labels[current], cleanCsvColumn(element));
        current += 1;
        element = strtok(NULL, ";");
    }
    printf("\n");
}

void backupData(char *filename) {
    FILE *file = fopen(filename, "w+");
    printf("File : %s\n", filename);
    if (file != NULL) {
        backupFile((char *) CUSTOMER_FILENAME, file);
        backupFile((char *) ACCOUNT_FILENAME, file);

        fclose(file);
    }
}

void backupFile(char *filename, FILE *output) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fprintf(output, "##%s\n", filename);

        char row[512];
        while (fgets(row, 255, file)) {
            fprintf(output, "%s", row);
        }
        fclose(file);
    }
}

void importData(char *filename) {

    int step = 0;

    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char row[512];
        while (fgets(row, 255, file)) {
            if (row[0] == '#' && row[1] == '#') {
                step += 1;
                char *path = strtok(row, "##");
                path[strlen(path) - 1] = '\0'; // Remove new line
            } else {
                if (step == 1) {
                    Customer *cust = buildCustomerFromCsv(row);
                    saveCustomer(cust);
                } else if (step == 2) {
                    Account *account = buildAccountFromCsv(row);
                    saveAccount(account);
                }
            }
        }

        fclose(file);
    }

}

float getTotalAmountAccounts() {
    FILE *file = fopen(ACCOUNT_FILENAME, "r");
    if (file == NULL) {
        return 0;
    }

    float total = 0;

    char row[512];
    char *rowCopy;
    while (fgets(row, 255, file)) {
        strtok(row, ";");
        strtok(NULL, ";");
        rowCopy = strtok(NULL, ";");
        rowCopy = cleanCsvColumn(rowCopy);

        total += (float) atof(rowCopy);
    }

    fclose(file);
    return total;
}

float getTotalRateAmountAccounts() {
    FILE *file = fopen(ACCOUNT_FILENAME, "r");
    if (file == NULL) {
        return 0;
    }

    float total = 0;
    float balance;
    float rate;

    char row[512];
    char *tmp;
    while (fgets(row, 255, file)) {
        strtok(row, ";");
        strtok(NULL, ";");

        tmp = strtok(NULL, ";");
        balance = (float) atof(cleanCsvColumn(tmp));

        tmp = strtok(NULL, ";");
        rate = (float) atof(cleanCsvColumn(tmp));

        total += balance * rate;
    }

    fclose(file);
    return total;
}

void searchCustomer(char *name) {
    FILE *file = fopen(CUSTOMER_FILENAME, "r");
    if (file != NULL) {
        char row[512];
        char *tmp;

        while (fgets(row, 255, file)) {
            char rowCopy[512];
            strcpy(rowCopy, row);

            strtok(row, ";");
            tmp = strtok(NULL, ";");
            tmp = cleanCsvColumn(tmp);

            int limit = (int) strlen(tmp);
            if (strlen(name) < limit) {
                limit = (int) strlen(name);
            }

            int i;
            for (i = 0; i < limit; i++) {
                if (tolower(tmp[i]) != name[i]) {
                    break;
                }
            }

            if (i == limit) {
                Customer *customer = buildCustomerFromCsv(rowCopy);
                displayCustomer(customer);
            }

        }

        fclose(file);
    }
}