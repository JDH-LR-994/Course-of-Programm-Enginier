/**
* @author JDH-LR-994
* @file RedBlackTree.hpp
* @brief Реализация красно-чёрного дерева
 * Красно-чёрное дерево - это бинарное дерево поиска, где у каждого
 * узла есть атрибут цвета, при этом:
 * 1. Узел должен быть либо красным, либо чёрным
 * 2. Корень - как правило чёрный
 * 3. Все фиктивные листья (NIL - узлы) - чёрные
 * 4. Оба потомка каждого красного узла - чёрные
 * 5. Любой простой путь от узла-предка до листового узла потомка
 * содержит одинаковое число чёрных узлов
 *
 * ВАЖНО! Как и любое другое бинарное дерево поиска, КЧД может работать только
 * с типами, которые можно сравнивать (указано вторым шаблонным параметром)
 *
 * @note Все операции (вставка, поиск) работают за O(log n) в худшем случае.
 */

#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include "StackArray.hpp"
#include "QueueList.hpp"
#include "Vector.hpp"
#include "Pair.hpp"

template<typename...>
using void_t = void;
/**
 * @brief SFINAE-проверка наличия операторов сравнения у типа T.
 * @details Проверяет, определён ли для типа T операторы <, >, ==, !=.
 * Если операторы отсутствуют, компиляция завершится с ошибкой.
 */
template<typename T, typename = void>
struct is_comparable : std::false_type {
};

template<typename T>
struct is_comparable<T, void_t<
            decltype(std::declval<T>() < std::declval<T>()),
            decltype(std::declval<T>() > std::declval<T>()),
            decltype(std::declval<T>() == std::declval<T>()),
            decltype(std::declval<T>() != std::declval<T>())
        > > : std::true_type {
};


/**
 * @brief Класс красно-чёрного дерева.
 * @tparam T Тип данных, хранящихся в узлах дерева.
 * @tparam T0 Вспомогательный параметр для SFINAE (не используется напрямую).
 * @details Если операторы сравнения отсутствуют, тип T не сможет быть использован в RedBlackTree.
*/
template<typename T, typename T0 = std::enable_if_t<is_comparable<T>::value> >
class RedBlackTree {
    /**
     * @brief Перечисление цветов узлов красно-чёрного дерева.
     * @details В красно-чёрном дереве каждый узел должен быть либо красным, либо чёрным.
     *          Это фундаментальное свойство, обеспечивающее балансировку дерева.
     *          - RED: Красный узел
     *          - BLACK: Чёрный узел
     */
    enum class Color { RED, BLACK };

    struct Node;
    /**
     * @brief Умные указатели для работы с узлами дерева.
     * @details Используются shared_ptr для владеющих указателей и weak_ptr для
     *          ссылок на родителя, чтобы избежать циклических зависимостей.
     */
    using NodePtr = std::shared_ptr<Node>; ///< Умный указатель на узел.
    using WeakNodePtr = std::weak_ptr<Node>; ///< Слабый указатель на узел (для избегания циклов)

    /**
     * @brief Структура узла дерева.
     */
    struct Node {
        T key_; ///< Ключ узла.
        std::size_t frequency_ = 1;
        Color color_; ///< Цвет узла.
        NodePtr left_; ///< Левый потомок.
        NodePtr right_; ///< Правый потомок.
        WeakNodePtr parent_; ///< Ссылка на родителя (слабый указатель).
        /**
         * @brief Конструктор узла.
         * @param k Ключ узла.
         * @param c Цвет узла.
         * @param p Ссылка на родителя (по умолчанию пустая).
         */
        Node(T k, Color c, WeakNodePtr p = WeakNodePtr{}) : key_(k),
                                                            color_(c),
                                                            left_(NIL),
                                                            right_(NIL),
                                                            parent_(p) {
        }
    };

public:
    /**
     * @brief Конструктор по умолчанию. Инициализирует дерево с пустым корнем (NIL).
     */
    RedBlackTree(): root(NIL) {
    };

