#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "csv.h"

const char *CUSTOMER_FILENAME = "../data/customers.csv";

char *getCsvCustomerHeader() {
    return "id;firstname;lastname\n";
}

char *getCustomerDataFormatted(Customer customer) {
    char *data = malloc(sizeof(char) * 2000);

    sprintf(data, "\"%d\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            customer.id,
            customer.lastname,
            customer.firstname,
            customer.profession,
            customer.phone);

    return data;
}

int saveCustomer(Customer *customer) {
    FILE *file = fopen(CUSTOMER_FILENAME, "a+");
    if (file == NULL) {
        return 0;
    }

    int isNew = 0;
    if (customer->id == NULL) {
        isNew = 1;
        customer->id = getLastCustomerId();
    }

    char *data = getCustomerDataFormatted(*customer);

    if (isNew == 1) {
        fputs(data, file);
    }

    free(data);
    fclose(file);
    return 1;
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

char *cleanCsvColumn(char *string) {
    string += 1; // Remove first "
    string[strlen(string) - 1] = '\0'; // Remove last "

    return string;
}

int getLastCustomerId() {
    FILE *file = fopen(CUSTOMER_FILENAME, "r");
    if (file == NULL) {
        return NULL;
    }

    char row[512];
    char oldRow[512];
    while (fgets(row, 255, file)) {
        strcpy(oldRow, row);
    }
    printf("Last : %s\n", oldRow);
    char *lastId = cleanCsvColumn(strtok(oldRow, ";"));

    return atoi(lastId) + 1;
}