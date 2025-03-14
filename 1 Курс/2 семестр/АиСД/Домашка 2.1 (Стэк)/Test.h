#ifndef TEST_H
#define TEST_H
#include "StackArray.hpp"
#include <cassert>


inline void testInitializationStackArrayWithHugeSize();
void testInitializationStackArrayWithWrongNegativeSize();
void testMethodPopWithoutItemsInStackArray();
void testMethodPopWithItemsInStackArray();
void testPushWithItemsWhichCountLessThanStackArraySize();
void testPushWithItemsWhichCountGreaterThanStackArraySize();
void testMethodIsEmptyWithEmptyStackArray();
void testMethodIsEmptyWithItemsInStackArray();
void testCheckBracketsWithRightExpression();
void testCheckBracketsWithStackOverflowExpression();
void testCheckBracketsWithEmptyStackExpression();

inline void main_test() {
    void testInitializationStackArrayWithWrongNegativeSize();
    void testInitializationStackArrayWithHugeSize();
    void testMethodPopWithoutItemsInStackArray();
    void testMethodPopWithItemsInStackArray();
    void testPushWithItemsWhichCountLessThanStackArraySize();
    void testPushWithItemsWhichCountGreaterThanStackArraySize();
    void testMethodIsEmptyWithEmptyStackArray();
    void testMethodIsEmptyWithItemsInStackArray();
    void testCheckBracketsWithRightExpression();
    void testCheckBracketsWithStackOverflowExpression();
    void testCheckBracketsWithEmptyStackExpression();
}

inline void testInitializationStackArrayWithWrongNegativeSize() {
    try {
        StackArray<int> stackArray(-10);
        assert(false);
    } catch (const WrongStackSize &e) {
        assert(true);
    }
}

inline void testInitializationStackArrayWithHugeSize() {
    try {
        StackArray<int> stackArray(2000000000000);
        assert(false);
    } catch (const std::bad_alloc &e) {
        assert(true);
    }
}

inline void testMethodPopWithoutItemsInStackArray() {
    StackArray<int> stackArray(10);
    try {
        stackArray.pop();
        assert(false);
    } catch (const StackUnderflow &e) {
        assert(true);
    }
}

inline void testMethodPopWithItemsInStackArray() {
    StackArray<int> stackArray(10);
    stackArray.push(10);
    assert(stackArray.pop() == 10);
}

inline void testPushWithItemsWhichCountLessThanStackArraySize() {
    StackArray<int> stackArray(10);
    stackArray.push(10);
    stackArray.push(20);
    stackArray.push(30);
    assert(stackArray.pop() == 30);
}

inline void testPushWithItemsWhichCountGreaterThanStackArraySize() {
    StackArray<int> stackArray(2);
    stackArray.push(10);
    stackArray.push(20);
    try {
        stackArray.push(30);
    } catch (const StackOverflow &e) {
        assert(true);
    }
}

inline void testMethodIsEmptyWithEmptyStackArray() {
    StackArray<int> stackArray(1);
    assert(stackArray.isEmpty());
}

inline void testMethodIsEmptyWithItemsInStackArray() {
    StackArray<int> stackArray(1);
    stackArray.push(10);
    assert(stackArray.isEmpty() == false);
}

inline void testCheckBracketsWithRightExpression() {
    assert(StackArray<std::string>::checkBalanceBrackets("([{}])", 5));
}

inline void testCheckBracketsWithStackOverflowExpression() {
    try {
        StackArray<std::string>::checkBalanceBrackets("([{([{()}])}])", 5);
    } catch (StackOverflow &e) {
        assert(true);
    }
}

inline void testCheckBracketsWithEmptyStackExpression() {
    assert(StackArray<std::string>::checkBalanceBrackets("", 10));
}
#endif //TEST_H
