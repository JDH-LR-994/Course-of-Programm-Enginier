#include "tests.hpp"

int main() {
    testEmptyTree();
    testSingleNodeTree();
    testTreeWithLeaves();
    testComplexTree();
    testMoveSemantics();
    testInsertDuplicate();
    testMultipleEraseOperations();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}