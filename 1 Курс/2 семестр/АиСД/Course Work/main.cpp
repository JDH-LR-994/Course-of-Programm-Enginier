// #include "Test.hpp"
//
// int main() {
//     mainTest();
// }


#include "ReadFunc.hpp"

int main() {
    std::string filePath = "example.txt";
    auto tree = extractWordsFromFile(filePath);

    auto res = tree.getTopKFrequent(3);

    for (auto r : res) {
        std::cout <<r.first << " " << r.second << std::endl;
    }
}