#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
#include <ctime>

class Date {
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);

    Date addDays(int days) const;
    std::string toString() const;

    void displayDate() const;

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif // DATE_H