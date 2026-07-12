#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> m;
    m["alice"] = 30;
    m["bob"]   = 25;

    // 1. find — read without inserting
    if (auto it = m.find("alice"); it != m.end())
        std::cout << "alice: " << it->second << '\n';

    // 2. the operator[] trap — prove it inserts
    std::cout << "size before: " << m.size() << '\n';   // 2
    int x = m["charlie"];                                 // INSERTS charlie=0
    std::cout << "charlie: " << x << ", size after: " << m.size() << '\n';  // 0, size 3

    std::cout << "====================================================\n";

    // 3. iterate
    for (const auto& [name, age] : m)
        std::cout << name << " -> " << age << '\n';
}