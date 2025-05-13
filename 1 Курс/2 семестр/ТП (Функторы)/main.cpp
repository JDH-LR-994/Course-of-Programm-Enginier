#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std::placeholders;

//Функция на проверки на чётность аргумента
bool is_even(int x) {
    return x % 2 == 0;
}

//Логически отрицаем функцию is_even, принимающую в себя один аргумент

int main() {
    std::vector v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::_Bind<std::logical_not<bool>(std::_Bind<bool (*(std::_Placeholder<1>))(int)>)> is_odd = std::bind(std::logical_not<bool>(), std::bind(is_even, _1));

    //Вывод в std::cout вектора через пробел

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    //Вывод в std::cout вектора с чётными элементами
    //    Для лямбды
    //    std::copy_if(v.begin(), v.end(),
    //    std::ostream_iterator<int>(std::cout, " "),
    //    [](const int i) { return i % 2 == 0; });

    //С функцией
    std::copy_if(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "), is_even);
    std::cout << std::endl;
    std::copy_if(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "), is_odd);
}
