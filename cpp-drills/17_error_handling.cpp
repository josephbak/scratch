#include <iostream>
#include <optional>

// Error-handling ladder (LLVM/MLIR, -fno-exceptions — errors are return values):
//   std::optional<T> : value OR nothing      (no value → no reason given)
//   LogicalResult    : success OR failure    (status only, carries NO value)
//   Expected<T>      : value OR an error      (failure carries WHY — an error object)
// Pick by: need a value? no → LogicalResult. yes → reason on failure? no → optional, yes → Expected.

class LogicalResult {
    bool ok_;

public:
    LogicalResult(bool b) : ok_(b) {}
    bool get_ok() const {
        return ok_;
    }
};

LogicalResult success() { return LogicalResult(true);}
LogicalResult failure() { return LogicalResult(false); }

bool succeeded(LogicalResult r) { return r.get_ok(); }
bool failed(LogicalResult r) { return !r.get_ok(); }

LogicalResult doStep(int x) {
    return x > 0 ? success() : failure();
}

std::optional<int> parsePositive(int x) {
    return x > 0 ? std::optional<int>(x) : std::nullopt;
}

int main() {
    if (auto v = parsePositive(5)) { std::cout << "got: " << *v << '\n'; } // *v -> the int
    int y = parsePositive(-1).value_or(0);
    std::cout << "y = " << y << '\n';            // 0 (fallback)

    std::cout << "=====================================" << '\n';

    for (int x : {5, -1}) {
    if (failed(doStep(x)))
        std::cout << x << ": failed\n";
    else
        std::cout << x << ": succeeded\n";
    }

    return 0;
}