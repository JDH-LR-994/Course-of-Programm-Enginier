#include <cassert>
#include "StackArray.hpp"

void testInitializationStackArrayWithWrongNegativeSize();
void testInitializationStackArrayWithHugeSize();
void testMethodPopWithoutItemsInStackArray();
void testMethodPopWithItemsInStackArray();
void testPushWithItemsWhichCountLessThanStackArraySize();
void testPushWithItemsWhichCountGreaterThanStackArraySize();
void testMethodIsEmptyWithEmptyStackArray();
void testMethodIsEmptyWithItemsInStackArray();

int main() {
    testInitializationStackArrayWithWrongNegativeSize();
    testInitializationStackArrayWithHugeSize();
    testMethodPopWithoutItemsInStackArray();
    testMethodPopWithItemsInStackArray();
    testPushWithItemsWhichCountLessThanStackArraySize();
    testPushWithItemsWhichCountGreaterThanStackArraySize();
    testMethodIsEmptyWithEmptyStackArray();
    testMethodIsEmptyWithItemsInStackArray();
}

void testInitializationStackArrayWithWrongNegativeSize() {
    try {
        StackArray<int> stackArray(-10);
        assert(false);
    } catch (const WrongStackSize &e) {
        assert(true);
    }
}
void testInitializationStackArrayWithHugeSize() {
    try {
        StackArray<int> stackArray(2000000000000);
        assert(false);
    } catch (const std::bad_alloc &e) {
        assert(true);
    }
}
void testMethodPopWithoutItemsInStackArray() {
    StackArray<int> stackArray(10);
    try {
        stackArray.pop();
        assert(false);
    } catch (const StackUnderflow &e) {
        assert(true);
    }
}
void testMethodPopWithItemsInStackArray() {
    StackArray<int> stackArray(10);
    stackArray.push(10);
    assert(stackArray.pop() == 10);
}
void testPushWithItemsWhichCountLessThanStackArraySize() {
    StackArray<int> stackArray(10);
    stackArray.push(10);
    stackArray.push(20);
    stackArray.push(30);
    assert(stackArray.pop() == 30);
}
void testPushWithItemsWhichCountGreaterThanStackArraySize() {
    StackArray<int> stackArray(2);
    stackArray.push(10);
    stackArray.push(20);
    try {
        stackArray.push(30);
    } catch (const StackOverflow &e) {
        assert(true);
    }
}
void testMethodIsEmptyWithEmptyStackArray() {
    StackArray<int> stackArray(1);
    assert(stackArray.isEmpty());
}
void testMethodIsEmptyWithItemsInStackArray() {
    StackArray<int> stackArray(1);
    stackArray.push(10);
    assert(stackArray.isEmpty() == false);
}
