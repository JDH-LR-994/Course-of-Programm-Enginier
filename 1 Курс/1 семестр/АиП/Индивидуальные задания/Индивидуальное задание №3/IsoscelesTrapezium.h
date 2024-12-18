#ifndef ISOCELESTRAPEZIUM_H
#define ISOCELESTRAPEZIUM_H

#include "Shape.h"

class IsoscelesTrapezium : public Shape {
public:
    IsoscelesTrapezium(const Point& bottomLeft, float bottomBase, float topBase, float height);
    float getArea() const override;
    FrameRectangle getFrameRectangle() const override;
    void move(const Point& newPos) override;
    void move(float dx, float dy) override;
    void scale(float factor) override;
    IsoscelesTrapezium* clone() const override;
    std::string getName() const override;

private:
    Point bottomLeft_;
    float bottomBase_;
    float topBase_;
    float height_;
};

#endif