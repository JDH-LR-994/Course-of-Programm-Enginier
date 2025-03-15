//
// Created by jdh99 on 3/15/2025.
//

#ifndef OBJECTPTR_H
#define OBJECTPTR_H
#include <iostream>

template <typename T>
class ObjectPtr {

public:
    explicit ObjectPtr(T *ptr):ptr_(ptr) {
        if (ptr_ == nullptr) {
            throw std::invalid_argument("Invalid pointer");
        }
    }
    ~ObjectPtr() {delete ptr_;} // деструктор
    T & operator*() const; // перегруженные операторы
    T * operator->() const;
private:
    T *ptr_; // «сырой» указатель на объект
    ObjectPtr(const T &) = delete;
    ObjectPtr(T &&) = delete;
    ObjectPtr & operator=(const T &) = delete;
    ObjectPtr & operator=(T &&) = delete;
};


#endif //OBJECTPTR_H
