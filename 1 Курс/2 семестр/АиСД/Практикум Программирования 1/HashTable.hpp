//
// Created by jdh99 on 13.05.2025.
//

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>

class HashTable {
    struct Node {
        char* key;
        Node* next;
        explicit Node(const char* k);
        ~Node();
    };

    int size_;
    Node** table_;

public:
    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;

    explicit HashTable(int size = 256);

    ~HashTable();

    void clear();

    int hash(const char* key) const;

    bool insert(const char* key);

    bool remove(const char* key);

    void printChain(int hashValue) const;

    void printAll() const;

private:
    bool contains(const char* key) const;
};


#endif //HASHTABLE_HPP
