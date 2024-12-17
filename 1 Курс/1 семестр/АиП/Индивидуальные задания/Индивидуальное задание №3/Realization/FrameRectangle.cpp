#include "FrameRectangle.hpp"

FrameRectangle::FrameRectangle() : width_(600), height_(800), pos_(Point(0.0, 0.0)) {};
FrameRectangle::FrameRectangle(double width, double height) : width_(width), height_(height), pos_(Point(width / 2, height / 2)) {}