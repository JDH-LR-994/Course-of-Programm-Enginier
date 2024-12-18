#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(float x = 0, float y = 0);
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);

private:
    float x_;
    float y_;
};

#endif