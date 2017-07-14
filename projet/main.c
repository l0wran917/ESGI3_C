#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer *customer = malloc(sizeof(customer));

    constructCustomer(customer);
    displayCustomer(customer);
    saveCustomer(customer);

    free(customer);
    return 0;
}
