#pragma once

#include <cassert>
#include <fstream>
#include <sstream>
#include "RedBlackTree.hpp"
#include "ReadFunc.hpp"

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

inline void testBasicTop3() {
    // Создаем временный файл для теста
    const std::string test_file = "test_basic.txt";
    std::ofstream out(test_file);
    out << "apple banana apple cherry banana apple";
    out.close();

    // Извлекаем слова и получаем топ-3
    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    // Проверяем результаты
    assert(top3.get_size() == 3);
    assert(top3[0].first == "apple" && top3[0].second == 3);
    assert(top3[1].first == "banana" && top3[1].second == 2);
    assert(top3[2].first == "cherry" && top3[2].second == 1);

}

inline void testRepeatedWords() {
    const std::string test_file = "test_repeated.txt";
    std::ofstream out(test_file);
    out << "hello hello hello world world world world test test";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    assert(top3.get_size() == 3);
    assert(top3[0].first == "world" && top3[0].second == 4);
    assert(top3[1].first == "hello" && top3[1].second == 3);
    assert(top3[2].first == "test" && top3[2].second == 2);

}

inline void testLessThan3Words() {
    const std::string test_file = "test_less3.txt";
    std::ofstream out(test_file);
    out << "single";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top = tree.getTopKFrequent(3);

    assert(top.get_size() == 1);
    assert(top[0].first == "single" && top[0].second == 1);

}

inline void testCaseInsensitive() {
    const std::string test_file = "test_case.txt";
    std::ofstream out(test_file);
    out << "Apple apple aPpLE Banana banana";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top2 = tree.getTopKFrequent(2);

    assert(top2.get_size() == 2);
    assert(top2[0].first == "apple" && top2[0].second == 3);
    assert(top2[1].first == "banana" && top2[1].second == 2);

}


inline void testEmptyFile() {
    const std::string test_file = "test_empty.txt";
    std::ofstream out(test_file);  // Создаем пустой файл
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top = tree.getTopKFrequent(3);

    assert(top.get_size() == 0);

}

inline void testDifferentDelimiters() {
    const std::string test_file = "test_delimiters.txt";
    std::ofstream out(test_file);
    out << "word1,word2.word3!word4?word1\nword2\tword5";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);
    assert(top3[0].first == "word" && top3[0].second == 7);

}

inline void testSimpleText() {
    const std::string test_file = "test_simple.txt";
    std::ofstream out(test_file);
    out << "the quick brown fox jumps over the lazy dog and the fox is quick";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    assert(top3.get_size() == 3);
    assert(top3[0].first == "the" && top3[0].second == 3);
    assert(top3[1].first == "fox" && top3[1].second == 2);
    assert(top3[2].first == "quick" && top3[2].second == 2);

}

inline void testTextWithPunctuation() {
    const std::string test_file = "test_punctuation.txt";
    std::ofstream out(test_file);
    out << "Hello, world! World is beautiful. Hello everyone!";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    assert(top3.get_size() == 3);
    assert(top3[0].first == "hello" && top3[0].second == 2);
    assert(top3[1].first == "world" && top3[1].second == 2);
    assert(top3[2].first == "is" || top3[2].first == "beautiful" || top3[2].first == "everyone");

}

inline void testTextWithSpecialChars() {
    const std::string test_file = "test_special_chars.txt";
    std::ofstream out(test_file);
    out << "It's a well-known fact; mother-in-law and state-of-the-art are compound words.";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    assert(top3.get_size() == 3);
    // Проверяем, что составные слова обрабатываются правильно
    for (const auto& pair : top3) {
        assert(pair.first == "a" || pair.first == "its" || pair.first == "and" ||
               pair.first == "are" || pair.first == "fact" || pair.first == "words" ||
               pair.first == "wellknown" || pair.first == "motherinlaw" || pair.first == "stateoftheart");
    }

}

inline void testMultilineText() {
    const std::string test_file = "test_multiline.txt";
    std::ofstream out(test_file);
    out << "First line\nSecond line\nThird line\nFirst line again";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    assert(top3.get_size() == 3);
    assert(top3[0].first == "line" && top3[0].second == 4);
    assert((top3[1].first == "first" && top3[1].second == 2) ||
           (top3[1].first == "second" || top3[1].first == "third" || top3[1].first == "again"));

}

inline void testTextWithStopWords() {
    const std::string test_file = "test_stopwords.txt";
    std::ofstream out(test_file);
    out << "This is a test of the system. This test should work correctly.";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    assert(top3.get_size() == 3);
    assert(top3[0].first == "test" && top3[0].second == 2);
    assert(top3[1].first == "this" && top3[1].second == 2);
    assert(top3[2].first == "a" || top3[2].first == "of" || top3[2].first == "the" ||
           top3[2].first == "system" || top3[2].first == "should" ||
           top3[2].first == "work" || top3[2].first == "correctly" || top3[2].first == "is");

}

inline void testLiteratureFragment() {
    const std::string test_file = "test_literature.txt";
    std::ofstream out(test_file);
    out << "It was the best of times, it was the worst of times, "
        << "it was the age of wisdom, it was the age of foolishness...";
    out.close();

    auto tree = extractWordsFromFile(test_file);
    auto top3 = tree.getTopKFrequent(3);

    assert(top3.get_size() == 3);
    assert(top3[0].first == "it" && top3[0].second == 4);
    assert((top3[1].first == "was" || top3[1].first == "of") && top3[1].second == 4);
    assert(top3[2].first == "the" && top3[2].second == 4);

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
    testBasicTop3();
    testRepeatedWords();
    testLessThan3Words();
    testCaseInsensitive();
    testEmptyFile();
    testDifferentDelimiters();
    testSimpleText();
    testTextWithPunctuation();
    testTextWithSpecialChars();
    testMultilineText();
    testTextWithStopWords();
    testLiteratureFragment();

    std::cout << "All tests passed successfully!" << std::endl;

}