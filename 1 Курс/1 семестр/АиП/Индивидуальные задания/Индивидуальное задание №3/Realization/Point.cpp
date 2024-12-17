#include "Point.hpp"

Point::Point() : x_(0), y_(0) {}

Point::Point(double x, double y) : x_(x), y_(y) {}

Point::getX() {return x_}

Point::getY() {return y_}