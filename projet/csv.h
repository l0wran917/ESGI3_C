#ifndef FINAL_CSV_H
#define FINAL_CSV_H

Customer *getCustomer(int id);
// ---------

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


#endif //FINAL_CSV_H
