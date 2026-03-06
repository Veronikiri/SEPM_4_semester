#include <iostream>

int main() {
    float a = 1.0;
    float b = -1.0;
    float c = 1.1920929e-7;
    
    float left = (a + b) + c;
    float right = a + (b + c);
    
    std::cout << "(a + b) + c = " << left << std::endl;
    std::cout << "a + (b + c) = " << right << std::endl;
    
    if (left != right) {
        std::cout << "Not equal!" << std::endl;
    }
    
    return 0;
}
