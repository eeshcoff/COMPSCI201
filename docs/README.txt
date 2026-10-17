-- Library Management System

A console-based C++ application that simulates a small library: it manages books, patrons, and borrow/return transactions through a menu-driven interface. Built as the M08A Final Project for my Fall Computer Science course to demonstrate object-oriented design and core C++ features in one integrated program.

Author: Emily Eshcoff

---

-- Features

- Load books and patrons from CSV text files at startup
- View all books, with polymorphic details (file size for e-books, page count for printed books)
- View all patrons and the books each one has borrowed
- Check out a book to a patron, with a due date 14 days out
- Return a book
- Add new books (e-book or printed) and new patrons
- Search books by author or by genre
- Every checkout and return appended to a transaction log
- Save books (including who has them checked out) and patrons back to file on exit
- Invalid input and invalid operations are reported without crashing the program

---

-- Project Structure

 LibraryManagementSystem/
    ├── data/
    │   ├── books.txt           - Book records (CSV)
    │   ├── patrons.txt         - Patron records (CSV)
    │   └── transactions.txt    - Append-only transaction log
    ├── include/
    │   ├── Book.h  EBook.h  PrintedBook.h
    │   ├── Patron.h
    │   ├── Transaction.h  Date.h
    │   ├── Library.h
    │   ├── Enums.h
    │   └── FileUtils.h         - Template load/save helpers
    └── src/
        ├── Book.cpp  EBook.cpp  PrintedBook.cpp
        ├── Patron.cpp
        ├── Transaction.cpp  Date.cpp
        ├── Library.cpp
        ├── Enums.cpp
        └── main.cpp            - Menu loop and input helpers


---

-- Building and Running

Requires a C++17 compiler (tested with g++ / MinGW).

bash
cd LibraryManagementSystem
g++ -std=c++17 -Wall -Iinclude src/.cpp -o library
./library            - Windows: .\library.exe


> Run from the LibraryManagementSystem folder. The program opens data/books.txt, data/patrons.txt, and data/transactions.txt by relative path. Running it from anywhere else stops at startup with "Error loading data: Could not open file".

---

-- Usage

On startup the program loads the data files and shows the menu:


===== Library Menu =====
1. View all books
2. View all patrons
3. Check out a book
4. Return a book
5. Add a book
6. Add a patron
7. Search by author
8. Search by genre
0. Save and exit


Enter the number of an option, then answer its prompts. Titles, author names, genres, and book types must be typed exactly as stored (they are case-sensitive).

Sample session:


Choice: 3
Patron ID: 2
Book title: Frankenstein
Book Frankenstein checked out by Patron ID 2. Due date: 10/31/2026

Choice: 3
Patron ID: 1
Book title: Frankenstein
Error: Book Frankenstein is already checked out.

Choice: 4
Patron ID: 2
Book title: Frankenstein
Book Frankenstein returned by Patron ID 2.

Choice: 8
Genre: Science
Books in genre Science:
Title: Quantum Physics 101
Author: Albert Einstein
Genre: Science
Status: Available
File Size: 4.5 MB
...

Choice: 0
Data saved. Goodbye!


> Book and patron changes are written to file only when you choose 0. Save and exit. Checkouts and returns are added to transactions.txt as soon as they happen.

---

-- Data File Formats

All files are plain comma-separated text, one record per line. Blank lines are skipped.

data/books.txt: Genre,Title,Author,Type,Size[,BorrowerID]


Fiction,The Great Gatsby,F. Scott Fitzgerald,Printed,180
Science,Quantum Physics 101,Albert Einstein,EBook,4.5
Non-Fiction,Silent Spring,Rachel Carson,Printed,368,2


- Genre: one of Fiction, Non-Fiction, Mystery, Science, Biography
- Type: Printed (Size = page count) or EBook (Size = file size in MB)
- BorrowerID (optional 6th field): the ID of the patron who has the book checked out. Written by the program on save; omitted when the book is available.

data/patrons.txt: ID,Name


1,Jane Doe
2,John Smith


data/transactions.txt: Date,Type,PatronID,Title (appended by the program)


10/16/2026,Checkout,2,A Brief History of Time
10/16/2026,Return,2,A Brief History of Time


If a line is malformed (wrong number of fields, unknown genre or type, or a non-numeric value), loading stops with an error that names the file and line number.

---

-- Known Limitations

- Titles, authors, and names can't contain commas, because the data files are plain CSV.
- Searches and title lookups must match exactly, including capitalization.
- Due dates are shown at checkout but not stored.
