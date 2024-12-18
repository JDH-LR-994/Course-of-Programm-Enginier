#include "Point.h"
#include <stdexcept>

Point::Point(float x, float y) : x_(x), y_(y) {}

float Point::getX() const {
    return x_;
}

float Point::getY() const {
    return y_;
}

void Point::setX(float x) {
    x_ = x;
}

void Point::setY(float y) {
    y_ = y;
}