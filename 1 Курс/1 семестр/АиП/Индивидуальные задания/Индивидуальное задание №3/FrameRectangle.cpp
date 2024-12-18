#include "FrameRectangle.h"
#include <stdexcept>

FrameRectangle::FrameRectangle(float width, float height, const Point& pos)
    : width_(width), height_(height), pos_(pos) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
}

float FrameRectangle::getWidth() const {
    return width_;
}

float FrameRectangle::getHeight() const {
    return height_;
}

Point FrameRectangle::getPos() const {
    return pos_;
}