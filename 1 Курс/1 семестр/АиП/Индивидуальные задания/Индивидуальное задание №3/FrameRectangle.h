#ifndef FRAMERECTANGLE_H
#define FRAMERECTANGLE_H

#include "Point.h"

class FrameRectangle {
public:
    FrameRectangle(float width, float height, const Point& pos);
    float getWidth() const;
    float getHeight() const;
    Point getPos() const;

private:
    float width_;
    float height_;
    Point pos_;
};

#endif