#include <iostream>

void showBits(int value) {
    for (int i = 31; i >= 0; i--) {
        int mask = 1 << i;
        std::cout << ((value & mask) ? '1' : '0');
        if (i % 8 == 0 && i != 0) std::cout << " ";
    }
}

int main() {
    int num_int;
    unsigned int num_uint;
    
    std::cout << "число для int: ";
    std::cin >> num_int;
    
    std::cout << "число для unsigned int: ";
    std::cin >> num_uint;
    
    std::cout << "\nРезультаты:" << std::endl;
    std::cout << "int:         ";
    showBits(num_int);
    std::cout << " = " << num_int << std::endl;
    
    std::cout << "unsigned int: ";
    showBits(num_uint);
    std::cout << " = " << num_uint << std::endl;
    
    return 0;
}
