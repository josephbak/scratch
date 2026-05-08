#include "lexer.hpp"
#include <cctype> // for std::isdigit, std::isspace

std::vector<Token> tokenize(std::string_view input) {
    std::vector<Token> tokens;
    size_t pos = 0;

    while (pos < input.length()) {
        char current = input[pos];

        // 1. Skip whitespace
        if (std::isspace(current)) {
            pos++;
            continue;
        }

        // 2. Handle Single-character operators
        if (current == '+') {
            tokens.push_back({TokenType::Plus, "+"});
            pos++;
            continue;
        }
        else if (current == '(') {
            tokens.push_back({TokenType::LParen, "("});
            pos++;
            continue;
        } else if (current == ')') {
            tokens.push_back({TokenType::RParen, ")"});
            pos++;
            continue;
        } else if (current == '*') {
            tokens.push_back({TokenType::Star, "*"});
            pos++;
            continue;
        } else if (current == '-') {
            tokens.push_back({TokenType::Minus, "-"});
            pos++;
            continue;
        }

        // 3. TODO: Handle Numbers (The Multi-digit Logic)
        // Hint: If isdigit(current), start a new loop to collect digits.
        if (std::isdigit(current)) {
            size_t start = pos;
            while (pos < input.length() && std::isdigit(input[pos])) {
                pos++;
            }

            // Create a view of just the digits
            std::string_view num_slice = input.substr(start, pos - start);
            // Convert view to an owning string and store it
            tokens.push_back({TokenType::Number, std::string(num_slice)});
            
            continue; // Jump back to start of main while-loop
            // Crucial: We don't want the pos++ at the bottom to run
            
        }

        // 4. Error handling: Unknown character
        pos++; 
    }

    tokens.push_back({TokenType::EndOfFile, ""});
    return tokens;
}