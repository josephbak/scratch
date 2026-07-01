#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    /*
    std::vector<int> v = {5, 2, 8, 1, 9, 3};
    int threshold = 6;
    auto it = std::find_if(v.begin(), v.end(), [&](int n ){return n > threshold; });
    if (it != v.end()) {
        std::cout << "the first number that's greater than the threshold is: " << *it << '\n';
        auto pos = std::distance(v.begin(), it);   // index of the found element
        std::cout << "at index " << pos << '\n';   // → 2  (8 is v[2])
        std::cout << "raw substraction: " << it - v.begin() << '\n';
    } else {
        std::cout << "no number is greater than the threshold.\n";
    }
    */

    /*
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> squares(v.size());

    std::transform(v.begin(), v.end(), squares.begin(),[](int n){ return n * n; });
    for (auto ele : squares) {
        std::cout << ele << '\n';
    }
    */

    /*
    std::vector<int> v = {5, 2, 8, 1, 9, 3, 7};
    auto newEnd = std::remove_if(v.begin(), v.end(), [](int n){ return n > 4;});
    std::cout << "--------------------------\n";
    // std::cout << *newEnd << '\n';
    std::cout << std::distance(v.begin(), newEnd) << '\n';
    std::cout << "--------------------------\n";
    v.erase(newEnd, v.end());
    for (auto ele : v) {
        std::cout << ele << '\n';
    }
    */

    std::vector<int> v = {5, 2, 8, 1, 9, 3};
    int sum = 0;
    int count = 0;

    std::for_each(v.begin(), v.end(), [=](int n) mutable {
        if (n > 4) count++;
        sum += n;

        std::cout << sum << '\n';
    });

    std::cout << "=======================================\n";
    std::cout << "sum: " << sum << ", count: " << count << '\n';

//    std::cout << std::accumulate(v.begin(), v.end(), 0) << '\n';

    return 0;

}