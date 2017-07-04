#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
#include "account.h"
#include "csv.h"

const char *CUSTOMER_FILENAME = "../data/customers.csv";

char* getCsvCustomerHeader(){
    return "id;firstname;lastname\n";
}

int saveCustomer(Customer customer) {
    FILE *file = fopen(CUSTOMER_FILENAME, "a+");
    if (file == NULL) {
        return 0;
    }
    fputs(getCsvCustomerHeader(), file);
    fputs("TEST", file);

    printf("#%s#\n", CUSTOMER_FILENAME);

    fclose(file);
    return 1;
}