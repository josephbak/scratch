#include <iostream>



class Shape {
public:
    // virtual void area() const {std::cout << "Shape's area \n";};
    virtual void area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void area() const override { std::cout << "circle's area \n";}
};

class Rectangle : public Shape {
public:
    // void area() const override { std::cout << "rectangle's area \n";}
};

void describe(const Shape& s) { s.area(); }

int main() {
    Circle c;
    Rectangle r;
    describe(c);
    describe(r);

    // Shape* s1 = new Circle();
    // Shape* s2 = new Rectangle();

    // s1->area();
    // s2->area();

    // delete s1;
    // delete s2;
    return 0;
}