#include <iostream>
#include <utility>

/*
std::forward<T>(x)  ≡  static_cast<T&&>(x)   → then reference-collapse (SAME rule as Rung 28)
    T = U&  → static_cast<U&>  → LVALUE out  → copy path
    T = U   → static_cast<U&&> → RVALUE out  → move path
  <T> explicit & mandatory: carries the deduced category.

move ≡ static_cast<U&&>  : UNCONDITIONAL → "I'm done with x, give it up"
fwd  ≡ static_cast<T&&>  : CONDITIONAL   → "relay x as the caller gave it"
bare x (named)           : ALWAYS lvalue expression → THE TRAP

WHY: named param x is an lvalue even when its TYPE is U&& → relaying x drops rvalue-ness
     → wrong overload (copy) fires → move + noexcept fast-path lost
FIX: relay a T&& (fwd-ref) param via  std::forward<T>(x)
*/

// void sink(const std::string& s) { std::cout << "COPY sink (const U&)\n"; }
void sink(std::string& s) { std::cout << "COPY sink (const U&)\n"; }
void sink(std::string&& s)      { std::cout << "MOVE sink (U&&)\n"; }

template <typename T> void relayBad(T&& x)  { sink(x); }                    // passes named x
template <typename T> void relayGood(T&& x) { sink(std::forward<T>(x)); }   // forwards

int main() {
    std::string s = "hi";

    relayBad(s);
    // lvalue -> T = U& -> x named -> copy sink
    relayBad(std::string("tmp"));
    // rvalue -> T = U -> x named -> copy sink
    std::cout << "=====================================\n";

    relayGood(s);
    // lvalue -> T = U& -> fowarward yields lvalue -> copy sink
    relayGood(std::string("tmp"));
    // rvalue -> T = U -> forward yields rvalue -> move sink
    return 0;
}