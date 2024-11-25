#include "ProcessFile.h"
#include "DataProcessor.h"
#include "Record.h"
#include "TreeMap.h"
#include <vector>
#include <limits>
#include <iostream>
#include <string>

int main() {
    int choice;
    do {
        std::cout << "Select an option:\n";
        std::cout << "1. Organize words from a text file by their first letter.\n";
        std::cout << "2. View and search data from data.csv.\n";
        std::cout << "0. Exit.\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    	//https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n

        if (choice == 1) {
            TreeMap<char, BinaryTree<std::string>> wordMap;
            std::string filename;

            std::cout << "Enter the name of the text file to process: ";
            std::getline(std::cin, filename);

            processFile(filename, wordMap);

            displayLetters(wordMap);

            char letter;
            do {
                std::cout << "\nEnter a letter to display words starting with it (or '0' to exit): ";
                std::cin >> letter;
                if (letter == '0') break;

                displayWordsForLetter(wordMap, letter);

            } while (true);

        }
        else if (choice == 2) {
            std::vector<Record> records;
            std::string filename = "data.csv";
            loadData(filename, records);

            std::string fieldName;
            std::cout << "Enter the field to index on (name, age, email, country, balance): ";
            std::getline(std::cin, fieldName);

            if (fieldName == "age") {
                TreeMap<int, std::vector<Record>> index;
                indexData<int>(records, fieldName, index);
                displayIndex<int>(index);

                int value;
                do {
                    std::cout << "\nEnter a value to view records (or '0' to exit): ";
                    std::string input;
                    std::getline(std::cin, input);
                    if (input == "0") break;
                    try {
                        value = std::stoi(input);
                        viewSubset<int>(index, value);
                    }
                    catch (const std::invalid_argument&) {
                        std::cout << "Invalid input. Please enter an integer value.\n";
                    }
                } while (true);

            }
            else if (fieldName == "balance") {
                TreeMap<double, std::vector<Record>> index;
                indexData<double>(records, fieldName, index);
                displayIndex<double>(index);

                double value;
                do {
                    std::cout << "\nEnter a value to view records (or '0' to exit): ";
                    std::string input;
                    std::getline(std::cin, input);
                    if (input == "0") break;
                    try {
                        value = std::stod(input);
                        viewSubset<double>(index, value);
                    }
                    catch (const std::invalid_argument&) {
                        std::cout << "Invalid input. Please enter a numeric value.\n";
                    }
                } while (true);

            }
            else {
                TreeMap<std::string, std::vector<Record>> index;
                indexData<std::string>(records, fieldName, index);
                displayIndex<std::string>(index);

                std::string value;
                do {
                    std::cout << "\nEnter a value to view records (or '0' to exit): ";
                    std::getline(std::cin, value);
                    if (value == "0") break;

                    viewSubset<std::string>(index, value);

                } while (true);
            }

        }
        else if (choice == 0) {
            std::cout << "Exiting program.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << "\n";

    } while (true);

    return 0;
}
