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
        printf("3 - Recherche d'un client\n");
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
    do {
        printf("Identifiant du client : ");
        scanf("%d", &id);

        customer = getCustomer(id);
        if (customer.id < 0) {
            printf("Le client n'existe pas\n");
        }
    } while (customer.id < 0);

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