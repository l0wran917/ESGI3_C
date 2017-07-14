#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {
    /*
    Customer customer = getCustomer(7);
    displayCustomer(&customer);

    Account account;
    createAccount(customer.id, &account);
    displayAccount(&account);
    saveAccount(&account);
    */
    displayAccountsByCustomer(7);

    return 0;
}
