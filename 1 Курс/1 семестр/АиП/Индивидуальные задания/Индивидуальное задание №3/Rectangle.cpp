#include "Rectangle.hpp"

Rectangle::Rectangle(Point pt_left_down, Point pt_right_up) : pt_left_down_(pt_left_down), pt_right_up_(pt_right_up) {}

double Rectangle::getArea() { return (pt_right_up_.getX() - pt_left_down_.getX()) * (pt_right_up_.getY() - pt_left_down_.getY()); }