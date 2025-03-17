//
// Created by jdh99 on 3/15/2025.
//

#ifndef MYSHAREDPTR_HPP
#define MYSHAREDPTR_HPP
#include <cstddef>
#include <iostream>
#include <ostream>

template <typename T>
class MySharedPtr {
public:
    explicit MySharedPtr(T *ptr);
    ~MySharedPtr();
    T & operator*() const;
    T * operator->() const;
    MySharedPtr (const MySharedPtr &other);
    MySharedPtr & operator=(const MySharedPtr &other);
    MySharedPtr(MySharedPtr && other) = delete;
    MySharedPtr & operator=(MySharedPtr && other) = delete;


private:
    T* ptr_;
    std::size_t* cnt {nullptr};
};

template<typename T>
MySharedPtr<T>::MySharedPtr(T *ptr): ptr_(ptr){
    cnt = new std::size_t(1);
}

template<typename T>
MySharedPtr<T>::~MySharedPtr() {
    std::cout << cnt << std::endl;
    if (cnt && 0 == --(*cnt)) {
        delete cnt;
        delete ptr_;
    }
}

template<typename T>
T & MySharedPtr<T>::operator*() const {
    return *ptr_;
}

template<typename T>
T * MySharedPtr<T>::operator->() const {
    return ptr_;
}

template<typename T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr &other) {
    ptr_ = other.ptr_;
    cnt = other.cnt;
    (*cnt)++;
}

template<typename T>
MySharedPtr<T> & MySharedPtr<T>::operator=(const MySharedPtr &other) {
    if (this != &other) {
        if (cnt && 0 == --(*cnt)) {
            delete cnt;
            delete ptr_;
        }
        ptr_ = other.ptr_;
        cnt = other.cnt;
        (*cnt)++;
    }
    return *this;
}



#endif //MYSHAREDPTR_HPP