    RedBlackTree(const RedBlackTree &) = delete; ///< Запрещённый конструктор копирования.

    RedBlackTree &operator=(const RedBlackTree &) = delete; ///< Запрещённое копирующее присваивание.

    RedBlackTree(RedBlackTree &&other) noexcept ///< Разрешенный конструктор перемещения.
    ;

    RedBlackTree &operator=(RedBlackTree &&other) noexcept ///< Разрешенное перемещающее присваивание.
    ;

    std::size_t getFrequency(T& arg) const;

    ~RedBlackTree() = default; ///< Деструктор по умолчанию.

    /**
     * @brief Итератор для обхода красно-чёрного дерева в порядке in-order (симметричный порядок).
     *
     * @details Итератор реализует forward iterator, позволяющий последовательно обходить узлы дерева
     * от наименьшего к наибольшему ключу. Обход выполняется нерекурсивно с использованием стека,
     * что гарантирует корректную работу даже для очень больших деревьев.
     *
     * Особенности реализации:
     * - Использует StackArray<NodePtr> для хранения узлов при обходе
     * - Автоматически вычисляет необходимый размер стека на основе количества узлов
     * - Поддерживает стандартные операции итератора: *, ->, ++ (префиксный и постфиксный)
     * - Корректно обрабатывает end-итератор (пустое дерево или завершение обхода)
     *
     * Гарантии:
     * - Время доступа к следующему элементу: O(1) амортизированное
     * - Потребление памяти: O(h), где h - высота дерева
     * - Инвалидация итератора при модификации дерева
     *
     * Пример использования:
     * @code
     * RedBlackTree<int> tree;
     * // ... заполнение дерева ...
     *
     * // Вариант 1: Range-based for loop
     * for (const auto& value : tree) {
     *     std::cout << value << " ";
     * }
     *
     * // Вариант 2: Явное использование итераторов
     * for (auto it = tree.begin(); it != tree.end(); ++it) {
     *     std::cout << *it << " ";
     * }
     * @endcode
     *
     * @tparam T Тип данных, хранящихся в узлах дерева
     * @tparam T0 SFINAE-параметр (не используется напрямую)
     */
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        explicit Iterator(NodePtr root = NIL, size_t max_stack_size = 100);

        reference operator*() const;

        pointer operator->() const;

        /**
         * @brief Префиксный оператор инкремента для итератора.
         * @return Ссылка на текущий итератор после инкремента.
         * @throws std::out_of_range если итератор уже end().
         * @details Алгоритм работы:
         * 1. Извлекаем текущий узел из стека
         * 2. Если у узла есть правый потомок, заполняем стек левыми потомками правого поддерева
         * 3. Возвращаем обновлённый итератор
         *
         * @note Сложность: O(1) амортизированная, так как каждый узел помещается в стек
         *       и извлекается из него ровно один раз за весь обход.
         */
        Iterator &operator++();

        std::size_t getFrequency() const;

        /**
         * @brief Постфиксный оператор инкремента для итератора.
         * @return Копия итератора до инкремента.
         * @details Отличается от префиксной версии тем, что возвращает
         *          предыдущее состояние итератора до увеличения.
         *
         * @note Реализован через префиксный оператор для избежания дублирования кода.
         */
        Iterator operator++(int);

        bool operator==(const Iterator &other) const;

        bool operator!=(const Iterator &other) const;

