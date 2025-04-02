//
// Created by jdh99 on 3/26/2025.
//

#ifndef TEST_HPP
#pragma once
#define TEST_HPP
#include <cassert>
#include "QueueList.hpp"

inline void main_test();
inline void correctWorkIteratorWithQueueListWithoutElement();
inline void correctWorkIteratorWithQueueListWithElement();
inline void thenMethodEnQueueListUsedThenQueueIsNotEmpty();
inline void thenItemAddAndRemoveThenQueueIsEmpty();
inline void thenTryingRemoveElementWithEmptyQueueWhenCatchQueueListUnderflow();

inline void main_test() {
    correctWorkIteratorWithQueueListWithoutElement();
    correctWorkIteratorWithQueueListWithElement();
    thenMethodEnQueueListUsedThenQueueIsNotEmpty();
    thenItemAddAndRemoveThenQueueIsEmpty();
    thenTryingRemoveElementWithEmptyQueueWhenCatchQueueListUnderflow();
}

inline void correctWorkIteratorWithQueueListWithoutElement() {
    QueueList<size_t> queueList;
    for (auto i: queueList) {
        assert(false);
    }
}

inline void correctWorkIteratorWithQueueListWithElement() {
    QueueList<size_t> queueList;
    queueList.enQueue(10);
    for (auto i: queueList) {
        assert(i == 10);
    }
}

inline void thenMethodEnQueueListUsedThenQueueIsNotEmpty() {
    QueueList<size_t> queueList;
    queueList.enQueue(10);
    assert(!queueList.isEmpty());
}

inline void thenItemAddAndRemoveThenQueueIsEmpty() {
    QueueList<size_t> queueList;
    queueList.enQueue(10);
    queueList.deQueue();
    assert(queueList.isEmpty());
}

inline void thenTryingRemoveElementWithEmptyQueueWhenCatchQueueListUnderflow() {
    try {
        QueueList<size_t> queueList;
        queueList.deQueue();
    } catch (...) {
        assert(true);
    }
}


#endif //TEST_HPP
