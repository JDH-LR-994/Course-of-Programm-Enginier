#include <iostream>

class Point
{
public:
    Point() : x_(0), y_(0) {}
    Point(double x, double y) : x_(x), y_(y) {}

private:
    double x_;
    double y_;
};

class Rectangle
{

public:
    Rectangle(Point pt_left_down, Point pt_right_up): pt_left_down_(pt_left_down), pt_right_up_(pt_right_up) {}

private:
    Point pt_left_down_;
    Point pt_right_up_;
};


int main(){
    Point pt_1 = Point(1, 1);
    Point pt_2 = Point(2, 2);
    Rectangle rect(pt_1, pt_2);
}
