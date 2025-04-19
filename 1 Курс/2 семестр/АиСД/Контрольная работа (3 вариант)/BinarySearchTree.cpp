//
// Created by jdh99 on 19.04.2025.
//
#include "BinarySearchTree.hpp"

inline BSTree::BSTree(BSTree &&other) noexcept: root_(std::move(other.root_)) {
}

inline BSTree &BSTree::operator=(BSTree &&other) noexcept {
    if (this == &other)
        return *this;
    root_ = std::move(other.root_);
    return *this;
}

void BSTree::insert(int key) {
    if (root_ == nullptr) {
        root_ = std::make_shared<Node>(key);
        return;
    }

    std::shared_ptr<Node> currentNode = root_;
    std::shared_ptr<Node> previousNode = nullptr;

    while (currentNode != nullptr) {
        previousNode = currentNode;
        if (currentNode->key_ > key) {
            currentNode = currentNode->left_;
        } else if (currentNode->key_ < key) {
            currentNode = currentNode->right_;
        } else {
            return;
        }
    }

    auto newNode = std::make_shared<Node>(key);
    if (key < previousNode->key_) {
        previousNode->left_ = newNode;
    } else {
        previousNode->right_ = newNode;
    }
}

void BSTree::eraseAllList() {
    if (root_ == nullptr) return;

    StackArray<std::shared_ptr<Node>> nodeStack(countNodes(root_) + 1);
    StackArray<std::shared_ptr<Node>> parentStack(countNodes(root_) + 1);
    StackArray<bool> isLeftStack(countNodes(root_) + 1);

    nodeStack.push_back(root_);
    parentStack.push_back(nullptr);
    isLeftStack.push_back(false);

    while (nodeStack.size() > 0) {
        auto current = nodeStack.pop();
        auto parent = parentStack.pop();
        bool isLeft = isLeftStack.pop();

        if (current->left_ == nullptr && current->right_ == nullptr && parent != nullptr) {
            if (isLeft) {
                parent->left_ = nullptr;
            } else {
                parent->right_ = nullptr;
            }
            continue;
        }

        if (current->right_ != nullptr) {
            nodeStack.push_back(current->right_);
            parentStack.push_back(current);
            isLeftStack.push_back(false);
        }
        if (current->left_ != nullptr) {
            nodeStack.push_back(current->left_);
            parentStack.push_back(current);
            isLeftStack.push_back(true);
        }
    }

    if (root_->left_ == nullptr && root_->right_ == nullptr) {
        root_ = nullptr;
    }
}

void BSTree::output(std::ostream &os, const std::shared_ptr<Node> &node) const {
    if (node == nullptr) return;

    os << "(" << node->key_;
    if (node->left_ !=  nullptr || node->right_ != nullptr ) {
        output(os, node->left_);
        output(os, node->right_);
    }

    os << ")";
}

std::size_t BSTree::countNodes(const std::shared_ptr<Node> &node) {
    if (node == nullptr || (node->left_ == nullptr && node->right_ == nullptr)) return 0;
    std::size_t count = 1;
    if (node->left_ != nullptr) count += countNodes(node->left_);
    if (node->right_ != nullptr) count += countNodes(node->right_);
    return count;
}
