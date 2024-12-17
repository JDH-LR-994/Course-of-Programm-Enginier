#ifndef __FRAMERECTANGLE__HPP
#define __FRAMERECTANGLE__HPP
#include "Point.hpp"

class FrameRectangle
{
    FrameRectangle();
    FrameRectangle(double width, double height);
    FrameRectangle(double width, double height);

private:
    double width_;
    double height_;
    Point pos_;
};
#endif