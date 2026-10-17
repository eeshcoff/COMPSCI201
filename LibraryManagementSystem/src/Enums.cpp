#include "Enums.h"
#include <stdexcept>

std::string genreToString(Genre g) {
    switch (g) {

        case Genre::Fiction: return "Fiction";
        case Genre::NonFiction: return "Non-Fiction";
        case Genre::Mystery: return "Mystery";
        case Genre::Science: return "Science";
        case Genre::Biography: return "Biography";
        default: return "Unknown";

    }
}

Genre stringToGenre(const std::string& str) {

    if (str == "Fiction") {
        return Genre::Fiction;

    } else if (str == "Non-Fiction") {
        return Genre::NonFiction;

    } else if (str == "Mystery") {
        return Genre::Mystery;

    } else if (str == "Science") {
        return Genre::Science;

    } else if (str == "Biography") {
        return Genre::Biography;

    } else {
        throw std::invalid_argument("Invalid genre string: " + str);

    }
}

std::string statusToString(BookStatus s) {
    switch (s) {
        case BookStatus::Available: return "Available";
        case BookStatus::CheckedOut: return "Checked Out";
        default: return "Unknown";
    }
}

std::string transactionTypeToString(TransactionType t) {
    switch (t) {
        case TransactionType::Checkout: return "Checkout";
        case TransactionType::Return: return "Return";
        default: return "Unknown";
    }
}