#include <cassert>
#include "MySharedPtr.hpp"
#include "iostream"
// Тест на создание указателя с объектом
void testConstructorWithObject() {
    MySharedPtr<int> ptr(new int(42));
    assert(*ptr == 42);  // Значение должно быть 42
}

// Тест на копирование указателя
void testCopyConstructor() {
    MySharedPtr<int> ptr1(new int(42));
    const MySharedPtr<int>& ptr2(ptr1);  // Копируем указатель
    assert(*ptr2 == 42);  // Значение должно быть 42
}

// Тест на оператор присваивания
void testAssignmentOperator() {
    const MySharedPtr<int> ptr1(new int(42));
    MySharedPtr<int> ptr2(new int(100));  // Создаём второй указатель
    ptr2 = ptr1;  // Присваиваем указатель
    assert(*ptr2 == 42);  // Значение должно быть 42
}

// Тест на освобождение ресурсов при уничтожении
void testDestructor() {
    MySharedPtr<int> ptr1(new int(42));
    {
        MySharedPtr<int> ptr2(ptr1);  // Копируем указатель
    }  // ptr2 уничтожается здесь
    // Проверяем, что ptr1 всё ещё работает
    assert(*ptr1 == 42);
}

// Тест на оператор разыменования
void testDereferenceOperator() {
    MySharedPtr<int> ptr(new int(42));
    assert(*ptr == 42);  // Значение должно быть 42
}

// Тест на оператор доступа к членам
void testArrowOperator() {
    struct TestStruct {
        int value;
    };
    MySharedPtr<TestStruct> ptr(new TestStruct{42});
    assert(ptr->value == 42);  // Значение должно быть 42
}

// Тест на присваивание самому себе
void testSelfAssignment() {
    MySharedPtr<int> ptr(new int(42));
    ptr = ptr;  // Присваиваем указатель самому себе
    assert(*ptr == 42);  // Значение должно быть 42
}

int main() {
    testConstructorWithObject();
    testCopyConstructor();
    testAssignmentOperator();
    testDestructor();
    testDereferenceOperator();
    testArrowOperator();
    testSelfAssignment();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}