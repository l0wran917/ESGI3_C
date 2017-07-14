#include <stdio.h>
#include <stdlib.h>
#include "customer.h"

void displayCustomer(Customer *customer) {
    printf("Voici les informations du client :\n");
    printf("Id : %d\n", customer->id);
    printf("Lastname : %s\n", customer->lastname);
    printf("Firstname : %s\n", customer->firstname);
    printf("Profession : %s\n", customer->profession);
    printf("Phone : %s\n", customer->phone);
}

void constructCustomer(Customer *customer) {
    printf("Veuillez renseigner le nom de famille du client :\n");
    scanf("%s", customer->lastname);
    printf("Veuillez renseigner le prenom du client :\n");
    scanf("%s", customer->firstname);
    printf("Veuillez renseigner la profession du client :\n");
    scanf("%s", customer->profession);
    printf("Veuillez renseigner le telephone du client :\n");
    scanf("%s", customer->phone);
}

void updateCustomer(Customer *customer) {
    int choice = 0;

    do {
        displayCustomer(customer);
        printf("Quelles informations souhaitez-vous modifier ?\n");
        printf("1 - Nom\n");
        printf("2 - Prenom\n");
        printf("3 - Profession\n");
        printf("4 - Numero de telephone\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Veuillez renseigner le nom de famille du client :\n");
                scanf("%s", customer->lastname);
                break;
            case 2:
                printf("Veuillez renseigner le prenom du client :\n");
                scanf("%s", customer->firstname);
                break;
            case 3:
                printf("Veuillez renseigner la profession du client :\n");
                scanf("%s", customer->profession);
                break;
            case 4:
                printf("Veuillez renseigner le telephone du client :\n");
                scanf("%s", customer->phone);
                break;
        }
        printf("Souhaitez-vous effectuer une nouvelle modification ? :\n 1 - Oui\n 2 - Non\n");
        choice = 0;
        scanf("%d", &choice);
    } while (choice == 1);
}
