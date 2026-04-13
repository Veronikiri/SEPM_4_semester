#include <iostream>
#include <bitset>

int main() {
    float x;
    std::cout << "число float: ";
    std::cin >> x;

    unsigned int bits = *(unsigned int*)&x;

    std::bitset<32> binary(bits);
    std::cout << "Двоичное представление: " << binary << std::endl;

    std::cout << "Знак : " << binary[31] << std::endl;
    std::cout << "Экспонента : " 
              << binary.to_string().substr(1, 8) << std::endl;
    std::cout << "Мантисса : " 
              << binary.to_string().substr(9, 23) << std::endl;

    return 0;
}

}
