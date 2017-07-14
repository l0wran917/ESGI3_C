#ifndef FINAL_CSV_H
#define FINAL_CSV_H
// Get
Customer *getCustomer(int id);
Account *getAccount(int id);
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
char *formatCustomerToCsv(Customer customer);
Customer *buildCustomerFromCsv(char *data);

// Account
char *formatAccountToCsv(Account account);
Account *buildAccountFromCsv(char *data);


#endif //FINAL_CSV_H
