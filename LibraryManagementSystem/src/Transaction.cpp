#include "Transaction.h"
#include <iostream>
#include <sstream>

Transaction::Transaction(int pid, std::string bt, TransactionType type) 
    : patronId(pid), bookTitle(bt), transactionType(type) {}

void Transaction::displayTransaction() const {
    std::cout << date << " | "
                << transactionTypeToString(transactionType) << " | "
                << "Patron ID: " << patronId << " | "
                << "Book Title: " << bookTitle << std::endl;
}

std::string Transaction::toFileString() const {
    std::ostringstream out;
    out << date << "," 
        << transactionTypeToString(transactionType) << "," 
        << patronId << "," 
        << bookTitle;
    return out.str();
}
