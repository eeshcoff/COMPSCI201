#include "Patron.h"
#include <ostream>
#include <stdexcept>

Patron::Patron(std::string n, int i) : name(n), id(i) {}

std::string Patron::getName() const {
    return name;
}

int Patron::getId() const {
    return id;
}

void Patron::borrowBook(Book* b) {
    borrowedBooks.push_back(b);
}

void Patron::returnBook(Book* b) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), b);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    } else {
        throw std::invalid_argument(name + " does not have \"" + b->getTitle() + "\" checked out.");
    }
}

void Patron::displayPatron() const {
    std::cout << "Patron Name: " << name << ", ID: " << id << std::endl;
    std::cout << "Borrowed Books: ";
    if (borrowedBooks.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < borrowedBooks.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << borrowedBooks[i]->getTitle();
        }
    }
    std::cout << std::endl;
}

bool Patron::operator==(const Patron& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& os, const Patron& p) {
    p.displayPatron();
    return os;
}

const std::vector<Book*>& Patron::getBorrowedBooks() const {
    return borrowedBooks;
}