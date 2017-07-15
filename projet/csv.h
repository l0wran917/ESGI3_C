#ifndef FINAL_CSV_H
#define FINAL_CSV_H

#include "customer.h"
#include "account.h"

// Get
Customer getCustomer(int id);
Account getAccount(int id);
char *getRow(int id, const char *filename);

// Save
int saveCustomer(Customer *customer);
int saveAccount(Account *account);
int saveRow(int id, char *data, const char *filename);

// Delete
int deleteCustomer(int id);
int deleteAccount(int id);
int deleteRow(int id, const char *filename);

// Utils
int getLastId(const char *filename);
char *cleanCsvColumn(char *string);

// Customer
char *formatCustomerToCsv(Customer *customer);
Customer *buildCustomerFromCsv(char *data);
char* searchAccountsByCustomer(int customerId);

// Account
char *formatAccountToCsv(Account *account);
Account *buildAccountFromCsv(char *data);

// History
void addHistory(int customerId, int accountId, char *label, float amount);
char *getHistoryFilename();

#endif //FINAL_CSV_H
