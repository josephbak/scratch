#include <iostream>
#include <algorithm>

template <typename T>
T myMax(T a, T b) {
    return std::max(a, b);
}

int main(){
    auto a = myMax(3, 7);
    std::cout << "value: " << a << ", type: " <<  typeid(a).name() << '\n';

    auto b = myMax(2.5, 9.1);
    std::cout << "value: " << b << ", type: " <<  typeid(b).name() << '\n';

    // auto c = myMax(3, 9.1);
    // std::cout << "value: " << c << ", type: " <<  typeid(c).name() << '\n';

    auto d = myMax<double>(3, 9.1);
    std::cout << "value: " << d << ", type: " <<  typeid(d).name() << '\n';
    return 0;
}