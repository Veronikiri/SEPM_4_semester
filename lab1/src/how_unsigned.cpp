#include <iostream>

int main() {
    unsigned int number;   
    std::cout << "положительное число: ";
    std::cin >> number;    
    std::cout << "Биты " << number << ": ";
    
    for (int i = 31; i >= 0; i--) {unsigned int mask = 1u << i;

        if (number & mask) {std::cout << "1";} 
        else {std::cout << "0";}
        
        if (i % 8 == 0 && i != 0) {std::cout << " ";}
    }
    
    std::cout << std::endl;
    return 0;
}
