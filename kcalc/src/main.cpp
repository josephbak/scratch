#include <iostream>
#include "lexer.hpp"

int main() {
    std::string input = "123 + 45 * (67 - 8)";
    auto tokens = tokenize(input);

    for (const auto& token : tokens) {
        // We use a static_cast to int just for printing the enum
        std::cout << "Token Type: " << static_cast<int>(token.type) 
                  << " | Value: '" << token.value << "'" << std::endl;
    }

    return 0;
}