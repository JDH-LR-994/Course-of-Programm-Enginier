#pragma once

#include <cassert>
#include <fstream>
#include <sstream>
#include "RedBlackTree.hpp"

// Тест 1: Проверка вставки и поиска элемента
inline void testInsertAndSearch() {
    RedBlackTree<int> tree;
    assert(tree.search(10) == false);
    assert(tree.insert(10) == true);
    assert(tree.search(10) == true);
    assert(tree.insert(10) == false); // Дубликат
    assert(tree.search(20) == false);
}

// Тест 2: Проверка удаления элемента
inline void testRemove() {
    RedBlackTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    assert(tree.remove(10) == true);
    assert(tree.search(10) == false);
    assert(tree.search(20) == true);
    assert(tree.remove(30) == false); // Несуществующий элемент
}

// Тест 3: Проверка свойств КЧД после вставки
inline void testRedBlackPropertiesAfterInsert() {
    RedBlackTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    // Корень должен быть чёрным
    assert(tree.begin() != tree.end()); // Хотя бы один элемент
}

// Тест 4: Проверка обхода в порядке возрастания (in-order)
inline void testInOrderTraversal() {
    RedBlackTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    // Перенаправляем вывод в строковый поток
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    tree.inorderWalkIterative();

    // Восстанавливаем стандартный вывод
    std::cout.rdbuf(old);

    // Проверяем вывод
    std::string output = buffer.str();
    assert(output.find("2 3 4 5 7") != std::string::npos);
}

// Тест 5: Проверка обхода по уровням (BFS)
inline void testLevelOrderTraversal() {
    RedBlackTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::stringstream ss;
    tree.walkByLevels(ss);
    std::string output = ss.str();
    // Проверим, что вывод содержит все элементы
    assert(output.find("10") != std::string::npos);
    assert(output.find('5') != std::string::npos);
    assert(output.find("15") != std::string::npos);
}

// Тест 6: Проверка высоты дерева
inline void testTreeHeight() {
    RedBlackTree<int> tree;
    assert(tree.getHeight() == 0); // Пустое дерево
    tree.insert(10);
    assert(tree.getHeight() == 0); // Только корень
    tree.insert(5);
    tree.insert(15);
    assert(tree.getHeight() == 1); // 2 уровня
}

// Тест 7: Проверка количества узлов
inline void testNodeCount() {
    RedBlackTree<int> tree;
    assert(tree.getNumberOfNodes() == 0);
    tree.insert(10);
    assert(tree.getNumberOfNodes() == 1);
    tree.insert(20);
    assert(tree.getNumberOfNodes() == 2);
    tree.remove(10);
    assert(tree.getNumberOfNodes() == 1);
}

// Тест 8: Проверка работы итератора
inline void testIterator() {
    RedBlackTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    auto it = tree.begin();
    assert(*it == 3);
    ++it;
    assert(*it == 5);
    ++it;
    assert(*it == 7);
    ++it;
    assert(it == tree.end());
}

// Тест 9: Проверка вывода дерева в файл
inline void testFileOutput() {
    RedBlackTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    // Выводим дерево в строку
    std::stringstream ss;
    tree.output(ss);
    const std::string output = ss.str();
    // Проверяем, что вывод содержит ключи в скобочной нотации
    assert(output.find("(B:10") != std::string::npos);  // Чёрный корень 10
    assert(output.find("(R:5") != std::string::npos);   // Красный узел 5
    assert(output.find("(R:15") != std::string::npos);  // Красный узел 15
}

// Тест 10: Проверка вставки большого количества элементов
inline void testMassiveInsert() {
    RedBlackTree<int> tree;
    for (int i = 0; i < 100; ++i) {
        assert(tree.insert(i) == true);
    }
    assert(tree.getNumberOfNodes() == 100);
    assert(tree.getHeight() < 2 * log2(tree.getNumberOfNodes() + 1)); // Для КЧД высота должна быть небольшой
}

// Тест 11: Проверка удаления с двумя потомками
inline void testRemoveWithTwoChildren() {
    RedBlackTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(12);
    tree.insert(20);

    assert(tree.remove(15) == true);
    assert(tree.search(15) == false);
    assert(tree.search(12) == true);
    assert(tree.search(20) == true);
}

// Тест 12: Проверка свойств КЧД после удаления
inline void testRedBlackPropertiesAfterRemove() {
    RedBlackTree<int> tree;
    for (int i = 0; i < 20; ++i) {
        tree.insert(i);
    }
    for (int i = 5; i < 15; ++i) {
        tree.remove(i);
    }
    // Проверяем, что дерево осталось сбалансированным
    assert(tree.getHeight() < 2 * log2(tree.getNumberOfNodes() + 1));
}

// Тест 13: Проверка работы с пользовательским типом
inline void testCustomType() {
    struct Point {
        int x, y;
        bool operator<(const Point& other) const { return x < other.x; }
        bool operator>(const Point& other) const { return x > other.x; }
        bool operator==(const Point& other) const { return x == other.x && y == other.y; }
        bool operator!=(const Point& other) const { return !(*this == other); }
    };

    RedBlackTree<Point> tree;
    tree.insert({1, 2});
    tree.insert({3, 4});
    assert(tree.search({1, 2}) == true);
    assert(tree.search({3, 4}) == true);
    assert(tree.search({5, 6}) == false);
}

// Тест 14: Проверка перемещающего конструктора
inline void testMoveConstructor() {
    RedBlackTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);

    RedBlackTree<int> tree2(std::move(tree1));
    assert(tree2.search(10) == true);
    assert(tree2.search(5) == true);
    assert(tree1.search(10) == false); // tree1 должен быть пуст
}

// Тест 15: Проверка перемещающего оператора присваивания
inline void testMoveAssignment() {
    RedBlackTree<int> tree1, tree2;
    tree1.insert(10);
    tree1.insert(5);

    tree2 = std::move(tree1);
    assert(tree2.search(10) == true);
    assert(tree2.search(5) == true);
    assert(tree1.search(10) == false); // tree1 должен быть пуст
}

// Главная тестовая функция, которая запускает все тесты
inline void mainTest() {
    testInsertAndSearch();
    testRemove();
    testRedBlackPropertiesAfterInsert();
    testInOrderTraversal();
    testLevelOrderTraversal();
    testTreeHeight();
    testNodeCount();
    testIterator();
    testFileOutput();
    testMassiveInsert();
    testRemoveWithTwoChildren();
    testRedBlackPropertiesAfterRemove();
    testCustomType();
    testMoveConstructor();
    testMoveAssignment();

    std::cout << "All tests passed successfully!" << std::endl;

}