//
// Created by jdh99 on 13.05.2025.
//

#include "HashTable.hpp"
#include <cstring>

HashTable::Node::Node(const char *k): key(strdup(k)), next(nullptr) {}

HashTable::Node::~Node() {
    delete[] key;
}

HashTable::HashTable(int size): size_(size), table_(new Node*[size_]()) {
    for (int i = 0; i < size_; ++i) {
        table_[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
    delete[] table_;
}

void HashTable::clear() {
    for (int i = 0; i < size_; ++i) {
        Node* current = table_[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        table_[i] = nullptr;
    }
}

int HashTable::hash(const char *key) const {
    int h = 0;
    while (*key) {
        h += *key++;
    }
    return h % size_;
}

bool HashTable::insert(const char *key) {
    if (key == nullptr || contains(key)) {
        return false;
    }

    int index = hash(key);
    Node* newNode = new Node(key);

    newNode->next = table_[index];
    table_[index] = newNode;

    return true;
}

bool HashTable::remove(const char *key) {
    int index = hash(key);
    Node* current = table_[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (strcmp(current->key, key) == 0) {
            if (prev == nullptr) {
                table_[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void HashTable::printChain(int hashValue) const {
    if (hashValue < 0 || hashValue >= size_) {
        std::cout << "Invalid hash value\n";
        return;
    }

    std::cout << "Chain for hash " << hashValue << ": ";
    Node* current = table_[hashValue];

    if (current == nullptr) {
        std::cout << "empty";
    } else {
        while (current != nullptr) {
            std::cout << current->key;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
    }
    std::cout << std::endl;
}

void HashTable::printAll() const {
    for (int i = 0; i < size_; ++i) {
        Node* current = table_[i];
        if (current != nullptr) {
            std::cout << "[" << i << "]: ";
            while (current != nullptr) {
                std::cout << current->key;
                if (current->next != nullptr) {
                    std::cout << " -> ";
                }
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
}

bool HashTable::contains(const char *key) const {
    int index = hash(key);
    Node* current = table_[index];

    while (current != nullptr) {
        if (strcmp(current->key, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
