//
// Created by jdh99 on 19.04.2025.
//

#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <memory>
#include "StackArray.hpp"
class BSTree {
public:
    BSTree(): root_(nullptr) {
    }
    ~BSTree() = default;
    BSTree(BSTree &&other) noexcept;
    BSTree &operator=(BSTree &&other) noexcept;
    BSTree &operator=(const BSTree &other) = delete;
    BSTree(const BSTree &other) = delete;

    void insert(int key);
    void output(std::ostream &os = std::cout) const {
        output(os, root_);
    }

    std::size_t countNodes() const {
        return countNodes(root_);
    }

    void eraseAllList();

private:
    struct Node {
        int key_;
        std::shared_ptr<Node> left_;
        std::shared_ptr<Node> right_;

        explicit Node (int key): key_(key), left_(nullptr), right_(nullptr) {}
    };

    std::shared_ptr<Node> root_;
    void output(std::ostream &os, const std::shared_ptr<Node> &node) const;

    static std::size_t countNodes(const std::shared_ptr<Node> &node);
};





#endif //BINARYSEARCHTREE_HPP
