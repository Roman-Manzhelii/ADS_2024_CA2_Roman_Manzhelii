#include "ProcessFile.h"
#include <iostream>
#include <fstream>
#include <cctype>

// Function to process the text file
void processFile(const std::string& filename, TreeMap<char, BinaryTree<std::string>>& wordMap) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string word;
    while (infile >> word) {
        // Clean the word: remove punctuation, convert to lowercase
        std::string cleanedWord;
        for (char ch : word) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                cleanedWord += std::tolower(static_cast<unsigned char>(ch));
            }
        }

        if (!cleanedWord.empty()) {
            char firstLetter = cleanedWord[0];
            // Check if the letter is already in the map
            if (!wordMap.containsKey(firstLetter)) {
                BinaryTree<std::string> wordSet;
                wordSet.add(cleanedWord);
                wordMap.put(firstLetter, wordSet);
            }
            else {
                // Add the word to the existing set
                BinaryTree<std::string>& wordSet = wordMap.get(firstLetter);
                if (!wordSet.containsKey(cleanedWord)) {
                    wordSet.add(cleanedWord);
                }
            }
        }
    }

    infile.close();
}


void displayLetters(const TreeMap<char, BinaryTree<std::string>>& wordMap) {
    std::cout << "Letters with words in the file:\n";
    BinaryTree<char> letters = wordMap.keySet();
    letters.printInOrder();
    std::cout << std::endl;
}

void displayWordsForLetter(TreeMap<char, BinaryTree<std::string>>& wordMap, char letter) {
    letter = std::tolower(static_cast<unsigned char>(letter));
    if (wordMap.containsKey(letter)) {
        BinaryTree<std::string>* words = wordMap.getPointer(letter);
        if (words != nullptr) {
            std::cout << "Words starting with '" << letter << "':\n";
            words->printInOrder();
            std::cout << std::endl;
        }
        else {
            std::cout << "No words starting with '" << letter << "' found.\n";
        }
    }
    else {
        std::cout << "No words starting with '" << letter << "' found.\n";
    }
}

