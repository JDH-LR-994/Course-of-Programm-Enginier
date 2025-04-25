//
// Created by jdh99 on 3/26/2025.
//

#ifndef QUEUELIST_HPP
#pragma once
#define QUEUELIST_HPP
#include <stdexcept>
#include <iterator>

template<class T>
struct Node {
    T data;
    Node *next;

    explicit Node(const T &data, Node *next = nullptr) : data(data), next(next) {
    }
};

class QueueOverflow : public std::runtime_error {
public:
    QueueOverflow() : std::runtime_error("Queue overflow") {
    }
};

class QueueUnderflow : public std::runtime_error {
public:
    QueueUnderflow() : std::runtime_error("Queue underflow") {
    }
};

template<class T>
class Queue {
public:
    virtual ~Queue() = default;

    virtual void enQueue(const T &e) = 0; // Добавление элемента в очередь
    virtual T deQueue() = 0; // Удаление элемента из очереди

    [[nodiscard]] virtual bool isEmpty() const noexcept = 0; // Проверка очереди на пустоту
};

template<typename T>
class QueueListIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit QueueListIterator(Node<T> *node) : current_(node) {
    }

    reference operator*() const;

    pointer operator->() const;

    QueueListIterator &operator++();

    QueueListIterator operator++(int);

    bool operator==(const QueueListIterator &other) const { return current_ == other.current_; }
    bool operator!=(const QueueListIterator &other) const { return !(*this == other); }

private:
    Node<T> *current_;
};


template<class T>
class QueueList final : public Queue<T> {
public:
    using iterator = QueueListIterator<T>;
    using const_iterator = QueueListIterator<const T>;

    void enQueue(const T &e) override;

    T deQueue() override;

    [[nodiscard]] int size() const;

    T front() const;

    [[nodiscard]] bool isEmpty() const noexcept override;

    ~QueueList() override;

    iterator begin() noexcept { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    const_iterator begin() const noexcept { return const_iterator(head); }
    const_iterator end() const { return const_iterator(nullptr); }

private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    size_t size_ = 0;
};


template<typename T>
typename QueueListIterator<T>::reference QueueListIterator<T>::operator*() const {
    if (!current_) throw std::out_of_range("Dereferencing end iterator");
    return current_->data;
}

template<typename T>
typename QueueListIterator<T>::pointer QueueListIterator<T>::operator->() const {
    if (!current_) throw std::out_of_range("Dereferencing end iterator");
    return &current_->data;
}

template<typename T>
QueueListIterator<T> &QueueListIterator<T>::operator++() {
    if (current_) current_ = current_->next;
    return *this;
}

template<typename T>
QueueListIterator<T> QueueListIterator<T>::operator++(int) {
    QueueListIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T>
void QueueList<T>::enQueue(const T &e) {
    try {
        auto *newNode = new Node<T>(e);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size_++;
    } catch (std::bad_alloc &) {
        throw QueueOverflow();
    }
}

template<class T>
T QueueList<T>::deQueue() {
    if (isEmpty()) {
        throw QueueUnderflow();
    }
    T result = head->data;
    Node<T> *temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    size_--;
    return result;
}

template<class T>
int QueueList<T>::size() const {
    return size_;
}

template<class T>
T QueueList<T>::front() const {
    return head->data;
}


template<class T>
bool QueueList<T>::isEmpty() const noexcept { return head == nullptr; }

template<class T>
QueueList<T>::~QueueList() {
    while (head) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

#endif //QUEUELIST_HPP
