#ifndef TEST_H
#define TEST_H
#include "StackArray.hpp"
#include "TaskFunc.hpp"
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

inline void testInitializationStackArrayWithWrongNegativeSize() {
    try {
        StackArray<int> stackArray(-10);
        assert(false);
    } catch ([[maybe_unused]] const WrongStackSize &e) {
        assert(true);
    }
}

inline void testInitializationStackArrayWithHugeSize() {
    try {
        StackArray<int> stackArray(2000000000000);
        assert(false);
    } catch ([[maybe_unused]] const std::bad_alloc &e) {
        assert(true);
    }
}

inline void testMethodPopWithoutItemsInStackArray() {
    StackArray<int> stackArray(10);
    try {
        stackArray.pop();
        assert(false);
    } catch ([[maybe_unused]] const StackUnderflow &e) {
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
    } catch ([[maybe_unused]] const StackOverflow &e) {
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
    assert(TaskFunc::checkBalanceBrackets("([{}])", 5));
}

inline void testCheckBracketsWithStackOverflowExpression() {
    try {
        TaskFunc::checkBalanceBrackets("([{([{()}])}])", 5);
    } catch ([[maybe_unused]] StackOverflow &e) {
        assert(true);
    }
}

inline void testCheckBracketsWithEmptyStackExpression() {
    assert(TaskFunc::checkBalanceBrackets("", 10));
}

inline void testDivision() {
    const char* infix = "8/2+3";
    char postfix[100];
    constexpr size_t stackSize = 100;

    TaskFunc::getPostfixFromInfix(infix, postfix, stackSize);
    assert(std::string(postfix) == "82/3+");
}

inline void testNestedBrackets() {
    const char* infix = "3*(4-(2+1))";
    char postfix[100];
    constexpr size_t stackSize = 100;

    TaskFunc::getPostfixFromInfix(infix, postfix, stackSize);
    assert(std::string(postfix) == "3421+-*");
}

inline void testExpressionWithBrackets() {
    const char* infix = "3*(4+2)";
    char postfix[100];
    constexpr size_t stackSize = 100;

    TaskFunc::getPostfixFromInfix(infix, postfix, stackSize);
    assert(std::string(postfix) == "342+*");
}

inline void testMultipleOperators() {
    const char* infix = "3+4*2-1";
    char postfix[100];
    constexpr size_t stackSize = 100;

    TaskFunc::getPostfixFromInfix(infix, postfix, stackSize);
    assert(std::string(postfix) == "342*+1-");
}

inline void testSimpleExpression() {
    const char* infix = "3+4";
    char postfix[100];
    constexpr size_t stackSize = 100;

    TaskFunc::getPostfixFromInfix(infix, postfix, stackSize);
    assert(std::string(postfix) == "34+");
}

#endif //TEST_H
