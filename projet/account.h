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

    void displayAccountsByCustomer(int customerId);

    void displayAccountBalance(int idCustomer);
    void depositAccount(Account account, int amountOfMoney);
    void withdrawAccount(Account account, int amountOfMoney);
    void transferringAccount(Account debitedAccount, Account creditedAccount, int amountOfMoney);

#endif //FINAL_ACCOUNT_H
