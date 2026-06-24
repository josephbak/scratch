#include <iostream>
#include <cassert>

class Shape {
public:
    enum class Kind { Circle, Rectangle };
private:
    const Kind kind_;
public:
    Shape(Kind k) : kind_(k) {}
    Kind getKind() const {return kind_;}
};

class Circle : public Shape{
public:
    Circle() : Shape(Kind::Circle) {}
    static bool classof(const Shape* s) { return s->getKind() == Kind::Circle; }
};

class Rectangle : public Shape{
public:
    Rectangle() : Shape(Kind::Rectangle) {}
    static bool classof(const Shape* s) { return s->getKind() == Kind::Rectangle; }
};

template <typename T>
bool myIsa (const Shape* s) {
    return T::classof(s);
}

template <typename T>
T* myDynCast(Shape* s) {
    return myIsa<T>(s) ? static_cast<T*>(s) : nullptr;
}

template <typename T>
T* myCast(Shape* s) {
    assert(myIsa<T>(s) && "myCast: type mismatch");   // fires in debug if wrong
    return static_cast<T*>(s);                         // unconditional — no nullptr branch
}

int main() {
    Circle c;
    Shape* s = &c;                          // base pointer, concrete type "hidden"

    if (auto* p = myDynCast<Circle>(s))
        std::cout << "it's a Circle\n";     // runs — s really is a Circle

    if (auto* p = myDynCast<Rectangle>(s))
        std::cout << "it's a Rectangle\n";  // skipped — myDynCast returns nullptr
    else
        std::cout << "not a Rectangle\n";

    std::cout << myIsa<Circle>(s) << " " << myIsa<Rectangle>(s) << "\n";  // 1 0
    return 0;
}