#include <iostream>
#include <vector>
#include <map>
#include <cxxabi.h>
#include <typeinfo>
#include <memory>

std::string demangle(const char* name) {
    int status = 0;
    std::unique_ptr<char, void(*)(void*)> res(
        abi::__cxa_demangle(name, nullptr, nullptr, &status),
        std::free);
    return (status == 0) ? res.get() : name;
}

int main() {
    int arr[3] = {10, 20, 30};
    int* p = arr;

    while (p != arr + 3) {
        std::cout << *p << '\n';
        p++;
    }

    std::vector<int> v = {1, 2, 3};
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << '\n';
    }

    std::map<std::string, int> m = {{"apple", 3}, {"cherry", 2},  {"banana", 1}}; 
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << ", " << it->second << '\n';
    }

    auto it = m.begin();
    std::cout << typeid(*it).name() << '\n';
    std::cout << demangle(typeid(*it).name()) << '\n';


    // arr ↔ begin(), arr+3 ↔ end(), *p ↔ *it, ++p ↔ ++it

    return 0;
}