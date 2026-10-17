#ifndef PRINTEDBOOK_H
#define PRINTEDBOOK_H

#include <string>
#include "Book.h"

class PrintedBook : public Book {

    int numPages;

    public:
        PrintedBook(std::string t, std::string a, Genre g, int pages);
        void displayInfo() const override;
        int getNumPages() const;

    };
    
#endif // PRINTEDBOOK_H