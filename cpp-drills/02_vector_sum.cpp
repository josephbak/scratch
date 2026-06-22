#include <cstddef>
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int raw_sum = 0;
    for (int x: nums) raw_sum += x;
    // for (int i = 0; i < nums.size(); ++i) {
    //     raw_sum += nums[i];
    // }

    std::cout << "the raw sum is: " << raw_sum << '\n';

    int acc_sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "the acc sum is: " << acc_sum << '\n';

    return 0;
}