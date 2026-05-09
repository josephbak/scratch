#pragma once
#include <string>
#include <string_view>
#include <vector>

enum class TokenType {
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    LParen,
    RParen,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value; // For numbers, store the literal string
};

class Lexer {
public:
    explicit Lexer(std::string_view input);

    // The main entry point to get all tokens
    std::vector<Token> tokenize();
    // std::vector<Token> tokenize(std::string_view input);

private:
    std::string_view input;
    size_t pos = 0;

    // Helper to peek at the current character
    // char peek() const;
    // Helper to consume and return the current character
    // char get();
    // Skip whitespace
    // void skipWhitespace();
    // Handle number multi-digit parsing
    // Token readNumber();
};

// This is the "Contract": Give me text, I give you Tokens.
// std::vector<Token> tokenize(std::string_view input);