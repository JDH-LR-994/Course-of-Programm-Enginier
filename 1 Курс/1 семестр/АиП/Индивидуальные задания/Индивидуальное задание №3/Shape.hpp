#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__
#include "FrameRectangle.hpp"

class Shape
{
    public:
    virtual double getArea() = 0;
    virtual FrameRectangle getFrameRectangle() = 0;
    virtual void move(Point pt) = 0;
    virtual void scale(double k) = 0;
    virtual Shape* clone() = 0;
    virtual std::string getName() = 0; 
};

#endif