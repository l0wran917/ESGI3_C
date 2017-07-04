#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
#include "csv.h"

const char *CUSTOMER_FILENAME = "../data/customers.csv";

char *getCsvCustomerHeader() {
    return "id;firstname;lastname\n";
}

char* getCustomerDataFormatted(Customer customer) {
    char* data = malloc(sizeof(char) * 2000);

    sprintf(data, "\"%d\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            customer.customerId,
            customer.lastname,
            customer.firstname,
            customer.profession,
            customer.phone);

    return data;
}

int saveCustomer(Customer customer) {
    FILE *file = fopen(CUSTOMER_FILENAME, "a+");
    if (file == NULL) {
        return 0;
    }

    char* data = getCustomerDataFormatted(customer);
    fputs(data, file);

    free(data);
    fclose(file);
    return 1;
}