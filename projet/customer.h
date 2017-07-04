#ifndef FINAL_CUSTOMER_H
#define FINAL_CUSTOMER_H

    struct Customer {
        int customerId;
        char *lastname;
        char *firstname;
        char *profession;
        char *phone;
    };
    typedef struct Customer Customer;

    void displayCustomer(struct Customer *customer);
    void constructCustomer(struct Customer *customer);
    void updateCustomer(struct Customer *customer);

    void displayCustomer(struct Customer *customer)
    {
        printf("Voici les informations du client :\n");
        printf("Id : %d\n", &customer->id);
        printf("Lastname : %s\n", &customer->lastname);
        printf("Firstname : %s\n", &customer->firstname);
        printf("Profession : %s\n", &customer->profession);
        printf("Phone : %s\n", &customer->phone);
    }

    void constructCustomer(struct Customer *customer)
    {
        printf("Veuillez renseigner le nom de famille du client :\n");
        scanf("%s", &customer->lastname);
        printf("Veuillez renseigner le prénom du client :\n");
        scanf("%s", &customer->firstname);
        printf("Veuillez renseigner la profession du client :\n");
        scanf("%s", &customer->profession);
        printf("Veuillez renseigner le téléphone du client :\n");
        scanf("%s", &customer->phone);
    }

    void updateCustomer(struct Customer *customer)
    {
        displayCustomer(customer);
        int choice = 0;
        printf("Quelles informations souhaitez-vous modifier ?\n");
        printf("1 - Nom\n");
        printf("2 - Prénom\n");
        printf("3 - Profession\n");
        printf("4 - Numéro de téléphone\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("Veuillez renseigner le nom de famille du client :\n");
                scanf("%s", &customer->lastname);
                break;
            case 2:
                printf("Veuillez renseigner le prénom du client :\n");
                scanf("%s", &customer->firstname);
                break;
            case 3:
                printf("Veuillez renseigner la profession du client :\n");
                scanf("%s", &customer->profession);
                break;
            case 4:
                printf("Veuillez renseigner le téléphone du client :\n");
                scanf("%s", &customer->phone);
                break;
        }
        printf("Souhaitez-vous effectuer une nouvelle modification ? :\n 1 - Oui\n 2 - Non\n");
        choice = 0;
        scanf("%d", &choice);
        if(choice == 1) {
            updateCustomer(customer);
        }
    }
#endif //FINAL_CUSTOMER_H
