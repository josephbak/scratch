#include <iostream>
#include <span>
#include <vector>

int sum(std::span<const int> xs) {
    int total = 0;
    for (int x: xs) total += x;
    return total;
}

std::span<const int> makeView() {
    std::vector<int> local = {1, 2, 3};
    return local;          // return a span viewing `local`
}                          // ← what happens to `local` here?


int main() {
    // // 2. call it with a std::vector  → span views the vector's buffer, no copy
    // std::vector<int> v = {1, 2, 3, 4};
    // std::cout << sum(v) << '\n';        // expect 10

    // // 3. call it with a C array       → same function, different backing store
    // int arr[] = {10, 20, 30};
    // std::cout << sum(arr) << '\n';      // expect 60

    std::span<const int> a = makeView();

    for (std::size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << '\n';
    }

    return 0;

}