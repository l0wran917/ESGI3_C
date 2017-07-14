#ifndef FINAL_CUSTOMER_H
#define FINAL_CUSTOMER_H

    struct Customer {
        int id;
        char *lastname;
        char *firstname;
        char *profession;
        char *phone;
    };
    typedef struct Customer Customer;

    void displayCustomer(struct Customer *customer);
    void constructCustomer(struct Customer *customer);
    void updateCustomer(struct Customer *customer);
#endif //FINAL_CUSTOMER_H
