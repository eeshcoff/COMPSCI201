#include "PrintedBook.h"

PrintedBook::PrintedBook(std::string t, std::string a, Genre g, int pages) 
    : Book(t, a, g), numPages(pages) {}

int PrintedBook::getNumPages() const {
    return numPages;
}

void PrintedBook::displayInfo() const {
    Book::displayInfo();
    std::cout << "Number of Pages: " << numPages << std::endl;
}
