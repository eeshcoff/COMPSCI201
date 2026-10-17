#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Book.h"
#include "Patron.h"
#include "Transaction.h"
#include "FileUtils.h"
#include "EBook.h"
#include "PrintedBook.h"

class Library {

    std::vector<Book*> books;
    std::map<int, Patron> patrons;
    std::vector<Transaction> transactions;

    Book* findBookByTitle(const std::string& title) const;
    Patron* findPatronById(int id);

    public:
        Library() = default;
        ~Library();

        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;

        void loadData();
        void saveData();
        void addBook(Book* b);
        void addPatron(const Patron& p);
        void checkoutBook(int patronId, std::string title);
        void returnBook(int patronId, std::string title);
        void displayBooks() const;
        void displayPatrons() const;
        void searchByAuthor(const std::string& author) const;
        void searchByGenre(Genre g) const;
};

#endif // LIBRARY_H