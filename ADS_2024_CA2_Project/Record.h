#pragma once
#include <string>
#include <iomanip>

struct Record {
    std::string name;
    int age;
    std::string email;
    std::string country;
    double balance;

    friend std::ostream& operator<<(std::ostream& os, const Record& record) {
        os << std::left << std::setw(20) << record.name
            << std::setw(5) << record.age
            << std::setw(30) << record.email
            << std::setw(20) << record.country
            << "$" << std::fixed << std::setprecision(2) << record.balance;
        return os;
    }
};
