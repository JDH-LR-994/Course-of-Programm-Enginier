#include "IsoscelesTrapezium.h"
#include <stdexcept>

IsoscelesTrapezium::IsoscelesTrapezium(const Point& bottomLeft, float bottomBase, float topBase, float height)
    : bottomLeft_(bottomLeft), bottomBase_(bottomBase), topBase_(topBase), height_(height) {
    if (bottomBase <= 0 || topBase <= 0 || height <= 0) {
        throw std::invalid_argument("All dimensions must be positive");
    }
}

float IsoscelesTrapezium::getArea() const {
    return (bottomBase_ + topBase_) * height_ / 2;
}

FrameRectangle IsoscelesTrapezium::getFrameRectangle() const {
    float width = bottomBase_ > topBase_ ? bottomBase_ : topBase_;
    Point center(bottomLeft_.getX() + width / 2, bottomLeft_.getY() + height_ / 2);
    return FrameRectangle(width, height_, center);
}

void IsoscelesTrapezium::move(const Point& newPos) {
    float dx = newPos.getX() - (bottomLeft_.getX() + bottomBase_ / 2);
    float dy = newPos.getY() - (bottomLeft_.getY() + height_ / 2);
    move(dx, dy);
}

void IsoscelesTrapezium::move(float dx, float dy) {
    bottomLeft_.setX(bottomLeft_.getX() + dx);
    bottomLeft_.setY(bottomLeft_.getY() + dy);
}
//
//void IsoscelesTrapezium::scale(float factor) {
//    if (factor <= 0) {
//        throw std::invalid_argument("Scale factor must be positive");
//    }
//    bottomBase_ *= factor;
//    topBase_ *= factor;
//    height_ *= factor;
//}
void IsoscelesTrapezium::scale(float factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be greater than zero.");
    }
    float width = bottomBase_ > topBase_ ? bottomBase_ : topBase_;
    Point center(bottomLeft_.getX() + width / 2, bottomLeft_.getY() + height_ / 2);
    float centerX = center.getX();
    float centerY = center.getY();

    bottomBase_ *= factor;
    topBase_ *= factor;
    height_ *= factor;

    float lowerShift = (bottomBase_ / 2);

    bottomLeft_ = Point(centerX - lowerShift, centerY - height_ / 2);
}


IsoscelesTrapezium* IsoscelesTrapezium::clone() const {
    return new IsoscelesTrapezium(bottomLeft_, bottomBase_, topBase_, height_);
}

std::string IsoscelesTrapezium::getName() const {
    return "ISOTRAPEZIUM";
}