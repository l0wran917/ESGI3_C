#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "account.h"
#include "csv.h"

const char *CUSTOMER_FILENAME = "../data/customers.csv";
const char *ACCOUNT_FILENAME = "../data/accounts.csv";
const char *FILENAME_TMP = "../data/tmp.csv";

Customer *getCustomer(int id) {
    FILE *file = fopen(CUSTOMER_FILENAME, "a+");
    if (file == NULL) {
        return NULL;
    }

    char row[512];
    char *rowId;
    while (fgets(row, 255, file)) {
        char rowCopy[512];
        strcpy(row, strtok(row, "\n")); // Remove endline
        strcpy(rowCopy, row);

        rowId = strtok(rowCopy, ";");
        rowId = cleanCsvColumn(rowId);
        if (atoi(rowId) == id) {
            return buildCustomerFromCsv(row);
        }
    }

    fclose(file);
    return NULL;
}

int saveCustomer(Customer *customer) {
    int isNew = 0;
    if (customer->id == NULL) {
        isNew = 1;
        customer->id = getLastId(CUSTOMER_FILENAME);
    }

    char *data = formatCustomerToCsv(*customer);
    saveRow(customer->id, data, CUSTOMER_FILENAME);

    free(data);
    return 1;
}

int saveAccount(Account *account) {

}

int saveRow(int id, char *data, const char *filename) {
    FILE *file = fopen(CUSTOMER_FILENAME, "a+");
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

    if(saved == 0){
        fputs(data, fileTmp);
    }

    fclose(fileTmp);
    fclose(file);
    remove(CUSTOMER_FILENAME);
    rename(FILENAME_TMP, CUSTOMER_FILENAME);

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
    rename(FILENAME_TMP, CUSTOMER_FILENAME);

    return 1;
}

char *formatCustomerToCsv(Customer customer) {
    char *data = malloc(sizeof(char) * 2000);

    sprintf(data, "\"%d\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            customer.id,
            customer.lastname,
            customer.firstname,
            customer.profession,
            customer.phone);

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

char *cleanCsvColumn(char *string) {
    string += 1; // Remove first "
    string[strlen(string) - 1] = '\0'; // Remove last "

    return string;
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