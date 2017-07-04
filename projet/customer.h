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

#endif //FINAL_CUSTOMER_H
