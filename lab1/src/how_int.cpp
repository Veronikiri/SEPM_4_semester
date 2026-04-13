#include <iostream>

int main() {
    int number;   
    std::cout << "число: ";
    std::cin >> number;   
    std::cout << "Биты" << number << ": ";
    
    for (int i = 31; i >= 0; i--) {
       
        int mask = 1 << i;
        
        if (number & mask) {std::cout << "1";}
        else {std::cout << "0";}
        
        if (i % 8 == 0 && i != 0) {std::cout << " ";}
    }
    
    std::cout << std::endl;
    return 0;
}
