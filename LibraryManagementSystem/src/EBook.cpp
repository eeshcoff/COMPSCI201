#include "EBook.h"

EBook::EBook(std::string t, std::string a, Genre g, double size) 
    : Book(t, a, g), fileSizeMB(size) {}

double EBook::getFileSize() const {
    return fileSizeMB;
}

void EBook::displayInfo() const {
    Book::displayInfo();
    std::cout << "File Size: " << fileSizeMB << " MB" << std::endl;
}
