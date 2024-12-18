#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& bottomLeft, const Point& topRight);
    float getArea() const override;
    FrameRectangle getFrameRectangle() const override;
    void move(const Point& newPos) override;
    void move(float dx, float dy) override;
    void scale(float factor) override;
    Rectangle* clone() const override;
    std::string getName() const override;

private:
    Point bottomLeft_;
    Point topRight_;
};

#endif