#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer *customer;
    Account account;

    //saveCustomer(customer);
    customer = getCustomer(1);
    displayCustomer(customer);

    return 0;
}
