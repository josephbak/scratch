#include <iostream>
#include <functional>

std::function<int()> makeBadLambda() {
    int n = 42;
    // return [n]() { return n; };
    return [&]() { return n; };
}

int main() {
    auto f = makeBadLambda();
    std::cout << f() << '\n';

    return 0;
}