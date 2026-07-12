#include <iostream>
#include <string_view>
#include <string>

void printInfo(std::string_view sv) {
    std::cout << sv << " (len " << sv.size() << ")\n";
}

std::string_view makeView() {
    std::string local = "abc";
    return local;         
}

int main() {
    // std::string owned = "hello";
    // printInfo(owned);
    // printInfo("literal");

    // std::string_view sv = "hello world";
    // std::cout << sv.substr(0, 5) << '\n';        // "hello" — a sub-view, still no copy
    // std::cout << sv.starts_with("hello") << '\n'; // 1

    std::string_view sv = std::string_view("hello world").substr(0, 5);  // views "hello", but
                                                                      // the buffer continues " world"
    std::printf("%s\n", sv.data());   // ✗ WRONG: prints "hello world" (or more) —
                                        //   printf reads until \0, ignoring sv's len=5

    std::string_view svv = makeView();
    for (std::size_t i = 0; i < svv.size(); ++i) {
        std::cout << svv[i] << '\n';
    }

    return 0;
}