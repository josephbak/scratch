#include <iostream>

void printAll() {
    std::cout << "done!\n";
}

template<typename First, typename... Rest>
void printAll(First first, Rest... rest) {
    std::cout << first << ' ';
    printAll(rest...);
}


int main() {
    printAll(1, 2.5, "hi");
    return 0;
}