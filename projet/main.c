#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer customer;
    createCustomer(&customer);
    displayCustomer(&customer);

    Account account;
    createAccount(customer.id, &account);
    displayAccount(&account);

    return 0;
}
