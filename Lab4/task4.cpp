#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <iterator>

template<typename Iterator>
void check_sort_compatibility() {
    using Category = typename std::iterator_traits<Iterator>::iterator_category;

    static_assert(std::is_base_of_v<std::random_access_iterator_tag, Category>,
        "ERROR");
}

template<typename Iterator, typename Compare>
void sort_with_interface(Iterator first, Iterator last, Compare comp) {
    check_sort_compatibility<Iterator>();
    std::cout << "All right!" << std::endl;
}

template<typename T, typename = void>
struct has_push_back : std::false_type {};

template<typename T>
struct has_push_back<T, std::void_t<decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))>>
    : std::true_type {};

template<typename Container>
struct MyStackAdapter {
    static_assert(has_push_back<Container>::value,
        "ERROR!");
    Container c;
};

int main() {

    std::vector<int> v = {3, 1, 2};
    sort_with_interface(v.begin(), v.end(), std::less<int>());
    MyStackAdapter<std::vector<int>> good_stack;

    std::cout << "Good!" << std::endl;

    return 0;
}

