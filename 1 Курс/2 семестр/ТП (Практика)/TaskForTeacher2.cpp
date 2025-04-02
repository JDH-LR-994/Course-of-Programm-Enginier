//
// Created by jdh99 on 3/22/2025.
//
#include <iostream>
#include <string>
#include <sstream>

int main() {
    //-----чтение строки с пробелами, использование манипулятора ws
    std::string str;
    std::getline(std::cin, str);
    std::cout << str << '\n';
    std::getline(std::cin >> std::ws, str);
    std::cout << str << '\n';
    std::getline(std::cin, str);
    std::cout << str << '\n';


    //-----istringstream; строка, как источник ввода

    char c1, c2, c3;
    std::istringstream("a b c") >> c1 >> c2 >> c3;
    std::cout << "Default  behavior: c1 = " << c1
            << " c2 = " << c2 << " c3 = " << c3 << '\n';

    // использование манипулятора noskipws
    std::istringstream("a b c") >> std::noskipws >> c1 >> c2 >> c3;
    std::cout << "noskipws behavior: c1 = " << c1
            << " c2 = " << c2 << " c3 = " << c3 << '\n';
}
