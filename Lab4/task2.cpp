#include <iostream>
#include <tuple>
#include <string>

template <size_t k, typename... Args>
struct TupleProcessor {
    static void process(const std::tuple<Args...>& t, auto& op) {
        if constexpr (k < sizeof...(Args)) {
            op(std::get<k>(t));
            TupleProcessor<k + 1, Args...>::process(t, op);
        }
    }
};

template <typename... Args, typename UnaryOperation>
void apply_to_all(const std::tuple<Args...>& t, UnaryOperation op) {
    TupleProcessor<0, Args...>::process(t, op);
}

int main() {
    auto my_tuple = std::make_tuple(42, 3.14, std::string("MIPT"), '!');

    auto print_op = [](const auto& x) {
        std::cout << x << " ";
    };

    std::cout << "Result: ";
    apply_to_all(my_tuple, print_op);
    std::cout << std::endl;

    return 0;
}
