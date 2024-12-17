#ifndef __POINT_HPP__
#define __POINT_HPP__
#include <iostream>

class Point
{
public:
    Point();
    Point(double x, double y);
    double getX();
    double getY();

private:
    double x_;
    double y_;
};
#endif