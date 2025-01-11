#include <iostream>

int t() noexcept {
    return 1;
}

int main() {
    std::cout << t() << std::endl;
}
