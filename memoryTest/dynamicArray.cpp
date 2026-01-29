#include <iostream>
#include <vector>

struct Numbers {
    std::vector<int> items;
};

int main() {
    Numbers xs;
    xs.items.reserve(256);

    for (int x = 0; x < 10; ++x) {
        xs.items.push_back(x);
    }

    for (int v : xs.items) {
        std::cout << v << '\n';
    }
}
