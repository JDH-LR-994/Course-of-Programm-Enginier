#include <iostream>
#include <cmath>
#include <iomanip> //Для вывода числа с определенным количеством знаков после запятой

class Triangle
{
public:
    Triangle() {}
    // Создание треугольника по координатам вершин
    friend std::istream &operator>>(std::istream &stream, Triangle &tr)
    {
        stream >> tr.A >> tr.B >> tr.C;
        // Проверка на построение треугольника
        if (!tr.is_triangle())
        {
            std::cerr << "ERROR: it is impossible to construct a triangle from given points";
            exit(1);
        }
        return stream;
    }
    // Вывод координат вершин
    friend std::ostream &operator<<(std::ostream &stream, Triangle &tr)
    {
        stream << tr.A << tr.B << tr.C;
        return stream;
    }

    double get_perimeter()
    {
        return perimeter;
    }

    bool operator==(Triangle &tr)
    {
        return A == tr.A && B == tr.B && C == tr.C;
    }

    double get_area()
    {
        return area;
    }
    bool operator<(Triangle &tr)
    {
        return area < tr.area;
    }
    // Сдвинуть все точки на k
    Triangle &operator+=(int k)
    {
        A += k;
        B += k;
        C += k;
        return *this;
    }

private:
    // Описание точек
    class Point
    {
    public:
        Point() : x_(0), y_(0) {}
        Point(int x, int y) : x_(x), y_(y) {}

        // Ввод координат точки
        friend std::istream &operator>>(std::istream &stream, Point &pt)
        {
            stream >> pt.x_ >> pt.y_;
            return stream;
        }
        // Вывод координат точки
        friend std::ostream &operator<<(std::ostream &stream, Point &pt)
        {
            stream << "(" << pt.x_ << "," << pt.y_ << ") ";
            return stream;
        }

        bool operator==(Point &pt)
        {
            return (x_ == pt.x_) && (y_ == pt.y_);
        }

        double get_lenght(Point &A)
        {
            return std::sqrt(std::pow((A.x_ - x_), 2) + std::pow((A.y_ - y_), 2));
        }

        Point &operator+=(int k)
        {
            x_ += k;
            y_ += k;
            return *this;
        }

    private:
        int x_, y_;
    };
    Point A, B, C;
    double perimeter, area;

    bool is_triangle()
    {
        double AB = A.get_lenght(B);
        double AC = A.get_lenght(C);
        double BC = B.get_lenght(C);
        this->perimeter = AB + AC + BC; // Сразу считаем периметр треугольника
        double s = perimeter / 2;
        this->area = std::sqrt(s * (s - AB) * (s - AC) * (s - BC)); // Сразу считаем площадь треугольника
        return (AB + AC > BC) && (BC + AB > AC) && (BC + AC > AB);
    }
};

// Само задание
int main()
{
    Triangle triangleR;
    std::cin >> triangleR;
    Triangle triangleP;
    std::cin >> triangleP;
    if (triangleR == triangleP)
    {
        std::cout << "The triangles are equal" << std::endl;
    }
    else
    {
        std::cout << "The triangles are not equal" << std::endl;
    }
    if (triangleR < triangleP)
    {
        std::cout << "The area of the first triangle is less than the second" << std::endl;
    }
    else
    {
        std::cout << "The area of the first triangle is NOT less than the second" << std::endl;
    }
    int k;
    std::cin >> k;
    triangleR += k;
    std::cout << "Triangle1 moved, new vertices=" << triangleR;
    return 0;
}
