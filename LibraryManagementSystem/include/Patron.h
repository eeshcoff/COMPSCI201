#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Book.h"


class Patron {
    
    std::string name;
    int id;
    std::vector<Book*> borrowedBooks;

    public:
        Patron(std::string n, int i);
        std::string getName() const;
        int getId() const;
        void borrowBook(Book* b);
        void returnBook(Book* b);
        void displayPatron() const;

        bool operator==(const Patron& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Patron& p);
        const std::vector<Book*>& getBorrowedBooks() const;
};

#endif // PATRON_H