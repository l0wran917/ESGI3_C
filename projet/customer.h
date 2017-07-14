#ifndef FINAL_CUSTOMER_H
#define FINAL_CUSTOMER_H

    struct Customer {
        int  id;
        char lastname[50];
        char debug[1];
        char firstname[50];
        char profession[50];
        char phone[10];
    };
    typedef struct Customer Customer;

    void displayCustomer(struct Customer *customer);
    void constructCustomer(struct Customer *customer);
    void updateCustomer(struct Customer *customer);

#endif //FINAL_CUSTOMER_H
