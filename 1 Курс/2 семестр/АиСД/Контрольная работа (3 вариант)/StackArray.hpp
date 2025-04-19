//
// Created by jdh99 on 19.04.2025.
//

#ifndef STACKARRAY_HPP
#define STACKARRAY_HPP
#include <exception>
#include <new>


template<class T>
class StackArray {
    T *array_;
    std::size_t size_ = 0;
    std::size_t capacity_;

public:
    explicit StackArray(std::size_t size);

    StackArray(const StackArray &other) = delete;

    StackArray &operator=(const StackArray &other) = delete;

    StackArray(StackArray &&other) = delete;

    StackArray &operator=(StackArray &&other) = delete;

    void push_back(const T &value);

    std::size_t size() const { return size_; };

    T pop();

    ~StackArray() {
        delete[] array_;
    }
};

template<class T>
StackArray<T>::StackArray(std::size_t size) {
    try {
        array_ = new T[size];
    } catch (const std::bad_alloc &) {
        throw std::bad_alloc();
    }
    capacity_ = size;
    size_ = 0;
}

template<class T>
void StackArray<T>::push_back(const T &value) {
    if (size_ == capacity_) {
        throw std::exception();
    }
    array_[size_++] = value;
}

template<class T>
T StackArray<T>::pop() {
    if (size_ == 0) {
        throw std::exception();
    }
    return array_[--size_];
}

#endif //STACKARRAY_HPP
