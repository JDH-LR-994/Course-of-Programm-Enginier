#include <iostream>
#include "Rectangle.h"
#include "IsoscelesTrapezium.h"
#include "CompositeShape.h"

void printShapeInfo(const Shape& shape) {
    FrameRectangle frame = shape.getFrameRectangle();
    std::cout << shape.getName() << " "
        << shape.getArea() << " "
        << frame.getPos().getX() - frame.getWidth() / 2 << " "
        << frame.getPos().getY() - frame.getHeight() / 2 << " "
        << frame.getPos().getX() + frame.getWidth() / 2 << " "
        << frame.getPos().getY() + frame.getHeight() / 2
        << std::endl;
    std::cout << "Center: " << frame.getPos().getX() << " " << frame.getPos().getY() << std::endl;
}

int main() {
    Rectangle rect(Point(0, 0), Point(4, 3));
    IsoscelesTrapezium trapezium(Point(0, 0), 4, 2, 3);
    CompositeShape composite(2);
    try {
        std::cout << "=== Test 1: Rectangle ===" << std::endl;
        printShapeInfo(rect);

        std::cout << "Testing movement of Rectangle" << std::endl;
        rect.move(Point(2, 2));
        printShapeInfo(rect);

        rect.move(1, -1);
        printShapeInfo(rect);

        std::cout << "Testing scaling of Rectangle" << std::endl;
        rect.scale(2);
        printShapeInfo(rect);

        std::cout << "Testing cloning of Rectangle" << std::endl;
        Shape* clonedRect = rect.clone();
        printShapeInfo(*clonedRect);

        delete clonedRect;


        std::cout << "\n=== Test 2: Isosceles Trapezium ===" << std::endl;
        printShapeInfo(trapezium);

        std::cout << "Testing movement of Trapezium" << std::endl;
        trapezium.move(Point(1, 1));
        printShapeInfo(trapezium);

        trapezium.move(-1, -1);
        printShapeInfo(trapezium);

        std::cout << "Testing scaling of Trapezium" << std::endl;
        trapezium.scale(2);
        printShapeInfo(trapezium);

        std::cout << "Testing cloning of Trapezium" << std::endl;
        Shape* clonedTrapezium = trapezium.clone();
        printShapeInfo(*clonedTrapezium);

        delete clonedTrapezium;

        std::cout << "\n=== Test 3: Composite Shape ===" << std::endl;
        composite.addShape(&rect);
        composite.addShape(&trapezium);
        printShapeInfo(composite);

        std::cout << "Testing movement of Composite Shape" << std::endl;
        composite.move(Point(5, 5));
        printShapeInfo(composite);

        composite.move(-2, -2);
        printShapeInfo(composite);

        std::cout << "Testing scaling of Composite Shape" << std::endl;
        composite.scale(0.5);
        printShapeInfo(composite);

        std::cout << "Testing cloning of Composite Shape" << std::endl;
        Shape* clonedComposite = composite.clone();
        printShapeInfo(*clonedComposite);

        delete clonedComposite;


        std::cout << "\n=== Test 4: Exception Handling ===" << std::endl;
        try {
            std::cout << "Testing invalid Rectangle creation" << std::endl;
            Rectangle invalidRect(Point(0, 0), Point(0, 0)); // Width or height is zero
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

        try {
            std::cout << "Testing invalid Trapezium creation" << std::endl;
            IsoscelesTrapezium invalidTrapezium(Point(0, 0), 0, 2, 3); // Base is zero
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

        try {
            std::cout << "Testing invalid Composite Shape scaling" << std::endl;
            composite.scale(-1); // Negative scale factor
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

        try {
            std::cout << "Testing Composite Shape exceeding capacity" << std::endl;
            CompositeShape smallComposite(1);
            smallComposite.addShape(&rect);
            smallComposite.addShape(&trapezium); // Exceeds capacity
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
