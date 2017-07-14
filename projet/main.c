#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer customer;
    //constructCustomer(&customer);
    customer = *getCustomer(2);
    strcpy(customer.firstname, "ok");
    displayCustomer(&customer);
    saveCustomer(&customer);

    return 0;
}
