#include "BinarySearchTree.hpp"

int main() {
    BSTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(36);
    tree.insert(60);
    tree.output();
    std::cout << std::endl;
    tree.eraseAllList();
    tree.output();
}
