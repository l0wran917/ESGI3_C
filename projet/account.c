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
    char *oldIds = ids;
    char idTmp[11];
    memset(idTmp, '\0', sizeof(idTmp));

    Account account;
    int delimiterPos = 0;
    while (strlen(ids) > 0) {
        char *str = strchr(ids, ',');
        if (str != NULL) {
            delimiterPos = (int) strlen(str);
        } else {
            delimiterPos = 0;
        }

        strncpy(idTmp, ids, strlen(ids) - delimiterPos);
        ids += strlen(idTmp) + 1;

        account = getAccount(atoi(idTmp));
        displayAccount(&account);
    }

    free(oldIds);
}

void depositAccount(Account *account, float amountOfMoney) {
    account->balance += amountOfMoney;
    saveAccount(account);
    addHistory(account->customerId, account->id, "Depot", amountOfMoney);
}

void withdrawAccount(Account *account, float amountOfMoney) {
    if (account->balance >= amountOfMoney) {
        account->balance -= amountOfMoney;
        saveAccount(account);
        addHistory(account->customerId, account->id, "Debit", -amountOfMoney);
    }
}

void transferringAccount(Account debitedAccount, Account creditedAccount, float amountOfMoney) {
    if (debitedAccount.balance > amountOfMoney) {
        debitedAccount.balance -= amountOfMoney;
        creditedAccount.balance += amountOfMoney;

        saveAccount(&debitedAccount);
        saveAccount(&creditedAccount);

        addHistory(debitedAccount.customerId, debitedAccount.id, "Transfert", -amountOfMoney);
        addHistory(creditedAccount.customerId, creditedAccount.id, "Transfert", amountOfMoney);
    } else {
        printf("Le compte débiteur ne possède pas suffisement d'argent (%d euros)", amountOfMoney);
    }
}