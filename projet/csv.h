#ifndef FINAL_CSV_H
#define FINAL_CSV_H

char *getCsvCustomerHeader();

char *getCustomerDataFormatted(Customer customer);

int saveCustomer(Customer *customer);

Customer *getCustomer(int id);

char *cleanCsvColumn(char *string);

#endif //FINAL_CSV_H
