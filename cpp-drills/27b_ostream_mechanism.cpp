#include <iostream>
#include <string>

class MyStream {
public:
    std::string buffer;
    MyStream& operator<<(int x) {
        buffer += std::to_string(x);
        return *this;
    }
};

MyStream& operator<<(MyStream& os, const char* s) {
    os.buffer += s;
    return os;
}

int main() {
    // desugared: ((out.operator<<(1)) via free op<<(_, "hi")) .operator<<(2)
    //   out.operator<<(1)        MEMBER → returns out&, buffer="1"
    //   operator<<(out&, "hi")   FREE   → returns out&, buffer="1hi"
    //   (out&).operator<<(2)     MEMBER → returns out&, buffer="1hi2"
    MyStream out;
    out << 1 << "hi" << 2;
    //1hi2
    std::cout << out.buffer << '\n';

    return 0;
}