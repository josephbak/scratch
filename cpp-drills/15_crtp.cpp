#include <iostream>

template <typename Sub>
class Shape {
public:
    void printArea() const {
        static_cast<const Sub*>(this)->areaImpl();
    }

    // void areaImpl() const { std::cout << "Shape are. \n";}
};

class Circle : public Shape<Circle> {
public:
    void areaImpl() const { std::cout << "Circle area.\n"; }
};

class Rectangle : public Shape<Rectangle> {
public:
    void areaImpl() const { std::cout << "Rectangle area. \n"; }
};

int main() {
    Circle c;
    Rectangle r;
    c.printArea();   // Circle area.
    r.printArea();   // Rectangle area.
    return 0;
}