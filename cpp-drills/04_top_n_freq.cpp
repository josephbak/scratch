#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>


int main(int argc, char** argv) {

    // check if argv[1] is accesible
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    // std::map<std::string, int> freq;
    std::unordered_map<std::string, int> freq;
    std::string word;

    while (file >> word) {
        ++freq[word];
    }

    std::vector<std::pair<std::string, int>> vec;
    for (const auto& [key, value] : freq) {
        // vec.push_back({key, value});
        vec.emplace_back(key, value);
    }

    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b){
        if (a.second != b.second) return a.second > b.second;  // primary: count desc
        return a.first < b.first;                              // tie-break: word asc
    });

    for (std::size_t i = 0; i < 5 && i < vec.size(); ++i) {
        std::cout << i + 1 << ": " << vec[i].first << ", freq: " << vec[i].second << '\n';
    }


    return 0;
}