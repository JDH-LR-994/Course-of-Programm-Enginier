#include <iostream>
#include <math.h>

#ifdef _MSC_VER
#define __FS__ __FUNCSIG__
#else
#define __FS__ __PRETTY_FUNCTION__
#endif

class Point {
private:
    int x_;
    int y_;

public:
    //конструктор
    Point() = default;
    Point(int x, int y) :
        x_(x),
        y_(y)
    {
        std::cout << __FS__ << this << '\n';
    }

    int GetX() const {
        return x_;
    }
    int GetY() const {
        return y_;
    }

    void SetX(int x) {
        x_ = x;
    }
    void SetY(int y) {
        y_ = y;
    }

    //метод для нахождения расстояния до другой точки
    double distance(const Point* b) const {
        return sqrt(pow(b->GetX() - x_, 2) + pow(b->GetY() - y_, 2));
    }

    //переопределение оператора ввода
    friend std::istream& operator >> (std::istream& in, Point& point) {
        in >> point.x_ >> point.y_;
        return in;
    }

    //переопределение оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.GetX() << "," << point.GetY() << ")";
        return os;
    }
};

class Triangle {
private:
    Point a_;
    Point b_;
    Point c_;
public:
    //конструктор
    Triangle() = default;
    Triangle(Point a, Point b, Point c) :
        a_(a),
        b_(b),
        c_(c)
    {
        std::cout << __FS__ << this << '\n';
    }
    void SetA(Point a) {
        a_ = a;
    }
    void SetB(Point b) {
        b_ = b;
    }
    void SetC(Point c) {
        c_ = c;
    }

    Point GetA() {
        return a_;
    }
    Point GetB() {
        return b_;
    }
    Point GetC() {
        return c_;
    }

    //метод для определения является ли фигура треугольником
    bool IsTriangle() const {
        double ab = a_.distance(&b_);
        double ac = a_.distance(&c_);
        double bc = b_.distance(&c_);
        if (((ab + bc) > ac) && ((ab + ac) > bc) && ((bc + ac) > ab)) {
            return true;
        }
        else {
            return false;
        }
    }

    //определение периматера треугольник
    double perimetr() const {
        double ab = a_.distance(&b_);
        double ac = a_.distance(&c_);
        double bc = b_.distance(&c_);
        return (ab + ac + bc);
    }

    //определение площади треугольника по формуле Герона
    double area() const {
        double p = this->perimetr();
        double ab = a_.distance(&b_);
        double ac = a_.distance(&c_);
        double bc = b_.distance(&c_);
        return sqrt(p * (p - ab) * (p - ac) * (p - bc));
    }

    //перемещение треугольника
    void move(int k) {
        a_.SetX(a_.GetX() + k);
        a_.SetY(a_.GetY() + k);
        b_.SetX(b_.GetX() + k);
        b_.SetY(b_.GetY() + k);
        c_.SetX(c_.GetX() + k);
        c_.SetY(c_.GetY() + k);
    }

    //переопределенеи оператора ввода
    friend std::istream& operator >> (std::istream& in, Triangle& triangle) {
        in >> triangle.a_ >> triangle.b_ >> triangle.c_;
        return in;
    }

    //переопределение оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
        os << triangle.a_ << " " << triangle.b_ << " " << triangle.c_;
        return os;
    }

    //переопределенеи оператора меньше
    bool operator < (const Triangle& left) const {
        if (this->area() < left.area()) {
            return true;
        }
        else {
            return false;
        }
    }

    //переопределение оператора +=
    Triangle& operator += (int k) {
        this->move(k);
        return *this;
    }

    //переопределение оператора сравнения
    bool operator == (const Triangle& left) const {
        double ab = a_.distance(&b_);
        double ac = a_.distance(&c_);
        double bc = b_.distance(&c_);
        double ab_ = left.a_.distance(&left.b_);
        double ac_ = left.a_.distance(&left.c_);
        double bc_ = left.b_.distance(&left.c_);
        if ((ab == ab_) && (((ac == ac_) && (bc == bc_)) || ((bc == ac_) && (ac == bc_)))) {
            return true;
        }
        else {
            if ((ab == ac_) && (((ac == ab_) && (bc == bc_)) || ((bc == ab_) && (ac == bc_)))) {
                return true;
            }
            else {
                if ((ab == bc_) && (((bc == ab_) && (ac == ac_)) || ((ac == ab_) && (bc == ac_)))) {
                    return false;
                }
                else {
                    return false;
                }
            }
        }
    }
};

int main()
{
    Point point1 = { 2 , 4 };
    Triangle triangle1;
    Triangle triangle2;

    std::cin >> triangle1;
    if (triangle1.IsTriangle()) {
        //std::cout.precision(3);
        //std::cout << "perimeterR: " << triangle1.perimetr() << std::endl;
    }
    else {
        std::cout << "ERROR: it is impossible to construct a triangle from given points";
        exit(1);
    }

    std::cin >> triangle2;

    if (triangle2.IsTriangle()) {
        //std::cout.precision(3);
        //std::cout << "perimeterR: " << triangle2.perimetr() << std::endl;
        if (triangle1 == triangle2) {
            std::cout << "The triangles are equal" << std::endl;
        }
        else {
            std::cout << "The triangles are not equal" << std::endl;
        }
        //if (triangle2.area() == triangle1.area()) {
        //    std::cout << "The areas are equal" << std::endl;
        //}
        //else {
        //    std::cout << "The areas are not equal" << std::endl;
        //}

        if (triangle1 < triangle2) {
            std::cout << "The area of the first triangle is less than the second" << std::endl;
        }
        else {
            std::cout << "The area of the first triangle is NOT less than the second" << std::endl;
        }

        int k;
        std::cin >> k;

        triangle1 += k;

        std::cout << "Triangle1 moved, new vertices=" << triangle1 << std::endl;

        return 0;
    }
    else {
        std::cout << "ERROR: it is impossible to construct a triangle from given points" << std::endl;
        exit(1);
    }
}