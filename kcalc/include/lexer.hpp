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

// This is the "Contract": Give me text, I give you Tokens.
std::vector<Token> tokenize(std::string_view input);