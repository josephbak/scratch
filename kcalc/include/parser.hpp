#pragma once
#include "lexer.hpp"
#include "ast.hpp"
#include <memory>
#include <vector>
#include <map>
#include <iostream>

class Parser {
    std::vector<Token> tokens;
    size_t curTokenPos = 0;

    // Map of operator character to its precedence level
    std::map<char, int> BinopPrecedence;

    public:
        // Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}
        Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
            // Initialize our precedence table
            BinopPrecedence['+'] = 20;
            BinopPrecedence['-'] = 20;
            BinopPrecedence['*'] = 40;
            // Precedence['/'] = 40; // Add this if you added '/' to your lexer
        }

        // Our parsing methods will go here...
        std::unique_ptr<ExprAST> ParseNumberExpr(); 
        std::unique_ptr<ExprAST> ParseParenExpr();
        std::unique_ptr<ExprAST> ParsePrimary();
        std::unique_ptr<ExprAST> ParseExpression();
        std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
        int GetTokPrecedence();
};