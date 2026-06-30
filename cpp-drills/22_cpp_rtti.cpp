#include <iostream>
#include <memory>

struct Shape {
    // virtual ~Shape() = default;   // minimum needed for RTTI
    virtual ~Shape() { std::cout << "Shape destruct\n";}
};

struct Rec : Shape {
    ~Rec() { std::cout << "Rec destruct\n"; }
    void length() const { std::cout << "Rec length\n"; }
};

struct Circle : Shape {
    ~Circle() {std::cout << "Circle destruct\n"; }
    void radius() const { std::cout << "Circle radius\n"; }
};

struct Unit : Circle {
    ~Unit() { std::cout << "Unit destruct\n"; }

};

void describe1(const Shape* s) {
    if (auto u = dynamic_cast<const Unit*>(s)) {
        std::cout << "unit\n";
    }else if (auto c = dynamic_cast<const Circle*>(s)) {
        std::cout << "circle\n";
    } else { std::cout << "other\n"; }
}


void describe2(const Shape* s) {
    if (typeid(*s) == typeid(Unit)) {
        std::cout << "unit\n";
    }else if (typeid(*s) == typeid(Circle) ) {
        std::cout << "circle\n";
    } else { std::cout << "other\n"; }
}

int main() {

    Shape* p = new Unit();

    describe1(p);
    std::cout << "-------------------------\n";
    describe2(p);
    std::cout << "-------------------------\n";

    delete p;

    return 0;
}