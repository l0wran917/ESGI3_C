#include <stdio.h>
#include <stdlib.h>

struct Account {
    int accountId;
    int customerId;
    int balance;
    int rate;
    int minimalTime;
};

typedef struct Account Account;

int main()
{
    printf("Hello world!\n");
    return 0;
}






/*
    Fonction permmetant la création d'un compte

    @param int  idClient  id du client
 */
void createAccount(int idCustomer) {
    Account newAccount;
    newAccount.accountId = 0; // TODO
    newAccount.customerId = idCustomer;
    newAccount.minimalTime = 0;
}

/*
    Fonction permmetant l'affichage du solde d'un compte

    @param int  idCustomer  id du client
 */
void displayAccountBalance(int idCustomer) {
    printf();
}

/*
    Fonction permmetant la suppression d'un compte

    @param int  idAccount  id du compte
 */
void deleteAccount(int idAccount) {

}

/*
    Fonction permmetant le créditement d'un compte

    @param Account  account          compte à créditer
    @param int      amountOfMoney    montant à créditer
 */
void depositAccount(Account account, int amountOfMoney) {
    account.balance += amountOfMoney;
}

/*
    Fonction permmetant le débitement d'un compte

    @param Account  account          compte à débiter
    @param int      amountOfMoney    montant à débiter
 */
void withdrawAccount(Account account, int amountOfMoney) {
    account.balance -= amountOfMoney;
}

/*
    Fonction permmetant le transfert d'argent entre deux comptes

    @param Account  debitedAccount   compte à débiter
    @param Account  creditedAccount  compte à débiter
    @param int      amountOfMoney    montant à transferer
 */
void transferringAccount(Account debitedAccount, Account creditedAccount, int amountOfMoney) {
    if(debitedAccount.balance > amountOfMoney) {
        debitedAccount.balance -= amountOfMoney;
        creditedAccount.balance += amountOfMoney;
    } else {
        printf("Le compte débiteur ne possède pas suffisement d'argent (%d euros)", amountOfMoney);
    }
}