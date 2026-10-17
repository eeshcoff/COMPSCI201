#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"
#include "Enums.h"

class Transaction {
    int patronId;
    std::string bookTitle;
    Date date;
    TransactionType transactionType;
    public:
        Transaction(int pid, std::string bt, TransactionType type);
        void displayTransaction() const;
        std::string toFileString() const;
};

#endif // TRANSACTION_H