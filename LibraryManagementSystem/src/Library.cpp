#include "Library.h"
#include <fstream>

// Helper function to split a CSV line into fields
static std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    return fields;
}

struct LoadedBook {
    Book* book;
    int borrowerId; // 0 if not borrowed
};

// Helper function to parse a book from a CSV line
static LoadedBook parseBook(const std::string& line, int) {
    std::vector<std::string> f = splitCSV(line);
    if (f.size() != 5 && f.size() != 6) {
        throw std::runtime_error("expected 5 or 6 fields, got " + std::to_string(f.size()));
    }
    Genre genre = stringToGenre(f[0]);
    Book* book = nullptr;
    if (f[3] == "Printed") {
        book = new PrintedBook(f[1], f[2], genre, std::stoi(f[4]));
    } else if (f[3] == "EBook") {
        book = new EBook(f[1], f[2], genre, std::stod(f[4]));
    } else {
        throw std::runtime_error("unknown book type: " + f[3]);
    }
    int borrower = (f.size() == 6) ? std::stoi(f[5]) : 0;
    return LoadedBook{book, borrower};
}

static Patron parsePatron(const std::string& line, int) {
    std::vector<std::string> f = splitCSV(line);
    if (f.size() != 2) {
        throw std::runtime_error("expected 2 fields, got " + std::to_string(f.size()));
    }
    return Patron(f[1], std::stoi(f[0]));
}

static std::string formatBook(const LoadedBook& lb) {
    const Book* book = lb.book;
    std::string line = genreToString(book->getGenre()) + "," + book->getTitle() + "," + book->getAuthor() + ",";

    if (const EBook* e = dynamic_cast<const EBook*>(book)) {
        std::ostringstream size;
        size << e->getFileSize();
        line += "EBook," + size.str();
    } else if (const PrintedBook* p = dynamic_cast<const PrintedBook*>(book)) {
        line += "Printed," + std::to_string(p->getNumPages());
    } else {
        throw std::runtime_error("Unknown book type for formatting."); 
    }

    if (lb.borrowerId != 0) {
        line += "," + std::to_string(lb.borrowerId);
    }
    return line;
}

static std::string formatPatron(const Patron& p) {
    return std::to_string(p.getId()) + "," + p.getName();
}

Library::~Library() {
    for (Book* book : books) {
        delete book;
    }
}


void Library::loadData() {
    std::vector<Patron> loadedPatrons = loadFromFile<Patron>("data/patrons.txt", parsePatron);
    for (const Patron& p : loadedPatrons) {
        addPatron(p);
    }

    std::vector<LoadedBook> loadedBooks = loadFromFile<LoadedBook>("data/books.txt", parseBook);
    for (const LoadedBook& lb : loadedBooks) {
        addBook(lb.book);
        if (lb.borrowerId != 0) {
           findPatronById(lb.borrowerId)->borrowBook(lb.book);
           lb.book->setStatus(BookStatus::CheckedOut);
        }
    }
}

void Library::addBook(Book* b) {
    books.push_back(b);
}

void Library::addPatron(const Patron& p) {
    if (patrons.count(p.getId()) > 0) {
        throw std::runtime_error("Patron with ID " + std::to_string(p.getId()) + " already exists.");
    }
    patrons.insert({p.getId(), p});
}

Book* Library::findBookByTitle(const std::string& title) const {
    for (Book* book : books) {
        if (book->getTitle() == title) {
            return book;
        }
    }
    throw std::runtime_error("Book with title '" + title + "' not found.");
}

Patron* Library::findPatronById(int id) {
    auto it = patrons.find(id);
    if (it == patrons.end()) {
        throw std::invalid_argument("Patron with ID " + std::to_string(id) + " not found.");
    }
    return &(it->second);
}

void Library::displayBooks() const {
    std::cout << "====== Books(" << books.size() << ") ======" << std::endl;
    for (const Book* book : books) {
        std::cout << *book << std::endl;
    }
}

void Library::displayPatrons() const {
    std::cout << "====== Patrons(" << patrons.size() << ") ======" << std::endl;
    for (const auto& pair : patrons) {
        std::cout << pair.second << std::endl;
    }
}

void Library::checkoutBook(int patronId, std::string title) {
    Patron* patron = findPatronById(patronId);
    Book* book = findBookByTitle(title);

    if (book->getStatus() == BookStatus::CheckedOut) {
        throw std::runtime_error("Book '" + title + "' is already checked out.");
    }

    patron->borrowBook(book);
    book->setStatus(BookStatus::CheckedOut);
    transactions.emplace_back(patronId, title, TransactionType::Checkout);
    Date dueDate = Date().addDays(14); // Assuming a 2-week checkout period
    std::ofstream log("data/transactions.txt", std::ios::app);
    log << transactions.back().toFileString() << std::endl;
    log.close();
    std::cout << "Book '" << title << "' checked out by Patron ID " << patronId << ". Due date: " << dueDate << std::endl;
}

void Library::returnBook(int patronId, std::string title) {
    Patron* patron = findPatronById(patronId);
    Book* book = findBookByTitle(title);

    if (book->getStatus() == BookStatus::Available) {
        throw std::runtime_error("Book '" + title + "' is not checked out.");
    }

    patron->returnBook(book);
    book->setStatus(BookStatus::Available);
    transactions.emplace_back(patronId, title, TransactionType::Return);
    std::ofstream log("data/transactions.txt", std::ios::app);
    log << transactions.back().toFileString() << std::endl;
    std::cout << "Book '" << title << "' returned by Patron ID " << patronId << "." << std::endl;
}

void Library::saveData() {
    std::map<Book*, int> borrowerOf;
    for (const auto& pair : patrons) {
        const Patron& patron = pair.second;
        for (Book* book : patron.getBorrowedBooks()) {
            borrowerOf[book] = patron.getId();
        }
    }

    std::vector<LoadedBook> bookRows;
    for (Book* book : books) {
        int borrowerId = (borrowerOf.count(book) > 0) ? borrowerOf[book] : 0;
        bookRows.push_back(LoadedBook{book, borrowerId});
    }

    std::vector<Patron> patronRows;
    for (const auto& pair : patrons) {
        patronRows.push_back(pair.second);
    }

    saveToFile<LoadedBook>("data/books.txt", bookRows, formatBook);
    saveToFile<Patron>("data/patrons.txt", patronRows, formatPatron);
}



void Library::searchByAuthor(const std::string& author) const {
    std::cout << "Books by " << author << ":" << std::endl;
    bool found = false;
    for (const Book* book : books) {
        if (book->getAuthor() == author) {
            std::cout << *book << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No books found by " << author << "." << std::endl;
    }
}

void Library::searchByGenre(Genre g) const {
    std::cout << "Books in genre " << genreToString(g) << ":" << std::endl;
    bool found = false;
    for (const Book* book : books) {
        if (book->getGenre() == g) {
            std::cout << *book << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No books found in genre " << genreToString(g) << "." << std::endl;
    }
}