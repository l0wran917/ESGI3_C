#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "customer.h"
#include "csv.h"

void clientManagementAction();

void createCustomerAction();

void viewAndEditCustomerAction();

void editCustomerAction(Customer *customer);

void createAccountAction(Customer *customer);

void displayAccountsAction(Customer *customer);

void bankingOperationAction(Customer *customer);

void depositAction(Customer *customer);

void withdrawAction(Customer *customer);

void transfertAction(Customer *customer);

int askAccountId(Customer *customer, int owned);

int askCustomerId();

void deleteAccountAction(Customer *customer);

void deleteCustomerAction();

void cleanOutput() {
    int i = 0;
    for (; i < 25; i++) {
        printf("\n");
    }
}

int main() {

    int choice = 0;

    do {
        cleanOutput();
        printf("Menu Principal\n");
        printf("Quelle action voulez vous effectuer ?\n\n");
        printf("1 - Gestion des clients\n");

        printf("0 - Quitter\n");
        printf("\nAction : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clientManagementAction();
                break;
        }
    } while (choice != 0);

    return 0;
}

void clientManagementAction() {
    int choice = 0;

    do {
        cleanOutput();
        printf("Gestion des clients\n");
        printf("Quelle action voulez vous effectuer ?\n\n");
        printf("1 - Creation d'un client\n");
        printf("2 - Visualisation et edition d'un client\n");
        printf("3 - Recherche d'un client (TODO)\n");
        printf("4 - Suppression d'un client\n");

        printf("0 - Quitter\n");
        printf("\nAction : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createCustomerAction();
                break;
            case 2:
                viewAndEditCustomerAction();
                break;
            case 3:

                break;
            case 4:
                deleteCustomerAction();
                break;
        }

    } while (choice != 0);

}

void createCustomerAction() {
    Customer customer;
    createCustomer(&customer);
    printf("Le client n°%d est maintenant present dans la base de donnees", customer.id);
    system("pause");
}

void viewAndEditCustomerAction() {
    int id = 0, choice = 0;
    Customer customer;

    cleanOutput();
    id = askCustomerId();
    customer = getCustomer(id);

    do {
        cleanOutput();
        printf("Client %s %s\n\n", customer.firstname, customer.lastname);
        printf("Quelle action voulez vous effectuer ?\n\n");
        printf("1 - Modifier les informations\n");
        printf("2 - Creation d'un compte\n");
        printf("3 - Consultation des comptes\n");
        printf("4 - Operation bancaire\n");
        printf("5 - Fermeture d'un compte\n");

        printf("0 - Quitter\n");
        printf("\nAction : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                editCustomerAction(&customer);
                break;
            case 2:
                createAccountAction(&customer);
                break;
            case 3:
                displayAccountsAction(&customer);
                break;
            case 4:
                bankingOperationAction(&customer);
                break;
            case 5:
                deleteAccountAction(&customer);
                break;
        }
    } while (choice != 0);
}

void editCustomerAction(Customer *customer) {
    cleanOutput();
    updateCustomer(customer);

    printf("Le client n°%d est maintenant a jour\n", customer->id);
    system("pause");
}

void createAccountAction(Customer *customer) {
    Account account;
    cleanOutput();
    createAccount(customer->id, &account);

    printf("Le compte n°%d est maintenant disponible\n", account.id);
    system("pause");
}

void displayAccountsAction(Customer *customer) {
    cleanOutput();
    displayAccountsByCustomer(customer);
    system("pause");
}

void bankingOperationAction(Customer *customer) {
    int choice = 0;
    do {
        cleanOutput();
        printf("Operation bancaire\n\n");
        printf("Quelle action voulez vous effectuer ?\n\n");
        printf("1 - Retrait\n");
        printf("2 - Depot\n");
        printf("3 - Transfert\n");

        printf("0 - Quitter\n");
        printf("\nAction : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                withdrawAction(customer);
                break;
            case 2:
                depositAction(customer);
                break;
            case 3:
                transfertAction(customer);
                break;
        }
    } while (choice != 0);
}

void depositAction(Customer *customer) {
    Account account;

    int id;
    float amount = 0;

    cleanOutput();
    displayAccountsByCustomer(customer);
    id = askAccountId(customer, 1);
    account = getAccount(id);

    printf("Quel montant voulez vous deposer ? ");
    scanf("%f", &amount);

    depositAccount(&account, amount);

    printf("Le solde actuel du compte n°%d est maintenant de %f\n", account.id, account.balance);
    system("pause");
}

void withdrawAction(Customer *customer) {
    Account account;

    int id;
    int allowed = 0;
    float amount = 0;

    cleanOutput();
    displayAccountsByCustomer(customer);
    id = askAccountId(customer, 1);
    account = getAccount(id);

    printf("Quel montant voulez vous debiter ? ");
    scanf("%f", &amount);

    withdrawAccount(&account, amount);

    printf("Le solde actuel du compte n°%d est maintenant de %f\n", account.id, account.balance);
    system("pause");
}

void transfertAction(Customer *customer) {
    cleanOutput();
    displayAccountsByCustomer(customer);
    int sourceId = askAccountId(customer, 1);
    int destId = askAccountId(customer, 0);
    float amount = 0;

    Account source = getAccount(sourceId);
    Account dest = getAccount(destId);

    printf("Quel montant voulez vous transferer ?\n");
    scanf("%f\n", &amount);

    transferringAccount(source, dest, amount);
}

int askAccountId(Customer *customer, int owned) {
    int id = 0;
    int allowed = 0;
    Account account;

    if (owned == 0) {
        allowed = 1;
    }

    do {
        printf("Identifiant du compte cible : ");
        scanf("%d", &id);

        account = getAccount(id);
        if (account.id < 0) {
            printf("Le compte n'existe pas\n");
        }

        if (account.id > 0 && account.customerId == customer->id) {
            allowed = 1;
        }

        if (allowed == 0) {
            printf("Ce compte ne vous appartient pas\n");
        }
    } while (account.id < 0 || allowed != 1);

    return account.id;
}

int askCustomerId() {
    Customer customer;
    int id;

    do {
        printf("Identifiant du client : ");
        scanf("%d", &id);

        customer = getCustomer(id);
        if (customer.id < 0) {
            printf("Le client n'existe pas\n");
        }
    } while (customer.id < 0);

    return id;
}

void deleteAccountAction(Customer *customer) {
    cleanOutput();
    displayAccountsByCustomer(customer);
    int accountId = askAccountId(customer, 1);
    deleteAccount(accountId);

    printf("Le compte n°%d n'existe plus\n", accountId);
    system("pause");
}

void deleteCustomerAction() {
    cleanOutput();
    int id = askCustomerId();
    deleteCustomer(id);

    printf("Le client n°%d n'existe plus\n", id);
    system("pause");
}