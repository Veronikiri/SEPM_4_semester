#include <iostream>

int main() {
    float a = 1.0;
    float b = 1.0 + 1.1920929e-7;
    
    if (a == b) {
        std::cout << "a == b (after arithmetic): equal" << std::endl;
    } else {
        std::cout << "a == b (after arithmetic): not equal" << std::endl;
    }
    
    float x = 1.0;
    float y = 1.0;
    if (x == y) {
        std::cout << "x == y (no arithmetic): equal" << std::endl;
    } else {
        std::cout << "x == y (no arithmetic): not equal" << std::endl;
    }
    
    return 0;
}
