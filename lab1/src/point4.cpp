#include <iostream>

int main() {
    float sum = 0.0;
    int k = 1;
    float old_sum = 0.0;
    
    while (true) {
        old_sum = sum;
        sum = sum + (1.0 / k);
        if (sum == old_sum) {
            std::cout << "First k where add 1/k no change: " << k << std::endl;
            break;
        }
        k = k + 1;
    }
    
    return 0;
}
