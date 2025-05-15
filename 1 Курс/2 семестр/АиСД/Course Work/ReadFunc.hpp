#include <cctype>
#include <iostream>
#include <fstream>
#include "RedBlackTree.hpp"

RedBlackTree<std::string> extractWordsFromFile(const std::string &filePath) {
    RedBlackTree<std::string> words;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return words;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (isalpha(ch)) {
            word += tolower(ch);
        } else if (!word.empty()) {
            words.insert(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.insert(word);
    }

    file.close();
    return words;
}