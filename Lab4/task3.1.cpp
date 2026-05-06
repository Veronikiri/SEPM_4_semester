#include <iostream>
#include <array>
#include <tuple>
#include <utility>

template <size_t LinearIndex, typename... Arrays>
constexpr auto get_cartesian_element(const Arrays&... arrays) {
    constexpr size_t total_dims = sizeof...(Arrays);
    size_t remaining = LinearIndex;
    
    size_t indices[total_dims] = {};
    size_t sizes[] = { arrays.size()... };
    
    for (int i = static_cast<int>(total_dims) - 1; i >= 0; --i) {
        indices[i] = remaining % sizes[i];
        remaining /= sizes[i];
    }

    return [=, &arrays...]<size_t... I>(std::index_sequence<I...>) {
        return std::make_tuple(arrays[indices[I]]...);
    }(std::make_index_sequence<total_dims>{});
}

template <typename... Arrays>
struct CartesianProduct {
    using ElementType = std::tuple<typename Arrays::value_type...>;
    static constexpr size_t total_size = (Arrays{}.size() * ...);
    using Type = std::array<ElementType, total_size>;

    static constexpr Type compute(const Arrays&... arrays) {
        return []<size_t... Is>(const Arrays&... arrs, std::index_sequence<Is...>) {
            return Type{ get_cartesian_element<Is>(arrs...)... };
        }(arrays..., std::make_index_sequence<total_size>{});
    }
};

template <typename... Arrays>
constexpr auto make_cartesian_product(const Arrays&... arrays) {
    return CartesianProduct<Arrays...>::compute(arrays...);
}

int main() {
    constexpr std::array<int, 2> arr1 = {1, 2};
    constexpr std::array<char, 3> arr2 = {'a', 'b', 'c'};

    constexpr auto result = make_cartesian_product(arr1, arr2);

    std::cout << "Cartesian Product size: " << result.size() << "\nElements:\n";
    for (const auto& t : result) {
        std::cout << "( " << std::get<0>(t) << ", " << std::get<1>(t) << " )\n";
    }

    return 0;
}