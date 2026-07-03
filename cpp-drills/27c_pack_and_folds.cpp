#include <iostream>

/*
pack args = (1, 2, 3)      op = +      init = 100

EXPANSION (not a fold — just repeats a pattern, comma-separated):
  args...              → 1, 2, 3
  f(args)...           → f(1), f(2), f(3)

FOLDS (insert op between elements → ONE result):
  ┌─────────────────────┬──────────────────────────┬────────┬──────────────┐
  │ form                │ literal expansion        │ result │ empty pack   │
  ├─────────────────────┼──────────────────────────┼────────┼──────────────┤
  │ (args + ...)        │ 1 + (2 + 3)              │  6     │ ERROR        │  unary right
  │ (... + args)        │ (1 + 2) + 3              │  6     │ ERROR        │  unary left
  │ (args + ... + 100)  │ 1 + (2 + (3 + 100))      │ 106    │ 100 (init)   │  binary right
  │ (100 + ... + args)  │ ((100 + 1) + 2) + 3      │ 106    │ 100 (init)   │  binary left
  └─────────────────────┴──────────────────────────┴────────┴──────────────┘

DIRECTION rule:  side the `...` sits on  →  which end groups first
  ... on RIGHT of pack → RIGHT fold → groups right-to-left → init is INNERMOST
  ... on LEFT  of pack → LEFT  fold → groups left-to-right → init is OUTERMOST

EMPTY-PACK rule:  unary fold legal ONLY for && (→true), || (→false), , (→void)
                  everything else needs BINARY form (init = the empty fallback)
*/

template<typename... Ts>
auto subURight(Ts... args){
// → (args - ...)          unary  right
// 10 - (3 - 2) = 9
// the right end
    return (args - ...);
}

template<typename... Ts>
auto subULeft(Ts... args){
// (... - args)          unary  left
// (10-3) - 2 = 5
// the left end
    return (... - args);
}

template<typename... Ts>
auto subBRight(Ts... args){
//→ (args - ... - 0)      binary right   (init = 0)
// 10 - (3 - (2 - 0)) = 9
// right end
    return (args - ... - 0);
}

template<typename... Ts>
auto subBLeft(Ts... args) {
// → (0 - ... - args)      binary left    (init = 0)
// (((0 - 10) - 3) - 2) = -15
// left end
    return (0 - ... - args);
}

/*
subURight()  →  error   (unary  - , empty)
subULeft()   →  error   (unary  - , empty)
subBRight()  →  0   (binary - , empty → 0)
subBLeft()   →  0   (binary - , empty → 0)
printSpaced()→  ?   (unary comma, empty)
*/

template <typename... Ts>
void printSpaced(Ts... args) {
    ((std::cout << args << ' '), ...);   // unary right fold over comma
    std::cout << '\n';

    // (std::cout << 10 << ' ', (std::cout << 3 << ' ', std::cout << 2 << ' '))
}

int main() {
//    auto ur = subURight(10, 3, 2);
//    auto ul = subULeft(10, 3, 2);
//    auto br = subBRight(10, 3, 2);
//    auto bl = subBLeft(10, 3, 2);
    
//     std::cout << ur << '\n';
//     std::cout << ul << '\n';
//     std::cout << br << '\n';
//     std::cout << bl << '\n';

    // std::cout << subURight() << '\n';
    // std::cout << subULeft() << '\n';
    // std::cout << subBRight() << '\n';
    // std::cout << subBLeft() << '\n';

    // printSpaced(10, 3, 2);
    printSpaced();

    
    return 0;
}