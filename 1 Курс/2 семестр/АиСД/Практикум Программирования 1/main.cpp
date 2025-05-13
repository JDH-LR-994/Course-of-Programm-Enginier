#include <cassert>
#include <string>
#include "HashTable.hpp"

void runTests() {
    std::cout << "=== Starting tests ===\n";

    {
        std::cout << "\nTest1: Creation and cleanup\n";
        HashTable ht(10);
        assert(ht.hash("test") >= 0 && ht.hash("test") < 10);
        ht.insert("test");
        ht.clear();
        ht.printAll();
        std::cout << "Test1 passed\n";
    }

    {
        std::cout << "\nTest2: Insert and collisions\n";
        HashTable ht(5);
        assert(ht.insert("apple"));
        assert(ht.insert("banana"));
        assert(ht.insert("orange"));
        assert(!ht.insert("apple"));


        assert(ht.insert("elppa"));

        std::cout << "=== Test 2: Chains ===\n";
        ht.printAll();
        std::cout << "Test2 passed\n";
    }

    {
        std::cout << "\nTest3: Removal\n";
        HashTable ht(10);
        ht.insert("one");
        ht.insert("two");
        ht.insert("three");

        assert(ht.remove("two"));
        assert(!ht.remove("two"));
        assert(!ht.remove("nonexistent"));

        std::cout << "=== Test 3: After removal ===\n";
        ht.printAll();
        std::cout << "Test3 passed\n";
    }

    {
        std::cout << "\nTest4: Print chains\n";
        HashTable ht(5);
        const char* test_data[] = {"a", "b", "c", "d", "e", "f", nullptr};
        for (int i = 0; test_data[i] != nullptr; ++i) {
            ht.insert(test_data[i]);
        }

        std::cout << "=== Test 4: Print chains ===\n";
        for (int i = 0; i < 5; ++i) {
            ht.printChain(i);
        }
        std::cout << "Test4 passed\n";
    }

    {
        std::cout << "\nTest5: Empty table\n";
        HashTable ht(10);
        assert(!ht.remove("anything"));
        ht.printAll();
        ht.printChain(0);
        std::cout << "Test5 passed\n";
    }

    {
        std::cout << "\nTest6: Invalid input\n";
        HashTable ht(10);

        assert(ht.insert(""));

        assert(!ht.insert(nullptr));

        ht.printChain(-1);
        ht.printChain(10);
        std::cout << "Test6 passed\n";
    }

    {
        std::cout << "\nTest7: Large dataset\n";
        HashTable ht(100);
        for (int i = 0; i < 1000; ++i) {
            std::string s = "key_" + std::to_string(i);
            assert(ht.insert(s.c_str()));
        }

        assert(!ht.insert("key_500"));
        assert(ht.remove("key_500"));
        assert(ht.insert("key_500"));

        std::cout << "=== Test 7: Large dataset ===\n";
        std::cout << "Hash of 'key_500': " << ht.hash("key_500") << "\n";
        ht.printChain(ht.hash("key_500"));
        std::cout << "Test7 passed\n";
    }

    std::cout << "\n=== All tests passed successfully! ===\n";
}

int main() {
    runTests();
    return 0;
}