#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "customer.h"
#include "csv.h"

int main() {
    Customer customer;
    Account account;

    customer.customerId = 1;
    customer.lastname = "Test";
    customer.firstname = "Oui";
    customer.profession = "Ok";
    customer.phone = "0102030405";

    saveCustomer(customer);

    return 0;
}
