#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual void print(int indent = 0) const = 0;
    virtual double eval() const = 0; // New method
};

class NumberExprAST : public ExprAST {
    double Val;
public:
    NumberExprAST(double Val) : Val(Val) {}

    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "Number: " << Val << "\n";
    }

    double eval() const override { return Val; }
};

class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;
public:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "Op: " << Op << "\n";
        LHS->print(indent + 2);
        RHS->print(indent + 2);
    }

    double eval() const override {
        double left = LHS->eval();
        double right = RHS->eval();
        if (Op == '+') return left + right;
        if (Op == '-') return left - right;
        if (Op == '*') return left * right;
        if (Op == '/') return left / right;
        return 0;
    }
};