#include <iostream>

// Класс, который хранит в себе ключи (какие-то данные) в порядке возрастания
template <typename key_t>
class DictionaryList
{
private:
    // Дополнительный класс узла, который будет содержать ключ и ссылки на следующий и предыдущий узел
    struct Node;
    Node *head_, *tail_;

public:
    DictionaryList() : head_(nullptr), tail_(nullptr) {}

    void insertItem(key_t key);
    Node *searchItem(key_t key);
    void deleteItem(key_t key);
    void clear();

    Node *getHead() { return head_; }
    Node *getTail() { return tail_; }

    ~DictionaryList();
    DictionaryList(DictionaryList &&other) noexcept;
    DictionaryList<key_t> &operator=(DictionaryList<key_t> &&other) noexcept;

    template <typename key_type>
    friend DictionaryList<key_type> getIntersection(DictionaryList<key_type> &first, DictionaryList<key_type> &second);
};

template <typename key_t>
struct DictionaryList<key_t>::Node
{
    key_t key_;
    Node *next_;
    Node *previous_;

    explicit Node(key_t k) noexcept: key_(k), next_(nullptr), previous_(nullptr)  {}
};

template <typename key_t>
typename DictionaryList<key_t>::Node* DictionaryList<key_t>::searchItem(key_t key)
{
    /*
    Поиск элемента по ключу
    Логика:
    Пробегаемся по всем элементам, пока не найдем или не закончим поиск
    */
    Node *current = head_;
    while (current != nullptr)
    {
        if (key == current->key_)
        {
            return current;
        }
        current = current->next_;
    }
    return nullptr;
}

template <typename key_t>
void DictionaryList<key_t>::deleteItem(key_t key)
{
    /*
    Удаление элемента по ключу
    Логика:
    1. Находим элемент по ключу
    2. Если элемент найден, обновляем ссылки соседних элементов
    3. Удаляем элемент
    */
    Node *current = head_;
    while (current != nullptr)
    {
        if (current->key_ == key)
        {
            if (current->previous_)
            {
                current->previous_->next_ = current->next_;
            }
            else
            {
                head_ = current->next_;
            }
            if (current->next_)
            {
                current->next_->previous_ = current->previous_;
            }
            else
            {
                tail_ = current->previous_;
            }
            delete current;
            return;
        }
        current = current->next_;
    }
}

template <typename key_t>
void DictionaryList<key_t>::clear()
{
    /*
    Очистка списка
    Логика:
    1. Сохраняем первый элемент
    2. Голову передвигаем на следующий элемент
    3. Удаляем первый элемент
    4. Зациклить первые три шага, пока список не станет пустым
    5. Обновляем указатель на хвост
    */
    while (head_ != nullptr)
    {
        Node *temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    tail_ = nullptr;
}

template <typename key_t>
void DictionaryList<key_t>::insertItem(key_t key)
{
    /*
    Добавление элемента в словарь по ключу
    Логика работы: если словарь пуст -> наш элемент теперь и хвост и голова
        Если словарь не пуст -> начинаем перебирать элементы начиная с головы: {
            Если ключи совпали -> удаляем *newNode (он уже есть) и уходим
            Если ключ меньше, чем ключ элемента, который мы проверяем -> наш элемент должен встать между проверяемым элементом и предыдущем для него
            Если мы смотрим уже последний элемент -> наш элемент должен стать последним
        }
    */
    Node *newNode = new Node(key);
    if (head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        Node *current = head_;
        while (current != nullptr)
        {
            if (key == current->key_)
            {
                delete newNode;
                return;
            }
            if (key < current->key_)
            {
                newNode->next_ = current;
                newNode->previous_ = current->previous_;
                if (current->previous_)
                {
                    current->previous_->next_ = newNode;
                }
                else
                {
                    head_ = newNode;
                }
                current->previous_ = newNode;
                break;
            }
            if (current->next_ == nullptr)
            {
                tail_ = newNode;
                newNode->previous_ = current;
                current->next_ = newNode;
                break;
            }
            current = current->next_;
        }
    }
}

template <typename key_t>
DictionaryList<key_t>::~DictionaryList()
{
    clear();
}

template <typename key_t>
DictionaryList<key_t>::DictionaryList(DictionaryList &&other) noexcept : head_(other.head_), tail_(other.tail_)
{
    /*
    Конструктор перемещения
    Логика:
    Заберём указатели на голову и хвост
    Обнуляем всё у другого объекта (теперь он есть, но пуст)
    */
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

template <typename key_t>
DictionaryList<key_t> &DictionaryList<key_t>::operator=(DictionaryList<key_t> &&other) noexcept
{
    /*
    Оператор перемещающего присваивания
    Логика:
    Если присваиваем не себе -> чистим своё, забираем все данные у другого, а его делаем пустым
    */
    if (this != &other)
    {
        clear();

        head_ = other.head_;
        tail_ = other.tail_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
    }
    return *this;
}

template <typename key_t>
DictionaryList<key_t> getIntersection(DictionaryList<key_t> &first, DictionaryList<key_t> &second)
{
    DictionaryList<key_t> result;

    auto *current = first.getHead();
    while (current != nullptr)
    {
        if (second.searchItem(current->key_))
        {
            result.insertItem(current->key_);
        }
        current = current->next_;
    }
    return result;
}