#include <iostream>

constexpr int square(const int i) { return i * i; }

int main() {
    int i2 {7};
    const int i3 {10};
    
    constexpr int i4 {square(i3)};
}