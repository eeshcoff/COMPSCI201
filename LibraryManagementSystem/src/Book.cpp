#include "Book.h"

Book::Book(std::string t, std::string a, Genre g) 
    : title(t), author(a), genre(g), status(BookStatus::Available) {}


std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

Genre Book::getGenre() const {
    return genre;
}

void Book::setStatus(BookStatus s) {
    status = s;
}

BookStatus Book::getStatus() const {
    return status;
}

void Book::displayInfo() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Genre: " << genreToString(genre) << std::endl;
    std::cout << "Status: " << statusToString(status) << std::endl;

}

bool Book::operator==(const Book& other) const {
    return title == other.title && author == other.author;
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
    b.displayInfo();
    return os;
}