#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "customer.h"
#include "csv.h"


int main() {

    Customer customer;
    customer = getCustomer(8);

    Account account;
    account = getAccount(4);
    depositAccount(account, 15);
    withdrawAccount(account, 10);

    Account account2;
    account2 = getAccount(1);
    transferringAccount(account, account2, 5);

    displayAccountsByCustomer(&customer);

    return 0;
}
