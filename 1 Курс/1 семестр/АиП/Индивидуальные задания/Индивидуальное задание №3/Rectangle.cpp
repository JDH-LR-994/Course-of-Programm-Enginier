#include "Rectangle.h"
#include <cmath>
#include <stdexcept>

Rectangle::Rectangle(const Point& bottomLeft, const Point& topRight)
    : bottomLeft_(bottomLeft), topRight_(topRight) {
    if (bottomLeft.getX() >= topRight.getX() || bottomLeft.getY() >= topRight.getY()) {
        throw std::invalid_argument("Invalid rectangle dimensions");
    }
}

float Rectangle::getArea() const {
    float width = topRight_.getX() - bottomLeft_.getX();
    float height = topRight_.getY() - bottomLeft_.getY();
    return width * height;
}

FrameRectangle Rectangle::getFrameRectangle() const {
    float width = topRight_.getX() - bottomLeft_.getX();
    float height = topRight_.getY() - bottomLeft_.getY();
    Point center((bottomLeft_.getX() + topRight_.getX()) / 2,
        (bottomLeft_.getY() + topRight_.getY()) / 2);
    return FrameRectangle(width, height, center);
}

void Rectangle::move(const Point& newPos) {
    float dx = newPos.getX() - (bottomLeft_.getX() + topRight_.getX()) / 2;
    float dy = newPos.getY() - (bottomLeft_.getY() + topRight_.getY()) / 2;
    move(dx, dy);
}

void Rectangle::move(float dx, float dy) {
    bottomLeft_.setX(bottomLeft_.getX() + dx);
    bottomLeft_.setY(bottomLeft_.getY() + dy);
    topRight_.setX(topRight_.getX() + dx);
    topRight_.setY(topRight_.getY() + dy);
}

void Rectangle::scale(float factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    Point center((bottomLeft_.getX() + topRight_.getX()) / 2,
        (bottomLeft_.getY() + topRight_.getY()) / 2);
    float width = (topRight_.getX() - bottomLeft_.getX()) / 2 * factor;
    float height = (topRight_.getY() - bottomLeft_.getY()) / 2 * factor;
    bottomLeft_ = Point(center.getX() - width, center.getY() - height);
    topRight_ = Point(center.getX() + width, center.getY() + height);
}

Rectangle* Rectangle::clone() const {
    return new Rectangle(bottomLeft_, topRight_);
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}