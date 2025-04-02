#include <fstream>
#include <iostream>

int main() {
    std::ifstream f("test.txt");
    while (!f.eof()) // попробуйте заменить на while (f)
    {
        int a = 10;
        f >> a;
        std::cout << a << '\n'
                << "good:   " << f.good() << '\n'
                << "fail:   " << f.fail() << '\n'
                << "bad:    " << f.bad() << '\n'
                << "eof:    " << f.eof() << '\n'
                << "(bool): " << static_cast<bool>(f) << '\n';
    }
}
