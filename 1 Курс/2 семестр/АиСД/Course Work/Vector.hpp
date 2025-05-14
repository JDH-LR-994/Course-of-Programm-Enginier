#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <stdexcept>

template<typename T>
class Vector {
    T *data_;
    std::size_t capacity_;
    std::size_t size_;

    void resize(std::size_t new_capacity);

public:
    class Iterator {
        T *ptr;

    public:
        explicit Iterator(T *p);

        T &operator*() const;

        T *operator->() const;

        Iterator &operator++();

        Iterator operator++(int);
    };

    class ConstIterator {
        const T* ptr;

    public:
        explicit ConstIterator(const T* p);

        const T& operator*() const;

        const T* operator->() const;

        ConstIterator& operator++();

        ConstIterator operator++(int);

        bool operator==(const ConstIterator& other) const;

        bool operator!=(const ConstIterator& other) const;

        // Для совместимости с STL алгоритмами
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::forward_iterator_tag;
    };

    Vector();

    explicit Vector(std::size_t initial_size);

    ~Vector();

    Vector(const Vector &other);

    Vector &operator=(const Vector &other);

    void push_back(const T &value);

    void pop_back();

    T &operator[](std::size_t index);

    const T &operator[](std::size_t index) const;

    std::size_t get_size() const;

    std::size_t get_capacity() const;

    bool empty() const;

    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }

    ConstIterator begin() const { return ConstIterator(data_); }
    ConstIterator end() const { return ConstIterator(data_ + size_); }

    ConstIterator cbegin() const { return ConstIterator(data_); }
    ConstIterator cend() const { return ConstIterator(data_ + size_); }

    void clear();
};

template<typename T>
void Vector<T>::resize(std::size_t new_capacity) {
    T *new_data = new T[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

template<typename T>
Vector<T>::Iterator::Iterator(T *p): ptr(p) {
}

template<typename T>
T & Vector<T>::Iterator::operator*() const { return *ptr; }

template<typename T>
T * Vector<T>::Iterator::operator->() const { return ptr; }

template<typename T>
typename Vector<T>::Iterator & Vector<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++ptr;
    return tmp;
}

template<typename T>
Vector<T>::ConstIterator::ConstIterator(const T *p): ptr(p) {}

template<typename T>
const T & Vector<T>::ConstIterator::operator*() const { return *ptr; }

template<typename T>
const T * Vector<T>::ConstIterator::operator->() const { return ptr; }

template<typename T>
typename Vector<T>::ConstIterator & Vector<T>::ConstIterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int) {
    ConstIterator tmp = *this;
    ++ptr;
    return tmp;
}

template<typename T>
bool Vector<T>::ConstIterator::operator==(const ConstIterator &other) const {
    return ptr == other.ptr;
}

template<typename T>
bool Vector<T>::ConstIterator::operator!=(const ConstIterator &other) const {
    return ptr != other.ptr;
}

template<typename T>
Vector<T>::Vector(): data_(nullptr), capacity_(0), size_(0) {
}

template<typename T>
Vector<T>::Vector(std::size_t initial_size): capacity_(initial_size), size_(initial_size) {
    data_ = new T[capacity_];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template<typename T>
Vector<T>::Vector(const Vector &other): capacity_(other.capacity_), size_(other.size_) {
    data_ = new T[capacity_];
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (this != &other) {
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template<typename T>
void Vector<T>::push_back(const T &value) {
    if (size_ >= capacity_) {
        resize(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}

template<typename T>
void Vector<T>::pop_back() {
    if (size_ == 0) {
        throw std::out_of_range("Vector is empty");
    }
    --size_;
}

template<typename T>
T &Vector<T>::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
const T &Vector<T>::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
std::size_t Vector<T>::get_size() const {
    return size_;
}

template<typename T>
std::size_t Vector<T>::get_capacity() const {
    return capacity_;
}

template<typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void Vector<T>::clear() {
    size_ = 0;
}

#endif //VECTOR_HPP