    private:
        StackArray<NodePtr> stack{100}; // Фиксированный размер стека (можно увеличить при необходимости)
        /**
         * @brief Заполняет стек левыми потомками начиная с заданного узла.
         * @param node Узел, с которого начинается заполнение стека.
         * @details Рекурсивно добавляет в стек все левые потомки узла,
         *          что позволяет в дальнейшем обходить их в порядке возрастания.
         *
         * @note Используется при инициализации итератора и переходе к правому поддереву.
         */
        void fillStack(NodePtr node);
    };

    Iterator begin() const {
        size_t max_depth = countNodes > 0 ? 2 * static_cast<size_t>(log2(countNodes + 1)) + 5 : 10;
        return Iterator(root, max_depth);
    }

    Iterator end() const {
        return Iterator();
    }


    Vector<Pair<T, int>> getTopKFrequent(std::size_t k) const {
        Vector<Pair<T, int>> elements;

        for (auto it = begin(); it != end(); it++) {
            elements.push_back(Pair<T, int>(*it, it.getFrequency()));
        }
        quickSort(elements);

        if (k > elements.get_size()) k = elements.get_size();

        Vector<Pair<T, int>> result;
        for (size_t i = 0; i < k; ++i) {
            result.push_back(elements[i]);
        }
        return result;
    }

    /**
     * @brief Поиск ключа в дереве.
     * @param k Ключ для поиска.
     * @return True, если ключ найден, иначе false.
     * @example
     * RedBlackTree<int> tree;
     * tree.insert(10);
     * bool found = tree.search(10); // Вернёт true
     * bool notFound = tree.search(20); // Вернёт false
     */
    bool search(const T &k) const;

    /**
     * @brief Вставка ключа в дерево.
     * @param key Ключ для вставки.
     * @return True, если вставка успешна, false, если ключ уже существует.
     * @example
     * RedBlackTree<int> tree;
     * bool inserted = tree.insert(10); // Вернёт true
     * bool duplicate = tree.insert(10); // Вернёт false (ключ уже есть)
     */
    bool insert(const T &key);

    /**
     * @brief Удаляет узел с заданным ключом из дерева и восстанавливает свойства красно-чёрного дерева.
     *
     * @param key Ключ узла, который требуется удалить.
     * @return True, если узел был найден и удалён, false, если ключ отсутствует в дереве.
     *
     * @details Алгоритм удаления состоит из нескольких этапов:
     * 1. Поиск удаляемого узла с помощью searchNode.
     * 2. Определение узла для замены (successor) и его потомка (child):
     *    - Если у узла нет одного из потомков, он заменяется своим единственным потомком.
     *    - Если у узла есть оба потомка, он заменяется узлом с минимальным ключом из правого поддерева (successor).
     * 3. Фиксация свойств дерева после удаления, если был удалён чёрный узел (вызов fixDelete).
     *
     * @note После удаления:
     * - Если удалённый узел был красным, свойства дерева не нарушаются.
     * - Если удалённый узел был чёрным, требуется балансировка (fixDelete).
     *
     * @warning Удаление несуществующего ключа безопасно и вернёт false.
     *
     * @example
     * RedBlackTree<int> tree;
     * tree.insert(10);
     * tree.insert(20);
     * bool success = tree.remove(10); // Вернёт true
     * bool fail = tree.remove(30);    // Вернёт false (ключ отсутствует)
     *
     * @see fixDelete() для деталей балансировки после удаления.
     * @see searchNode() для реализации поиска узла.
     */
    bool remove(const T &key);

    /**
     * @brief Метод, который позволяет получить количество узлов в дереве
     * @return количество узлов в дереве
     */
    [[nodiscard]] int getNumberOfNodes() const {
        return countNodes;
    }


