#include "parser.hpp"
#include <memory>

std::unique_ptr<ExprAST> Parser::ParseNumberExpr() {
    std::string valStr = tokens[curTokenPos].value;
    double val = std::stod(valStr);
    curTokenPos++;
    
    // TASK: Create a NumberExprAST using 'val' and return it.
    // Remember: make_unique handles the 'new' keyword for you.
    return std::make_unique<NumberExprAST>(val);
}

std::unique_ptr<ExprAST> Parser::ParseParenExpr() {
    curTokenPos++; // eat '('
    
    // 1. Get the expression inside the parentheses
    auto V = ParseExpression(); 
    if (!V) return nullptr; // Error handling
    
    // 2. We expect the current token to be ')'
    if (tokens[curTokenPos].type != TokenType::RParen) {
        // Handle error: missing ')'
        return nullptr; 
    }
    
    // 3. TASK: What do we need to do with the cursor before returning V?
    // Hint: We are currently sitting on ')'.
    curTokenPos++;
    
    return V;
}

std::unique_ptr<ExprAST> Parser::ParsePrimary() {
    // 1. Get the current token type
    TokenType type = tokens[curTokenPos].type;

    // 2. TASK: Use if/else if to call the correct function
    if (type == TokenType::Number) {
        return ParseNumberExpr();
    } 
    else if (type == TokenType::LParen) {
        return ParseParenExpr();
    } 
    else {
        // Unknown token starting an expression
        return nullptr;
    }
}

// Helper function to get the precedence of the current token
int Parser::GetTokPrecedence() {
    if (curTokenPos >= tokens.size()) return -1;
    
    char op = tokens[curTokenPos].value[0];

    // Find the operator in our map
    auto it = BinopPrecedence.find(op);

    // If it's NOT in the map, it's not a math operator we recognize
    if (it == BinopPrecedence.end()) {
        return -1;
    }

    // It was found! Return the weight (the 'second' part of the pair)
    return it->second;
}

std::unique_ptr<ExprAST> Parser::ParseExpression() {
    // 1. Every expression starts with a primary (number or paren)
    auto LHS = ParsePrimary();
    if (!LHS) return nullptr;

    // 2. Now look for binary operators following the LHS.
    // We start with a base precedence of 0.
    return ParseBinOpRHS(0, std::move(LHS));
}

std::unique_ptr<ExprAST> Parser::ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
    while (true) {
        int TokPrec = GetTokPrecedence();

        // If the next operator is less important than our current floor, return what we have.
        if (TokPrec < ExprPrec)
            return LHS;

        // We have an operator!
        char BinOp = tokens[curTokenPos].value[0];
        curTokenPos++; // eat BinOp

        // Get the next primary expression
        auto RHS = ParsePrimary();
        if (!RHS) return nullptr;

        // Lookahead: check the operator to the right of RHS
        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec) {
            // RHS binds more tightly to the NEXT operator
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS) return nullptr;
        }

        // Merge LHS, BinOp, and RHS into a new LHS
        LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}