#ifndef EBOOK_H
#define EBOOK_H

#include <string>

#include "Book.h"

class EBook : public Book {
    double fileSizeMB;
public:
    EBook(std::string t, std::string a, Genre g, double size);
    double getFileSize() const;
    void displayInfo() const override;
};

#endif // EBOOK_H