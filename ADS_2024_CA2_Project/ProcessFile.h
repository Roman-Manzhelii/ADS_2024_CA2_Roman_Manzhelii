#pragma once

#include <string>
#include "TreeMap.h"

void processFile(const std::string& filename, TreeMap<char, BinaryTree<std::string>>& wordMap);
void displayLetters(const TreeMap<char, BinaryTree<std::string>>& wordMap);
void displayWordsForLetter(TreeMap<char, BinaryTree<std::string>>& wordMap, char letter);
