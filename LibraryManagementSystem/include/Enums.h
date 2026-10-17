#ifndef ENUMS_H
#define ENUMS_H

#include <string>

enum class Genre { 
    Fiction, 
    NonFiction, 
    Mystery, 
    Science, 
    Biography 
    };

enum class BookStatus { 
    Available, 
    CheckedOut 
    };

enum class TransactionType { 
    Checkout, 
    Return 
    };

std::string genreToString(Genre g);
Genre stringToGenre(const std::string& str);
std::string statusToString(BookStatus s);
std::string transactionTypeToString(TransactionType t);

#endif // ENUMS_H