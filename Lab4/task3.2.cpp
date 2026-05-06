#include <iostream>
#include <utility>

template <int... Coeffs>
struct LinearSequence {
    template <int... Inits>
    struct WithInits {
        template <size_t K>
        static constexpr int get() {
            constexpr int init[] = {Inits...};
            constexpr size_t N = sizeof...(Coeffs);
            
            if constexpr (K < N) {
                return init[K];
            } else {
                return calculate<K>(std::make_index_sequence<N>{});
            }
        }
        
    private:
        template <size_t K, size_t... I>
        static constexpr int calculate(std::index_sequence<I...>) {
            constexpr int a[] = {Coeffs...};
            constexpr size_t N = sizeof...(Coeffs);
            return ((a[I] * WithInits::get<K - N + I>()) + ...);
        }
    };
};

int main() {
    using Fibonacci = LinearSequence<1, 1>::WithInits<0, 1>;
    using MyRec = LinearSequence<2, 0, 3>::WithInits<1, 1, 1>;
    
    std::cout << "Fib(10) = " << Fibonacci::get<10>() << std::endl;
    std::cout << "MyRec(5) = " << MyRec::get<5>() << std::endl;
    
    return 0;
}