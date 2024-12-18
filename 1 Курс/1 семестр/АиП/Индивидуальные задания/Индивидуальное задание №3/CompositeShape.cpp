#include "CompositeShape.h"
#include <stdexcept>
#include <algorithm>

CompositeShape::CompositeShape(size_t capacity)
    : capacity_(capacity), size_(0)
{
    if (capacity_ == 0)
    {
        throw std::invalid_argument("Capacity must be greater than zero.");
    }
    shapes_ = new Shape *[capacity_];
}

CompositeShape::CompositeShape(const CompositeShape &other)
    : capacity_(other.capacity_), size_(0)
{
    shapes_ = new Shape *[capacity_];
    copyFrom(other);
}

CompositeShape &CompositeShape::operator=(const CompositeShape &other)
{
    if (this != &other)
    {
        clear();
        delete[] shapes_;
        capacity_ = other.capacity_;
        shapes_ = new Shape *[capacity_];
        copyFrom(other);
    }
    return *this;
}

CompositeShape::~CompositeShape()
{
    clear();
    delete[] shapes_;
}

void CompositeShape::addShape(const Shape *shape)
{
    if (size_ >= capacity_)
    {
        Shape **temp = new Shape *[capacity_ * 2];
        for (size_t i = 0; i < size_; ++i)
        {
            temp[i] = shapes_[i];
        }
        delete[] shapes_;
        shapes_ = temp;
        capacity_ *= 2;
    }
    if (!shape)
    {
        throw std::invalid_argument("Shape cannot be null.");
    }
    shapes_[size_++] = shape->clone();
}

float CompositeShape::getArea() const
{
    float totalArea = 0;
    for (size_t i = 0; i < size_; ++i)
    {
        totalArea += shapes_[i]->getArea();
    }
    return totalArea;
}

FrameRectangle CompositeShape::getFrameRectangle() const
{
    if (size_ == 0)
    {
        throw std::runtime_error("CompositeShape is empty.");
    }
    float minX = shapes_[0]->getFrameRectangle().getPos().getX() - shapes_[0]->getFrameRectangle().getWidth() / 2;
    float minY = shapes_[0]->getFrameRectangle().getPos().getY() - shapes_[0]->getFrameRectangle().getHeight() / 2;
    float maxX = shapes_[0]->getFrameRectangle().getPos().getX() + shapes_[0]->getFrameRectangle().getWidth() / 2;
    float maxY = shapes_[0]->getFrameRectangle().getPos().getY() + shapes_[0]->getFrameRectangle().getHeight() / 2;

    for (size_t i = 1; i < size_; ++i)
    {
        const auto &frame = shapes_[i]->getFrameRectangle();
        float left = frame.getPos().getX() - frame.getWidth() / 2;
        float bottom = frame.getPos().getY() - frame.getHeight() / 2;
        float right = frame.getPos().getX() + frame.getWidth() / 2;
        float top = frame.getPos().getY() + frame.getHeight() / 2;

        minX = std::min(minX, left);
        minY = std::min(minY, bottom);
        maxX = std::max(maxX, right);
        maxY = std::max(maxY, top);
    }

    float width = maxX - minX;
    float height = maxY - minY;
    return FrameRectangle(width, height, Point((minX + maxX) / 2, (minY + maxY) / 2));
}

void CompositeShape::move(const Point &newPos)
{
    if (size_ == 0)
    {
        throw std::runtime_error("CompositeShape is empty.");
    }
    FrameRectangle frame = getFrameRectangle();
    float dx = newPos.getX() - frame.getPos().getX();
    float dy = newPos.getY() - frame.getPos().getY();
    move(dx, dy);
}

void CompositeShape::move(float dx, float dy)
{
    for (size_t i = 0; i < size_; ++i)
    {
        shapes_[i]->move(dx, dy);
    }
}

void CompositeShape::scale(float factor)
{
    if (factor <= 0)
    {
        throw std::invalid_argument("Scale factor must be greater than zero.");
    }
    FrameRectangle frame = getFrameRectangle();
    Point center = frame.getPos();
    for (size_t i = 0; i < size_; ++i)
    {
        Point shapeCenter = shapes_[i]->getFrameRectangle().getPos();
        float dx = shapeCenter.getX() - center.getX();
        float dy = shapeCenter.getY() - center.getY();
        shapes_[i]->move(dx * (factor - 1), dy * (factor - 1));
        shapes_[i]->scale(factor);
    }
}

CompositeShape *CompositeShape::clone() const
{
    CompositeShape *newComposite = new CompositeShape(capacity_);
    for (size_t i = 0; i < size_; ++i)
    {
        newComposite->addShape(shapes_[i]);
    }
    return newComposite;
}

std::string CompositeShape::getName() const
{
    return "CompositeShape";
}

void CompositeShape::clear()
{
    for (size_t i = 0; i < size_; ++i)
    {
        delete shapes_[i];
    }
    size_ = 0;
}

void CompositeShape::copyFrom(const CompositeShape &other)
{
    for (size_t i = 0; i < other.size_; ++i)
    {
        addShape(other.shapes_[i]);
    }
}