#include <iostream>
#include <memory>

struct Node {
    int id;
    std::shared_ptr<Node> other;   // ← the cyclic link
    // std::weak_ptr<Node> other;   // ← changed shared_ptr to weak_ptr
    Node(int i) : id(i) { std::cout << "construct " << id << '\n'; }
    ~Node() { std::cout << "destruct " << id << '\n'; }
};

int main() {
    {
        auto a = std::make_shared<Node>(1);
        auto b = std::make_shared<Node>(2);
        a->other = b;   // a points to b  → b's strong count = 2
        b->other = a;   // b points to a  → a's strong count = 2
    }   // scope ends: a and b (the locals) are destroyed → each strong count drops 2→1
        // but a still has count 1 (from b->other), b has count 1 (from a->other)
        // NEITHER reaches 0 → NEITHER destructor runs → LEAK
    std::cout << "scope ended\n";
    // you will see NO "destruct" lines before "scope ended" — that's the leak
}