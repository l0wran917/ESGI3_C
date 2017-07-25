#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
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

void displayHistoryAction(Customer *customer);

void administrationAction();

void exportAction();

void importAction();

void displayTotalAccountAmountAction();

void displayTotalRateAmountAction();

void searchCustomerAction();

void createFolders();

void cleanOutput() {
    int i = 0;
    for (; i < 25; i++) {
        printf("\n");
    }
}

int main() {
    createFolders();

    int choice = 0;

    do {
        cleanOutput();
        printf("Menu Principal\n");
        printf("Quelle action voulez vous effectuer ?\n\n");
        printf("1 - Gestion des clients\n");
        printf("2 - Administration\n");

        printf("0 - Quitter\n");
        printf("\nAction : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clientManagementAction();
                break;
            case 2:
                administrationAction();
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
            case 3:
                searchCustomerAction();
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
        printf("4 - Consultation de l'historique quotidient\n");
        printf("5 - Operation bancaire\n");
        printf("6 - Fermeture d'un compte\n");

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
                displayHistoryAction(&customer);
                break;
            case 5:
                bankingOperationAction(&customer);
                break;
            case 6:
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
    scanf("%f", &amount);

    transferringAccount(source, dest, amount);
    printf("Le virement est effectue\n");
    system("pause");
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

        if (account.id >= 0 && account.customerId == customer->id) {
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

void displayHistoryAction(Customer *customer) {
    displayHistoriesByCustomer(customer);
    system("pause");
}

void administrationAction() {
    int choice = 0;

    do {
        cleanOutput();
        printf("Administration\n");
        printf("Quelle action voulez vous effectuer ?\n\n");
        printf("1 - Afficher solde de tous les comptes\n");
        printf("2 - Afficher le montant d'interets total\n");
        printf("3 - Exporter les données\n");
        printf("4 - Importer les données\n");

        printf("0 - Quitter\n");
        printf("\nAction : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayTotalAccountAmountAction();
                break;
            case 2:
                displayTotalRateAmountAction();
                break;
            case 3:
                exportAction();
                break;
            case 4:
                importAction();
                break;
        }

    } while (choice != 0);

}

void exportAction() {
    cleanOutput();

    char filename[512];
    char outputPath[] = "../data/backup/";

    printf("Nom du fichier de backup : ");
    scanf("%s", filename);

    strcat(outputPath, filename);

    backupData(outputPath);
    printf("Backup fini\n");
    system("pause");
}

void importAction() {
    cleanOutput();

    char filename[512];
    char filePath[] = "../data/backup/";
    int fileExists = -1;

    do {
        printf("Nom du fichier de backup : ");
        scanf("%s", filename);

        strcat(filePath, filename);

        fileExists = access(filePath, R_OK);
        if (fileExists != 0) {
            printf("Le fichier n'existe pas\n");
            strcpy(filePath, "../data/backup/");
        }
    } while (fileExists != 0);

    importData(filePath);
    printf("Les donnees sont importees\n");
    system("pause");
}

void displayTotalAccountAmountAction() {
    float total = getTotalAmountAccounts();
    printf("La banque cummule au total %f€\n", total);
    system("pause");
}

void displayTotalRateAmountAction() {
    float total = getTotalRateAmountAccounts();
    printf("La banque devra au total %f€\n", total);
    system("pause");
}

void searchCustomerAction() {
    cleanOutput();
    char input[512];

    printf("Entrez le nom : ");
    scanf("%s", input);

    searchCustomer(input);
    system("pause");
}

void createFolders() {
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        int created = 0;

#if defined(_WIN32)
        created = _mkdir("data");
#else
        created = mkdir("data", 0777);
#endif
        if (created == -1) {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
#if defined(_WIN32)
        created = _mkdir("data/backup");
#else
        created = mkdir("data/backup", 0777);
#endif
        if (created == -1) {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
#if defined(_WIN32)
        created = _mkdir("data/history");
#else
        created = mkdir("data/history", 0777);
#endif
        if (created == -1) {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);

        }
    }
}