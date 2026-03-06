#include <iostream>

int main() {
    float a = 1.0;
    float b = a;
    float one = 1.0;
    
    while (b - a != one) {
        a = b;
        b = b + one;
    }
    
    std::cout << "First a where next - a == 1: " << a << std::endl;
    std::cout << "First b: " << b << std::endl;
    
    float x = b;
    float x_plus_one = x + one;
    while (x != x_plus_one) {
        x = x_plus_one;
        x_plus_one = x + one;
    }
    
    std::cout << "Last x where x+1 != x: " << x << std::endl;
    std::cout << "x0: " << x_plus_one << std::endl;
    
    return 0;
}
