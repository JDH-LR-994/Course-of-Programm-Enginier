#ifndef __RECTANGLE_HPP__
#define __RECTANGLE_HPP__
#include "Shape.hpp"

class Rectangle: Shape{
    public:
    Rectangle(Point pt_left_down, Point pt_right_up);
    double getArea() override;
    
    private:
    Point pt_left_down_;
    Point pt_right_up_;
};

#endif // __RECTANGLE_HPP__
