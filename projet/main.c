#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer *customer = malloc(sizeof(customer));

    updateCustomer(customer);

    displayCustomer(customer);

    saveCustomer(customer);

    return 0;
}
