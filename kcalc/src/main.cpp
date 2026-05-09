#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

int main() {

    // lexer test
    /*
    std::string input = "123 + 45 * (67 - 8)";
    auto tokens = tokenize(input);

    for (const auto& token : tokens) {
        // We use a static_cast to int just for printing the enum
        std::cout << "Token Type: " << static_cast<int>(token.type) 
                  << " | Value: '" << token.value << "'" << std::endl;
    }
    */

    // parser test
    // std::string input = "3 + 4 * 5";
    std::string input = "123 + 45 * (67 - 8)";

    // Lexing
    Lexer lexer(input);
    // Lexer lexer();
    auto tokens = lexer.tokenize();

    // parsing
    Parser parser(tokens);
    auto root = parser.ParseExpression();

    if (root) {
        std::cout << "Parse Successful! Tree structure:" << std::endl;
        root->print();

        std::cout << "Result: " << root->eval() << std::endl;
    } else {
        std::cerr << "Parse Failed!" << std::endl;
    }

    return 0;
}