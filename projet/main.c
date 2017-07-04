#include <stdio.h>
#include <stdlib.h>

struct Customer
{
    int customerId;
    char* lastname;
    char* firstname;
    char* profession;
    int* phone;
} customer;


struct Account {
    int accountId;
    int customerId;
    int balance;
    int rate;
    int minimalTime = 0;
};

int main()
{
    printf("Hello world!\n");
    return 0;
}
