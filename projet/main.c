#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer customer;
    constructCustomer(&customer);
    displayCustomer(&customer);
    saveCustomer(&customer);

    return 0;
}
