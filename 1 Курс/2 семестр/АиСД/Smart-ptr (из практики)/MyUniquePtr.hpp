//
// Created by jdh99 on 3/15/2025.
//

#ifndef MYUNIQUE_PTR_HPP
#define MYUNIQUE_PTR_HPP
#include <iostream>
template <typename T>
class MyUniquePtr {
public:
    explicit MyUniquePtr(T *ptr);
    ~MyUniquePtr();
    T & operator*() const;
    T * operator->() const;
    MyUniquePtr(const MyUniquePtr &) = delete;
    MyUniquePtr(MyUniquePtr &&) = delete;
    MyUniquePtr & operator=(const MyUniquePtr &) = delete;
    MyUniquePtr & operator=(MyUniquePtr &&) = delete;
private:
    T *ptr_;
};

template<typename T>
MyUniquePtr<T>::MyUniquePtr(T *ptr): ptr_(ptr) {
    if (ptr_ != nullptr ) {
        throw std::invalid_argument("Invalid Pointer");
    }
}

template<typename T>
MyUniquePtr<T>::~MyUniquePtr() {
    delete ptr_;
}

template<typename T>
T & MyUniquePtr<T>::operator*() const {
    return *ptr_;
}

template<typename T>
T * MyUniquePtr<T>::operator->() const {
    return ptr_;
}


#endif
