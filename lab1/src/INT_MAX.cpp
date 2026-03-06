#include <iostream>
#include <climits>  

int main() {
    int a = INT_MAX;
    std::cout << "INT_MAX = " << a << std::endl;
    a = a + 1;
    std::cout << "INT_MAX + 1 = " << a << std::endl;

    return 0;
}
