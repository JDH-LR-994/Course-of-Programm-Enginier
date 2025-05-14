// #include "Test.hpp"
//
// int main() {
//     mainTest();
// }


#include "ReadFunc.hpp"

int main() {
    RedBlackTree<std::string> tree;
    std::string filePath = "example.txt";

    Vector<std::string> words = extractWordsFromFile(filePath);

    insertWordsIntoRBTree(tree, words);

    for (auto word : tree) {
        std::cout << word << " " << tree.get_frequency(word) <<  std::endl;
    }
}