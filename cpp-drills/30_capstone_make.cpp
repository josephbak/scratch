#include <iostream>
#include <string>

struct Widget {
    Widget(int a, const std::string& b) { std::cout << "Widget(" << a << ", " << b << ")\n"; }
};

template <typename T, typename... Args>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

int main() {

    std::string name = "iree";
    int x = 42;

    // V1 baseline:            both mix — rvalue int, lvalue string
    make<Widget>(42, name);
    // Args...   = (int, std::string&)
    // Args&&... = (int&&, std::string&)
    // forward   = std::forward<int>(42), std::forward<std::string&>(name)
    // stolen?   = none

    // V2 flip categories:     lvalue int, rvalue string
    make<Widget>(x, std::string("tmp"));
    // Args...   = (int&, std::string)
    // Args&&... = (int&, std::string&&)
    // forward   = std::forward<int&>(x), std::forward<std::string>("tmp")
    // stolen?   = none

    // V3 explicit move:       does name get STOLEN here?
    make<Widget>(x, std::move(name));
    // Args...   = (int&, std::string)
    // Args&&... = (int&, std::string&&)
    // forward   = std::forward<int&>(x), std::forward<std::string>()
    // stolen?   = none

    // V4 both lvalues:        nothing should be stealable
    make<Widget>(x, name);
    // Args...   = (int&, std::string&)
    // Args&&... = (int&, std::string&)
    // forward   = std::forward<int&>(x), std::forward<std::string&>(name)
    // stolen?   = none

    // V5 both rvalues:        literal + temporary
    make<Widget>(7, std::string("z"));
    // Args...   = (int, std::string)
    // Args&&... = (int&&, std::string&&)
    // forward   = std::forward<int>(7), std::forward<std::string>("z")
    // stolen?   = none



    // std::string name = "iree";
    // make<Widget>(42, name);


    // T          = Widget (expliicit)
    // Args...    = (int, std::string&) (rvalue, lvalue) (deduced)
    /*
    42    : rvalue → Args = int          → param int&&              → args slot binds rvalue
    name  : lvalue → Args = std::string& → param std::string& && → std::string&  → binds lvalue 
    */
    // Args&&...  = (42, name) (rvalue, lvalue)
    // forward<Args>(args)...  expands to → td::forward<int>(42),  std::forward<std::string&>(name)
    //   → literal expansion of the pack + forward


    /*
    T          = Widget                              (explicit pin — rung 26)
    Args...    = (int, std::string&)                 (TYPES; & injected on the lvalue — rung 28)
    Args&&...  = (int&&, std::string&)               (after collapse: rvalue-ref, lvalue-ref)
    forward…   = forward<int>(42), forward<std::string&>(name)
                → (rvalue, lvalue) → Widget(int, const std::string&): 42 bound, name COPIED intact
    */

    return 0;
}