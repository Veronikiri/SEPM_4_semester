#include <iostream>

int main() {
    int k = 2097152;
    int n = k + 100;
    
    float forward_sum = 0.0;
    for (int i = 1; i <= n; i = i + 1) {forward_sum = forward_sum + (1.0 / i);}
    
    float backward_sum = 0.0;
    for (int i = n; i >= 1; i = i - 1) {backward_sum = backward_sum + (1.0 / i);}
    
    std::cout << "Forward sum to k+100: " << forward_sum << std::endl;
    std::cout << "Backward sum to k+100: " << backward_sum << std::endl;
    
    return 0;
}