private:
    /**
 * @brief Фиктивный чёрный узел, представляющий листья дерева.
 * @details Инициализируется через createNIL() и является общим для всех экземпляров дерева.
 */
    static NodePtr NIL; ///< Фиктивный чёрный узел, представляющий листья дерева.
    NodePtr root = NIL; ///< Корень дерева.
    std::size_t countNodes = 0; ///< Количество узлов в дереве

    /**
     * @brief Получение "дядюшки" узла (брата родителя).
     * @details Дядя узла — это брат его родителя. Например:
     * - Если узел является левым потомком своего родителя, то дядя — правый потомок деда.
     * - Если узел является правым потомком, то дядя — левый потомок деда.
     * @param node Узел, для которого ищется дядя.
     * @return Указатель на дядю или NIL, если:
     *         - у узла нет родителя,
     *         - у родителя нет деда,
     *         - дядя является NIL.
     * @example
     * // Пример корректного дерева:
     * //              G (чёрный)
     * //            /   \
     * //     P (чёрный)   U (красный)  <-- U — дядя для X.
     * //    /
     * //  X (красный)
     * auto uncle = getUncle(X); // Вернёт U, так как U — брат родителя P.
     *
     * // Пример, когда дядя — NIL:
     * //            G (чёрный)
     * //          /      \
     * //     P (чёрный)   NIL          <-- Дядя для X — NIL.
     * //    /
     * //  X (красный)
     * auto uncle = getUncle(X); // Вернёт NIL.
     */
    NodePtr getUncle(const NodePtr &node) const;

    /**
     * @brief Выполняет правый поворот вокруг указанного узла.
     *
     * @param pivot Узел, являющийся центром поворота (ось поворота)
     *
     * @details Графическое представление операции:
     * @verbatim
     *       До поворота:           После поворота:
     *
     *         pivot                   child
     *        /     \                 /     \
     *     child      C     -->     A       pivot
     *     /   \                         /     \
     *    A     B                       B       C
     * @endverbatim
     *
     * @note Особенности операции:
     * 1. Узел `child` становится новым корнем поддерева
     * 2. Поддерево `B` становится правым потомком `pivot`
     * 3. Сохраняется порядок элементов: A < child < B < pivot < C
     *
     * @warning Ограничения:
     * - Запрещено вызывать для NIL-узлов
     * - Узел должен иметь левого потомка (child != NIL)
     *
     * @see rotateLeft() для симметричной операции
     */
    void rotateRight(NodePtr pivot);

    /**
     * @brief Выполняет левый поворот вокруг указанного узла.
     *
     * @param pivot Узел, вокруг которого выполняется поворот (ось поворота)
     *
     * @details Графическое представление операции:
     * @verbatim
     *       До поворота:           После поворота:
     *
     *         pivot                   child
     *        /     \                 /     \
     *       A     child     -->     pivot     C
     *            /     \         /     \
     *           B       C       A       B
     * @endverbatim
     *
     * @note Особенности операции:
     * 1. Узел `child` становится новым корнем поддерева
     * 2. Поддерево `B` становится левым потомком `pivot`
     * 3. Сохраняется порядок элементов: A < pivot < B < child < C
     *
     * @warning Ограничения:
     * - Запрещено вызывать для NIL-узлов
     * - Узел должен иметь правого потомка (child != NIL)
     *
     * @see rotateRight() для симметричной операции
     */
    void rotateLeft(NodePtr pivot);

    /**
     * @brief Балансировка дерева после вставки.
     * @param pivot Узел, с которого начинается балансировка (новый узел).
     * @details Восстанавливает свойства красно-чёрного дерева после вставки:
     * 1. Каждый узел красный или чёрный
     * 2. Корень чёрный
     * 3. Все листья (NIL) чёрные
     * 4. Оба потомка красного узла чёрные
     * 5. Пути от узла до листьев содержат одинаковое число чёрных узлов
     *
     * Алгоритм рассматривает три основных случая:
     * - Случай 1: Дядя узла красный -> перекрашивание
     * - Случай 2: Дядя чёрный, узел - правый потомок -> левый поворот
     * - Случай 3: Дядя чёрный, узел - левый потомок -> правый поворот
     *
     * @note Сложность: O(log n) в худшем случае, так как может потребоваться
     *       подняться от нового узла до корня.
     * @example
     * RedBlackTree<int> tree;
     * tree.insert(10); // Автоматически вызывает fixInsert при необходимости.
     */
    void fixInsert(NodePtr pivot);

    /**
     * @brief Поиск узла по ключу.
     * @param k Ключ для поиска.
     * @return Указатель на найденный узел или NIL, если узел не найден.
     * @note Используется внутри методов класса (например, для удаления).
     */
    NodePtr searchNode(const T &k) const;

    /**
     * @brief Заменяет одно поддерево другим в дереве.
     *
     * @param oldNode Поддерево, которое нужно заменить
     * @param newNode Поддерево, на которое нужно заменить
     *
     * @details Функция выполняет следующие действия:
     * 1. Обновляет ссылку у родителя oldNode на newNode
     * 2. Обновляет родителя у newNode
     *
     * @note Не изменяет связи newNode с его потомками
     * @warning Не проверяет, является ли oldNode корнем дерева
     */
    void replaceSubtree(NodePtr oldNode, NodePtr newNode);

    /**
     * @brief Находит узел с минимальным ключом в поддереве.
     *
     * @param subtreeRoot Корень поддерева для поиска
     * @return Узел с минимальным ключом в поддереве
     *
     * @note Если subtreeRoot == NIL, возвращает NIL
     * @complexity O(h), где h - высота поддерева
     */
    NodePtr minimum(NodePtr subtreeRoot);

    /**
     * @brief Восстанавливает свойства красно-чёрного дерева после удаления узла.
     *
     * @param pivot Узел, с которого начинается восстановление (обычно удалённый или заменённый узел).
     *
     * @details Этот метод вызывается после удаления узла и обрабатывает возможные нарушения свойств КЧД:
     * - Если удалённый узел был чёрным, это могло нарушить баланс чёрных высот.
     * - Метод рекурсивно поднимается от `pivot` к корню, исправляя нарушения.
     *
     * Алгоритм рассматривает 4 основных случая:
     *
     * 1. Брат красный:
     *    - Перекрашивает брата в чёрный, родителя — в красный.
     *    - Делает поворот вокруг родителя в сторону `pivot`.
     *    - Преобразует ситуацию в случаи 2, 3 или 4.
     *
     * 2. Брат чёрный, оба его потомка чёрные:
     *    - Перекрашивает брата в красный.
     *    - Переносит проблему на родителя (теперь он становится новым `pivot`).
     *
     * 3. Брат чёрный, ближний потомок красный, дальний — чёрный:
     *    - Перекрашивает ближний потомок в чёрный, брата — в красный.
     *    - Делает поворот вокруг брата в сторону, противоположную `pivot`.
     *    - Преобразует ситуацию в случай 4.
     *
     * 4. Брат чёрный, дальний потомок красный:
     *    - Перекрашивает брата в цвет родителя.
     *    - Перекрашивает родителя и дальний потомок в чёрный.
     *    - Делает поворот вокруг родителя в сторону `pivot`.
     *    - Завершает балансировку (проблема решена).
     *
     * @note После завершения цикла корень всегда перекрашивается в чёрный (свойство КЧД №2).
     *
     * @example
     * // После удаления узла:
     * fixDelete(replacedNode); // Восстанавливает свойства дерева.
     */
    void fixDelete(NodePtr pivot);

    /**
     * @brief Создаёт фиктивный лист (NIL) с чёрным цветом и ссылками на себя.
     * @details Этот метод вызывается только один раз при инициализации статического члена NIL.
     * @return Указатель shared_ptr на фиктивный лист.
     */
    static NodePtr createNIL();

    static void quickSort(Vector<Pair<std::string, int>>& vec);

    static void quickSortImpl(Vector<Pair<std::string, int>>& vec, int low, int high);

    static int partition(Vector<Pair<std::string, int>>& vec, int low, int high);
};

