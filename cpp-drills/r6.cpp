#include <iostream>

struct Vec2 {
    double x;
    double y;

    // Vec2(double X, double Y) : x(X), y(Y) {}

    Vec2 operator+(const Vec2& o) const {
        return {x + o.x, y + o.y}; 
    }
    
    // Vec2 operator*(double scale) const {
    //     return {x * scale, y* scale};
    // }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v){
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

Vec2 operator*(double scale, const Vec2& a) {
    return {a.x * scale, a.y * scale};
}

Vec2 operator*(const Vec2& a, double scale) {
    return {a.x * scale, a.y * scale};
}

int main() {
    Vec2 vec1{1, 2};
    Vec2 vec2{3, 4};

    Vec2 vec3 = vec1 + vec2;
    Vec2 vec4 = vec1 * 2;

    Vec2 vec5 = 5 * vec1;


    std::cout << "vec1: " << vec1 << '\n';
    std::cout << "vec3: " << vec3 << '\n';
    std::cout << "vec4: " << vec4 << '\n';
    std::cout << "vec5: " << vec5 << '\n';

    return 0;
}