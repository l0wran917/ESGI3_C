#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer customer;
    customer = getCustomer(8);
    displayAccountsByCustomer(customer.id);

    return 0;
}
