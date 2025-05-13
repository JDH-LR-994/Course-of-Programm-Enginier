#ifndef READFUNC_HPP
#define READFUNC_HPP
#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include <string>
#include <cctype>

Vector<std::string> extractWordsFromFile(const std::string& filePath) {
    Vector<std::string> words;
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
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    file.close();
    return words;
}
#endif //READFUNC_HPP
