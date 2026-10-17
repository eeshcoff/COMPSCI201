#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

#include "Enums.h"

class Book {
    
    protected:
        std::string title;
        std::string author;
        Genre genre;
        BookStatus status;

    public:
        std::string getTitle() const;
        std::string getAuthor() const;
        Genre getGenre() const;

        Book(std::string t, std::string a, Genre g);
        virtual ~Book() = default;

        virtual void displayInfo() const;
        void setStatus(BookStatus s);
        BookStatus getStatus() const;

        bool operator==(const Book& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Book& b);
};
#endif // BOOK_H