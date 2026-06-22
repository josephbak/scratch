#include <iostream>
#include <string>
#include <vector>

bool is_sep(char c) { return c == ' ' || c == ',' || c == '\t'; }

int main() {
    std::string line = "%0 = arith.addi %1, %2";

    std::vector<std::string> vec;

    std::size_t s_pt = 0;
    std::size_t e_pt = 0;

    // skip seperators -> mark start -> consume token -> emit
    while (e_pt < line.size()) {
        // skip leading separators
        while (e_pt < line.size() && is_sep(line[e_pt])) e_pt++;
        s_pt = e_pt;
        // scan the token
        while (e_pt < line.size() && !is_sep(line[e_pt])) e_pt++;
        if (s_pt != e_pt) vec.push_back(line.substr(s_pt, e_pt - s_pt));
    }

    for (const auto& ele: vec){
        std::cout << ele << '\n';
    }


    return 0;
}