#include <iostream>
#include <cmath>
#include <iomanip> //Для вывода числа с определенным количеством знаков после запятой
#ifdef _MSC_VER
#define __FS__ __FUNCSIG__
#else
#define __FS__ __PRETTY_FUNCTION__
#endif

class Triangle
{
public:
    Triangle() {
        std::cout << __FS__ << this << std::endl;
    }
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
    // Сдвинуть все точки на k
    Triangle &operator+=(int k)
    {
        A += k;
        B += k;
        C += k;
        return *this;
    }
    ~Triangle(){
        std::cout << __FS__ << this << std::endl;
    
    }
private:
    // Описание точек
    class Point
    {
    public:
        Point() : x_(0), y_(0) {
            std::cout << __FS__ << this << std::endl;
        }
        Point(int x, int y) : x_(x), y_(y) {
            std::cout << __FS__ << this << std::endl;
        }

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

        ~Point (){
            std::cout << __FS__ << this << std::endl;
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
    std::cout << "perimeterR: " << std::setprecision(3) << triangleR.get_perimeter() << std::endl;
    Triangle triangleP;
    std::cin >> triangleP;
    std::cout << "perimeterP: " << std::setprecision(3) << triangleP.get_perimeter() << std::endl;
    if (triangleR == triangleP)
    {
        std::cout << "The triangles are equal" << std::endl;
    }
    else
    {
        std::cout << "The triangles are not equal" << std::endl;
    }
    if (triangleP.get_area() == triangleR.get_area())
    {
        std::cout << "The areas are equal" << std::endl;
    }
    else
    {
        std::cout << "The areas are not equal" << std::endl;
    }
    int k;
    std::cin >> k;
    triangleP += k;
    std::cout << "TriangleP moved, new vertices=" << triangleP;
    return 0;
}
