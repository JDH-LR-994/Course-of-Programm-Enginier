//
// Created by jdh99 on 13.05.2025.
//
#pragma once

#include "BinarySearchTree.hpp"
#include <cassert>
#include <sstream>

inline void testEmptyTree() {
    BSTree tree;
    std::ostringstream oss;
    tree.output(oss);
    assert(oss.str().empty());
    assert(tree.countNodes() == 0);

    tree.eraseAllList();
    oss.str("");
    tree.output(oss);
    assert(oss.str().empty());
}

inline void testSingleNodeTree() {
    BSTree tree;
    tree.insert(10);

    std::ostringstream oss;
    tree.output(oss);
    assert(oss.str() == "(10)");
    assert(tree.countNodes() == 0);

    tree.eraseAllList();
    oss.str("");
    tree.output(oss);
    assert(oss.str().empty());
}

inline void testTreeWithLeaves() {
    BSTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    std::ostringstream oss;
    tree.output(oss);
    assert(oss.str() == "(10(5)(15))");
    assert(tree.countNodes() == 1);

    tree.eraseAllList();
    oss.str("");
    tree.output(oss);
    assert(oss.str() == "(10)");
}

inline void testComplexTree() {
    BSTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);
    tree.insert(1);
    tree.insert(4);
    tree.insert(17);
    tree.insert(25);

    std::ostringstream oss;
    tree.output(oss);

    assert(tree.countNodes() == 5);

    tree.eraseAllList();
    oss.str("");
    tree.output(oss);
    assert(oss.str() == "(10(5(3))(15(20)))");
}

inline void testMoveSemantics() {
    BSTree tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);

    BSTree tree2(std::move(tree1));
    std::ostringstream oss;
    tree2.output(oss);
    assert(oss.str() == "(10(5)(15))");

    BSTree tree3;
    tree3 = std::move(tree2);
    oss.str("");
    tree3.output(oss);
    assert(oss.str() == "(10(5)(15))");

    oss.str("");
    tree1.output(oss);
    assert(oss.str().empty());

    oss.str("");
    tree2.output(oss);
    assert(oss.str().empty());
}

inline void testInsertDuplicate() {
    BSTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(10); // Дубликат

    std::ostringstream oss;
    tree.output(oss);
    assert(oss.str() == "(10(5))");
    assert(tree.countNodes() == 1);
}

inline void testMultipleEraseOperations() {
    BSTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    tree.eraseAllList();
    std::ostringstream oss;
    tree.output(oss);
    assert(oss.str() == "(10(5))");

    tree.eraseAllList();
    oss.str("");
    tree.output(oss);
    assert(oss.str() == "(10)");

    tree.eraseAllList();
    oss.str("");
    tree.output(oss);
    assert(oss.str().empty());
}

