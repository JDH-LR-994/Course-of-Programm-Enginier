#include "Test.h"

//void testGetPostfixFromInfixWithWrongSize();

int main() {
    testInitializationStackArrayWithWrongNegativeSize();
    testInitializationStackArrayWithHugeSize();
    testMethodPopWithoutItemsInStackArray();
    testMethodPopWithItemsInStackArray();
    testPushWithItemsWhichCountLessThanStackArraySize();
    testPushWithItemsWhichCountGreaterThanStackArraySize();
    testMethodIsEmptyWithEmptyStackArray();
    testMethodIsEmptyWithItemsInStackArray();
    testCheckBracketsWithRightExpression();
    testCheckBracketsWithStackOverflowExpression();
    testCheckBracketsWithEmptyStackExpression();
}



//void testGetPostfixFromInfixWithWrongSize() {}