template<typename T, typename T0>
RedBlackTree<T, T0>::RedBlackTree(RedBlackTree &&other) noexcept: root(std::move(other.root)), countNodes(other.countNodes) {
    other.root = NIL;
    other.countNodes = 0;
}

template<typename T, typename T0>
RedBlackTree<T, T0> & RedBlackTree<T, T0>::operator=(RedBlackTree &&other) noexcept {
    if (this != &other) {
        root = std::move(other.root);
        countNodes = other.countNodes;
        other.root = NIL;
        other.countNodes = 0;
    }
    return *this;
}

template<typename T, typename T0>
std::size_t RedBlackTree<T, T0>::getFrequency(T &arg) const {
    auto node = searchNode(arg);
    if (node != NIL) {
        return node->frequency_;
    }
    return 0;
}

template<typename T, typename T0>
RedBlackTree<T, T0>::Iterator::Iterator(NodePtr root, size_t max_stack_size): stack(max_stack_size) {
    if (root != NIL) {
        fillStack(root);
    }
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator::reference RedBlackTree<T, T0>::Iterator::operator*() const {
    if (stack.isEmpty()) {
        throw std::out_of_range("Dereferencing end iterator");
    }
    return stack.top()->key_;
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator::pointer RedBlackTree<T, T0>::Iterator::operator->() const {
    if (stack.isEmpty()) {
        throw std::out_of_range("Dereferencing end iterator");
    }
    return &stack.top()->key_;
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator &RedBlackTree<T, T0>::Iterator::operator++() {
    if (stack.isEmpty()) {
        throw std::out_of_range("Incrementing end iterator");
    }
    NodePtr node = stack.pop();
    if (node->right_ != NIL) {
        fillStack(node->right_);
    }
    return *this;
}

template<typename T, typename T0>
std::size_t RedBlackTree<T, T0>::Iterator::getFrequency() const {
    return stack.top().get()->frequency_;
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator RedBlackTree<T, T0>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::Iterator::operator==(const Iterator &other) const {
    // Оба итератора равны, если их стеки пусты (end-итераторы)
    // Или если их верхние элементы совпадают (для промежуточных состояний)
    return (stack.isEmpty() && other.stack.isEmpty()) ||
           (!stack.isEmpty() && !other.stack.isEmpty() && stack.top() == other.stack.top());
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::Iterator::operator!=(const Iterator &other) const {
    return !(*this == other);
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::Iterator::fillStack(NodePtr node) {
    while (node != NIL) {
        stack.push(node);
        node = node->left_;
    }
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::search(const T &k) const {
    return searchNode(k) != NIL;
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::insert(const T &key) {

    NodePtr found = searchNode(key);
    if (found != NIL) {
        ++(found->frequency_);
        return false;
    }

    if (root == NIL) {
        root = std::make_shared<Node>(key, Color::BLACK);
        root->left_ = root->right_ = NIL;
        countNodes++;
        return true;
    }

    NodePtr currentNode = root;
    NodePtr parent = NIL;

    // Поиск места для вставки
    while (currentNode != NIL) {
        parent = currentNode;
        if (key < currentNode->key_) {
            currentNode = currentNode->left_;
        } else if (key > currentNode->key_) {
            currentNode = currentNode->right_;
        } else {
            return false; // Ключ уже существует
        }
    }

    // Создание нового узла
    auto newNode = std::make_shared<Node>(key, Color::RED, parent);
    if (key < parent->key_) {
        parent->left_ = newNode;
    } else {
        parent->right_ = newNode;
    }

    // Балансировка
    fixInsert(newNode);
    countNodes++;
    return true;
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::remove(const T &key) {
    NodePtr node = searchNode(key);
    if (node == NIL) return false; // Узел не найден

    NodePtr successor = NIL;
    NodePtr child = NIL;
    Color originalColor = node->color_;

    // Определяем узел для удаления и его потомка
    if (node->left_ == NIL) {
        child = node->right_;
        replaceSubtree(node, child);
    } else if (node->right_ == NIL) {
        child = node->left_;
        replaceSubtree(node, child);
    } else {
        // У узла есть оба потомка
        successor = minimum(node->right_);
        originalColor = successor->color_;
        child = successor->right_;

        if (successor->parent_.lock() != node) {
            replaceSubtree(successor, child);
            successor->right_ = node->right_;
            successor->right_->parent_ = successor;
        }
        replaceSubtree(node, successor);
        successor->left_ = node->left_;
        successor->left_->parent_ = successor;
        successor->color_ = node->color_;
    }

    // Балансировка, если удалён чёрный узел
    if (originalColor == Color::BLACK) {
        fixDelete(child);
    }
    countNodes--;
    return true;
}


template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::getUncle(const NodePtr &node) const {
    auto parent = node->parent_.lock();
    if (!parent) return NIL; // Если родитель не существует, дядя тоже не существует.
    auto grandparent = parent->parent_.lock();
    if (!grandparent) return NIL;
    return (parent == grandparent->left_) ? grandparent->right_ : grandparent->left_;
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::rotateLeft(NodePtr pivot) {
    if (pivot == NIL || pivot->right_ == NIL) return; // Проверка на NIL
    auto child = pivot->right_;
    pivot->right_ = child->left_;

    if (pivot->right_)
        pivot->right_->parent_ = pivot;

    child->parent_ = pivot->parent_;

    if (auto parent = pivot->parent_.lock()) {
        if (parent->left_ == pivot)
            parent->left_ = child;
        else
            parent->right_ = child;
    } else {
        root = child;
    }

    child->left_ = pivot;
    pivot->parent_ = child;
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::rotateRight(NodePtr pivot) {
    if (pivot == NIL || pivot->left_ == NIL) return; // Проверка на NIL
    auto child = pivot->left_;
    pivot->left_ = child->right_;

    if (pivot->left_)
        pivot->left_->parent_ = pivot;

    child->parent_ = pivot->parent_;

    if (auto parent = pivot->parent_.lock()) {
        if (parent->left_ == pivot)
            parent->left_ = child;
        else
            parent->right_ = child;
    } else {
        root = child;
    }

    child->right_ = pivot;
    pivot->parent_ = child;
}


template<typename T, typename T0>
void RedBlackTree<T, T0>::fixInsert(NodePtr pivot) {
    while (pivot != root && pivot->parent_.lock()->color_ == Color::RED) {
        auto parent = pivot->parent_.lock();
        auto grandparent = parent->parent_.lock();
        NodePtr uncle = (parent == grandparent->left_) ? grandparent->right_ : grandparent->left_;

        if (uncle->color_ == Color::RED) {
            // Случай 1: дядя красный.
            parent->color_ = Color::BLACK;
            uncle->color_ = Color::BLACK;
            grandparent->color_ = Color::RED;
            pivot = grandparent;
        } else {
            if (parent == grandparent->left_) {
                // Случай 2: pivot — правый потомок.
                if (pivot == parent->right_) {
                    pivot = parent;
                    rotateLeft(pivot);
                    parent = pivot->parent_.lock(); // Обновляем parent после поворота
                }
                // Случай 3: pivot — левый потомок.
                parent->color_ = Color::BLACK;
                grandparent->color_ = Color::RED;
                rotateRight(grandparent);
            } else {
                // Зеркальные случаи для правого поддерева.
                if (pivot == parent->left_) {
                    pivot = parent;
                    rotateRight(pivot);
                    parent = pivot->parent_.lock(); // Обновляем parent
                }
                parent->color_ = Color::BLACK;
                grandparent->color_ = Color::RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color_ = Color::BLACK;
}


template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::searchNode(const T &k) const {
    if (root == NIL) return NIL;
    NodePtr current = root;
    while (current != NIL) {
        if (current->key_ == k) return current;
        current = (current->key_ > k) ? current->left_ : current->right_;
    }
    return NIL;
}


template<typename T, typename T0>
void RedBlackTree<T, T0>::replaceSubtree(NodePtr oldNode, NodePtr newNode) {
    if (oldNode == NIL) return;

    if (auto parent = oldNode->parent_.lock()) {
        if (oldNode == parent->left_) {
            parent->left_ = newNode;
        } else {
            parent->right_ = newNode;
        }
    } else {
        root = newNode;
    }

    if (newNode != NIL) {
        newNode->parent_ = oldNode->parent_;
    }
}


template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::minimum(NodePtr subtreeRoot) {
    if (subtreeRoot == NIL) return NIL;
    while (subtreeRoot->left_ != NIL) {
        subtreeRoot = subtreeRoot->left_;
    }
    return subtreeRoot;
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::fixDelete(NodePtr pivot) {
    while (pivot != root && pivot->color_ == Color::BLACK) {
        auto parent = pivot->parent_.lock();
        if (!parent) break; // Защита от nullptr

        bool isLeftChild = (pivot == parent->left_);
        NodePtr sibling = isLeftChild ? parent->right_ : parent->left_;

        // Случай 1: Брат красный -> преобразуем в случаи 2-4
        if (sibling != NIL && sibling->color_ == Color::RED) {
            sibling->color_ = Color::BLACK;
            parent->color_ = Color::RED;
            if (isLeftChild) {
                rotateLeft(parent);
                sibling = parent->right_; // Обновляем брата после поворота
            } else {
                rotateRight(parent);
                sibling = parent->left_;
            }
        }

        // Случай 2: Брат чёрный, оба потомка чёрные
        if ((sibling->left_ == NIL || sibling->left_->color_ == Color::BLACK) &&
            (sibling->right_ == NIL || sibling->right_->color_ == Color::BLACK)) {
            if (sibling != NIL) {
                sibling->color_ = Color::RED;
            }
            pivot = parent; // Поднимаем проблему вверх
        } else {
            // Случай 3: Брат чёрный, ближний потомок красный
            if (isLeftChild && (sibling->right_ == NIL || sibling->right_->color_ == Color::BLACK)) {
                if (sibling->left_ != NIL) {
                    sibling->left_->color_ = Color::BLACK;
                }
                sibling->color_ = Color::RED;
                rotateRight(sibling);
                sibling = parent->right_;
            } else if (!isLeftChild && (sibling->left_ == NIL || sibling->left_->color_ == Color::BLACK)) {
                if (sibling->right_ != NIL) {
                    sibling->right_->color_ = Color::BLACK;
                }
                sibling->color_ = Color::RED;
                rotateLeft(sibling);
                sibling = parent->left_;
            }

            // Случай 4: Брат чёрный, дальний потомок красный
            sibling->color_ = parent->color_;
            parent->color_ = Color::BLACK;
            if (isLeftChild) {
                if (sibling->right_ != NIL) {
                    sibling->right_->color_ = Color::BLACK;
                }
                rotateLeft(parent);
            } else {
                if (sibling->left_ != NIL) {
                    sibling->left_->color_ = Color::BLACK;
                }
                rotateRight(parent);
            }
            pivot = root; // Выход из цикла
        }
    }
    pivot->color_ = Color::BLACK; // Корень всегда чёрный
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::createNIL() {
    auto nil = std::make_shared<Node>(T{}, Color::BLACK);
    nil->left_ = nil->right_ = nil; // Ссылки на себя
    nil->parent_ = WeakNodePtr{}; // Пустой родитель
    return nil;
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::quickSort(Vector<Pair<std::string, int>> &vec) {
    if (vec.get_size() <= 1) return;
    quickSortImpl(vec, 0, vec.get_size() - 1);
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::quickSortImpl(Vector<Pair<std::string, int>> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSortImpl(vec, low, pi - 1);
        quickSortImpl(vec, pi + 1, high);
    }
}

template<typename T, typename T0>
int RedBlackTree<T, T0>::partition(Vector<Pair<std::string, int>> &vec, int low, int high) {
    int pivot = vec[high].second;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (vec[j].second >= pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

// Инициализация статического члена NIL
template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::NIL = createNIL();

#endif //REDBLACKTREE_HPP