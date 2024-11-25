#pragma once
#include <string>
#include <vector>
#include "Record.h"
#include "TreeMap.h"
#include <functional>
#include <iostream>
#include <stdexcept>

void loadData(const std::string& filename, std::vector<Record>& records);

void displayKey(const std::string& key);
void displayKey(int key);
void displayKey(double key);

// KeyExtractor is a template structure that helps extract key values ​​from a (Record)
// based on the (KeyType) and (fieldName).
template<typename KeyType>
struct KeyExtractor;

template<>
struct KeyExtractor<int> {
    static int getKey(const Record& record, const std::string& fieldName) {
        if (fieldName == "age") {
            return record.age;
        }
        throw std::invalid_argument("Invalid fieldName for int KeyType");
    }
};

template<>
struct KeyExtractor<double> {
    static double getKey(const Record& record, const std::string& fieldName) {
        if (fieldName == "balance") {
            return record.balance;
        }
        throw std::invalid_argument("Invalid fieldName for double KeyType");
    }
};

template<>
struct KeyExtractor<std::string> {
    static std::string getKey(const Record& record, const std::string& fieldName) {
        if (fieldName == "name") {
            return record.name;
        }
        else if (fieldName == "email") {
            return record.email;
        }
        else if (fieldName == "country") {
            return record.country;
        }
        throw std::invalid_argument("Invalid fieldName for std::string KeyType");
    }
};

template<typename KeyType>
void indexData(const std::vector<Record>& records, const std::string& fieldName, TreeMap<KeyType, std::vector<Record>>& index) {
    index.clear();

    try {
        for (const auto& record : records) {
            KeyType key = KeyExtractor<KeyType>::getKey(record, fieldName);

            if (!index.containsKey(key)) {
                std::vector<Record> recordList;
                recordList.push_back(record);
                index.put(key, recordList);
            }
            else {
                index.get(key).push_back(record);
            }
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

template<typename KeyType>
void displayIndex(TreeMap<KeyType, std::vector<Record>>& index) {
    BinaryTree<KeyType> keysTree = index.keySet();

    // Traverse the keysTree and display each key and the count
    std::function<void(BSTNode<KeyType>*)> traverse;
    traverse = [&](BSTNode<KeyType>* node) {
        if (node != nullptr) {
            traverse(node->getLeft());

            KeyType key = node->getItem();
            int count = index.get(key).size();

            std::cout << "Value: ";
            displayKey(key);
            std::cout << ", Count: " << count << std::endl;

            traverse(node->getRight());
        }
        };

    traverse(keysTree.root);
}

template<typename KeyType>
void viewSubset(TreeMap<KeyType, std::vector<Record>>& index, const KeyType& value) {
    if (index.containsKey(value)) {
        std::vector<Record>& records = index.get(value);

        std::cout << "Records with value '";
        displayKey(value);
        std::cout << "':\n";

        for (const auto& record : records) {
            std::cout << record << std::endl;
        }
    }
    else {
        std::cout << "No records found with value '";
        displayKey(value);
        std::cout << "'.\n";
    }
}
