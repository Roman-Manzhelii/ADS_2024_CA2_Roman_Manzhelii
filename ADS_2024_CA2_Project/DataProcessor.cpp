#include "DataProcessor.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n\"");
    size_t last = str.find_last_not_of(" \t\r\n\"");
    if (first == std::string::npos || last == std::string::npos)
        return "";
    return str.substr(first, (last - first + 1));
}

double parseBalance(const std::string& balanceStr) {
    std::string cleaned = balanceStr;
    cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), ','), cleaned.end());
    cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), '$'), cleaned.end());
    return std::stod(cleaned);
}

void loadData(const std::string& filename, std::vector<Record>& records) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(infile, line);

    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        std::string token;
        Record record;

        // Parse each field
        std::getline(ss, token, ',');
        record.name = trim(token);

        std::getline(ss, token, ',');
        record.age = std::stoi(trim(token));

        std::getline(ss, token, ',');
        record.email = trim(token);

        std::getline(ss, token, ',');
        record.country = trim(token);

        std::getline(ss, token);
        record.balance = parseBalance(trim(token));

        records.push_back(record);
    }

    infile.close();
}

void displayKey(const std::string& key) {
    std::cout << key;
}

void displayKey(int key) {
    std::cout << key;
}

void displayKey(double key) {
    std::cout << std::fixed << std::setprecision(2) << key;
}
