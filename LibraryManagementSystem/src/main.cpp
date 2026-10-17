#include "Library.h"

#include <limits>
#include <stdexcept>
#include <string>

int readChoice(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            return value;
        }
        if (std::cin.eof()) {
            throw std::runtime_error("Input ended unexpectedly.");
        }
        std::cout << "Enter a number to navigate the menu." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

void printMenu() {
std::cout << "\n===== Library Menu =====" << std::endl;
std::cout << "1. View all books" << std::endl;
std::cout << "2. View all patrons" << std::endl;
std::cout << "3. Check out a book" << std::endl;
std::cout << "4. Return a book" << std::endl;
std::cout << "5. Add a book" << std::endl;
std::cout << "6. Add a patron" << std::endl;
std::cout << "7. Search by author" << std::endl;
std::cout << "8. Search by genre" << std::endl;
std::cout << "0. Save and exit" << std::endl;
}

int main() {
    Library library;

    try {
        library.loadData();
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        return 1;
    }

    int choice = -1;
    do {
        printMenu();
        try {
            choice = readChoice("Choice: ");

            switch (choice) {
                case 1:
                    library.displayBooks();
                    break;
                
                case 2:
                    library.displayPatrons();
                    break;

                case 3: {
                    int id = readChoice("Patron ID: ");
                    std::string title = readLine("Book title: ");
                    library.checkoutBook(id, title);
                    break;

                }
                case 4: {
                    int id = readChoice("Patron ID: ");
                    std::string title = readLine("Book title: ");
                    library.returnBook(id, title);
                    break;
                }

                case 5: {
                    std::string type = readLine("Type (EBook or Printed): ");
                    if (type != "EBook" && type != "Printed") {
                        throw std::invalid_argument("Type must be EBook or Printed.");
                    }
                    std::string title = readLine("Title: ");
                    std::string author = readLine("Author: ");
                    Genre genre = stringToGenre(readLine("Genre (Fiction, Non-Fiction, Mystery, Science, Biography): "));

                    if (type == "EBook") {
                        double size;
                        std::cout << "File size (MB): ";
                        if (!(std::cin >> size)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            throw std::invalid_argument("File size must be a number.");
                        }
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        library.addBook(new EBook(title, author, genre, size));
                    }
                    else {
                        int pages = readChoice("Page count: ");
                        library.addBook(new PrintedBook(title, author, genre, pages));
                    }
                    std::cout << "Added \"" << title << "\"." <<std::endl;
                    break;
                }

                case 6: {
                    int id = readChoice("New patron ID: ");
                    std::string name = readLine("Name: ");
                    library.addPatron(Patron(name, id));
                    std::cout << "Added patron " << name << "." << std::endl;
                    break;
                }

                case 7: {
                    std::string author = readLine("Author: ");
                    library.searchByAuthor(author);
                    break;                }

                case 8: {
                    Genre genre = stringToGenre(readLine("Genre: "));
                    library.searchByGenre(genre);
                    break;
                }

                case 0: {
                    library.saveData();
                    std::cout << "Data saved. Goodbye!" << std::endl;
                    break;
                }

                default: {
                    std::cout << "Invalid option. Choose 0-8." << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            if (std::cin.eof()) break;
        }
    } while (choice != 0);

    return 0;
}