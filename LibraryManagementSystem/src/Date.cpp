#include "Date.h"
#include <ctime>
#include <iomanip>
#include <sstream>


Date::Date() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    day = now->tm_mday;
    month = now->tm_mon + 1; // tm_mon is 0-based
    year = now->tm_year + 1900; // tm_year is years since 1900

}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date Date::addDays(int days) const {
    std::tm t{};
    t.tm_mday = day + days;
    t.tm_mon = month - 1; // tm_mon is 0-based
    t.tm_year = year - 1900; // tm_year is years since 1900
    t.tm_hour = 12;

    std::mktime(&t); // Normalize the time structure

    return Date(t.tm_mday, t.tm_mon + 1, t.tm_year + 1900);
}

std::string Date::toString() const {
    std::ostringstream out;

    out << std::setw(2) << std::setfill('0') << month << "/"
        << std::setw(2) << std::setfill('0') << day << "/"
        << year;
    return out.str();
}

void Date::displayDate() const {
    std::cout << toString() << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.toString();
    return os;
}