#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "account.h"
#include "csv.h"

void createAccount(int idCustomer, Account *account) {
    account->id = -1;
    account->customerId = idCustomer;

    printf("Veuillez renseigner le montant de depart present sur le compte :\n");
    scanf("%f", &(account->balance));
    printf("Veuillez renseigner le taux de ce compte :\n");
    scanf("%f", &(account->rate));
    printf("Veuillez renseigner la durée avant mise à disposition (en jour) :\n");
    scanf("%d", &(account->minimalTime));

    saveAccount(account);
}

void displayAccount(Account *account) {
    printf("Voici les informations du compte N°%d : \n", account->id);
    printf("Solde : %f\n", account->balance);
    printf("Taux : %f\n", account->rate);
    printf("Durée avant dispo : %d\n", account->minimalTime);
    printf("\n");
}

void displayAccountsByCustomer(Customer *customer) {
    char *id;
    char *ids = searchAccountsByCustomer(customer->id);
    char *ptr = ids;

    id = strtok_r(ids, ",", &ptr);

    Account account;
    while (id != NULL) {
        account = getAccount(atoi(id));
        displayAccount(&account);

        id = strtok_r(NULL, ",", &ptr);
    }

    free(ids);
}

void depositAccount(Account account, int amountOfMoney) {
    account.balance += amountOfMoney;
    saveAccount(&account);
}

void withdrawAccount(Account account, int amountOfMoney) {
    if (account.balance >= amountOfMoney) {
        account.balance -= amountOfMoney;
        saveAccount(&account);
    }
}

void transferringAccount(Account debitedAccount, Account creditedAccount, int amountOfMoney) {
    if (debitedAccount.balance > amountOfMoney) {
        debitedAccount.balance -= amountOfMoney;
        creditedAccount.balance += amountOfMoney;

        saveAccount(&debitedAccount);
        saveAccount(&creditedAccount);
    } else {
        printf("Le compte débiteur ne possède pas suffisement d'argent (%d euros)", amountOfMoney);
    }
}
