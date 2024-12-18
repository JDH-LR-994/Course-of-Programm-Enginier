#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "Shape.h"

class CompositeShape : public Shape {
public:
    CompositeShape(size_t capacity);
    CompositeShape(const CompositeShape& other);
    CompositeShape& operator=(const CompositeShape& other);
    ~CompositeShape();

    void addShape(const Shape* shape);
    float getArea() const override;
    FrameRectangle getFrameRectangle() const override;
    void move(const Point& newPos) override;
    void move(float dx, float dy) override;
    void scale(float factor) override;
    CompositeShape* clone() const override;
    std::string getName() const override;

private:
    Shape** shapes_;
    size_t capacity_;
    size_t size_;
    void clear();
    void copyFrom(const CompositeShape& other);
};
#endif