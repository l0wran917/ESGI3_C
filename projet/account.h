#ifndef FINAL_ACCOUNT_H
#define FINAL_ACCOUNT_H

    struct Account {
        int accountId;
        int customerId;
        int balance;
        int rate;
        int minimalTime;
    };

    typedef struct Account Account;

    void createAccount(int idCustomer);
    void displayAccountBalance(int idCustomer);
    void depositAccount(Account account, int amountOfMoney);
    void withdrawAccount(Account account, int amountOfMoney);
    void transferringAccount(Account debitedAccount, Account creditedAccount, int amountOfMoney);

#endif //FINAL_ACCOUNT_H
