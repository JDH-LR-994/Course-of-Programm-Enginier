#include "solution.hpp"


int main() {
    // true
    std::cout << std::boolalpha; // Для вывода true/false вместо 1/0
    std::cout << check_expression("a+b*c") << '\n';
    std::cout << check_expression("1+2*3") << '\n';
    std::cout << check_expression("(a+b)*c") << '\n';
    std::cout << check_expression("x/y-z") << '\n';

    // false
    std::cout << check_expression("1+2*") << '\n';
    std::cout << check_expression("a+") << '\n';
    std::cout << check_expression("(a+b") << '\n';
    std::cout << check_expression("+a*b") << '\n';

    return 0;
}
