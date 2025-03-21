#pragma once
#include <stdexcept>

template<class T>
class Stack {
public:
    virtual ~Stack() = default;

    virtual void push(const T &e) = 0; // Добавление элемента в стек
    virtual T pop() = 0; // Удаление верхнего элемента
    virtual bool isEmpty() = 0; // Проверка стека на пустоту
};


class WrongStackSize final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Wrong stack size";
    }
};

class StackOverflow final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Stack overflow";
    }
};

class StackUnderflow final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Stack underflow";
    }
};

template<typename T>
class StackArray final : public Stack<T> {
    T *data;
    std::size_t size_;
    std::size_t capacity_;

public:
    explicit StackArray<T>(long long size);

    StackArray(const StackArray &other)
        : data(other.data),
          size_(other.size_),
          capacity_(other.capacity_) {
    }

    StackArray(StackArray &&other) noexcept
        : data(other.data),
          size_(other.size_),
          capacity_(other.capacity_) {
    }

    StackArray &operator=(const StackArray &other);

    StackArray &operator=(StackArray &&other) noexcept;

    void push(const T &e) override;

    T pop() override;

    bool isEmpty() override { return size_ == 0; }
    ~StackArray() override { delete[] data; }

};

template<typename T>
StackArray<T>::StackArray(const long long size) {
    //Почему long long у size?
    //std::size_t не давал бы смысл для WrongStackSize (нет отрицательных чисел)
    //int - не даёт возможности в bad_alloc уйти

    if (size <= 0) {
        throw WrongStackSize();
    }
    try {
        data = new T[size];
    } catch (const std::bad_alloc &) {
        throw std::bad_alloc();
    }
    capacity_ = size;
    size_ = 0;
}

template<typename T>
StackArray<T> &StackArray<T>::operator=(const StackArray &other) {
    if (this == &other)
        return *this;
    data = other.data;
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
}

template<typename T>
StackArray<T> &StackArray<T>::operator=(StackArray &&other) noexcept {
    if (this == &other)
        return *this;
    data = other.data;
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
}

template<typename T>
void StackArray<T>::push(const T &e) {
    if (capacity_ == size_) {
        throw StackOverflow();
    }
    data[size_++] = e;
}

template<typename T>
T StackArray<T>::pop() {
    if (this->isEmpty()) {
        throw StackUnderflow();
    }
    return data[--size_];
}