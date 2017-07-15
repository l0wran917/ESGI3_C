#ifndef FINAL_ACCOUNT_H
#define FINAL_ACCOUNT_H

    struct Account {
        int id;
        int customerId;
        float balance;
        float rate;
        int minimalTime;
    };

    typedef struct Account Account;

    void createAccount(int idCustomer, Account* account);
    void displayAccount(Account *account);

    void displayAccountsByCustomer(struct Customer *customer);

    void depositAccount(Account *account, float amountOfMoney);
    void withdrawAccount(Account *account, float amountOfMoney);
    void transferringAccount(Account debitedAccount, Account creditedAccount, float amountOfMoney);

#endif //FINAL_ACCOUNT_H
