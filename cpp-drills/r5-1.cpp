#include <iostream>
#include <string>
#include <string_view>
#include <vector>

bool is_sep(char c) { return c == ' ' || c == ',' || c == '\t'; }

int main() {
    std::string line = "%0 = arith.addi %1, %2";

    std::vector<std::string_view> vec;

    std::size_t s_pt = 0;
    std::size_t e_pt = 0;

    // skip seperators -> mark start -> consume token -> emit
    while (e_pt < line.size()) {
        // skip leading separators
        while (e_pt < line.size() && is_sep(line[e_pt])) e_pt++;

        // mark
        s_pt = e_pt;

        // consume, scan the token
        while (e_pt < line.size() && !is_sep(line[e_pt])) e_pt++;

        /// emit
        if (s_pt != e_pt) vec.push_back(std::string_view(line).substr(s_pt, e_pt - s_pt));
    }

    for (const auto& ele: vec){
        std::cout << ele << '\n';
    }


    return 0;
}