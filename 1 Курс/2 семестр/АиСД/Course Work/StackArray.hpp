#pragma once

template<class T>
class Stack {
public:
    virtual ~Stack() = default;

    virtual void push(const T &e) = 0; // Добавление элемента в стек
    virtual T pop() = 0; // Удаление верхнего элемента
    [[nodiscard]] virtual bool isEmpty() const = 0;  // Добавлен const
    [[nodiscard]] virtual bool isFull() const = 0;   // Новый метод
    virtual const T& top() const = 0;  // Новый метод
};


class WrongStackSize final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override  {
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
    explicit StackArray<T>(size_t size);

    StackArray(const StackArray &other)
        : data(new T[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_) {
        std::copy(other.data, other.data + size_, data);
    }

    StackArray(StackArray &&other) noexcept:
        data(other.data),
        size_(other.size_),
        capacity_(other.capacity_) {
            other.data = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
    }
    [[nodiscard]] bool isFull() const override;

    StackArray &operator=(const StackArray &other);

    StackArray &operator=(StackArray &&other) noexcept;

    void push(const T &e) override;

    const T& top() const override;

    T pop() override;

    [[nodiscard]] bool isEmpty() const override { return size_ == 0; }
    ~StackArray() override { delete[] data; }
};

template<typename T>
StackArray<T>::StackArray(const size_t size) {
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
bool StackArray<T>::isFull() const {
    return size_ == capacity_;
}

template<typename T>
StackArray<T> & StackArray<T>::operator=(const StackArray &other) {
    if (this != &other) {
        delete[] data;
        data = new T[other.capacity_];
        std::copy(other.data, other.data + other.size_, data);
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    return *this;
}

template<typename T>
StackArray<T> & StackArray<T>::operator=(StackArray &&other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
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
const T& StackArray<T>::top() const {
    if (isEmpty()) {
        throw StackUnderflow();
    }
    return data[size_ - 1];
}

template<typename T>
T StackArray<T>::pop() {
    if (this->isEmpty()) {
        throw StackUnderflow();
    }
    return data[--size_];
}
