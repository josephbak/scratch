#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
    }

    // 1. Open the file
    std::ifstream file(argv[1]);

    // 2. Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    int count = 0;
    std::string word;

    while (file >> word) {
        count++;
    }

    std::cout << "The number of words in the file is: " << count << '\n';

    return 0;
}