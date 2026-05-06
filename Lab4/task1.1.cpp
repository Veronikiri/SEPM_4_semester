#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <cstdlib>
#include <ctime>

template <typename RandomAccessIterator, typename Compare>
void my_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    if (std::distance(first, last) <= 1) return;

    auto pivot = *std::next(first, std::distance(first, last) / 2);
    RandomAccessIterator i = first;
    RandomAccessIterator j = last - 1;

    while (i <= j) {
        while (comp(*i, pivot)) i++;
        while (comp(pivot, *j)) j--;

        if (i <= j) {
            std::iter_swap(i, j);
            i++;
            j--;
        }
    }
    if (first < j) my_sort(first, j + 1, comp);
    if (i < last) my_sort(i, last, comp);
}

inline bool compare_func(int a, int b) {
    return a < b;
}

struct LessThan {
    bool operator()(int a, int b) const { return a < b; }
};

void run_benchmarks() {
    const int N = 50000;
    std::vector<int> v(N);
    std::deque<int> d(N);

    for(int i = 0; i < N; ++i) {
        int val = rand();
        v[i] = d[i] = val;
    }

    auto start_v = std::chrono::high_resolution_clock::now();
    my_sort(v.begin(), v.end(), std::less<int>());
    auto end_v = std::chrono::high_resolution_clock::now();

    auto start_d = std::chrono::high_resolution_clock::now();
    my_sort(d.begin(), d.end(), std::less<int>());
    auto end_d = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff_v = end_v - start_v;
    std::chrono::duration<double> diff_d = end_d - start_d;

    std::cout << "Vector: " << diff_v.count() << "s\n";
    std::cout << "Deque:  " << diff_d.count() << "s\n";
}

int main() {
    srand(time(0));
    
    std::vector<int> v(10);
    for(int i = 0; i < 10; i++) {
        v[i] = rand() % 100;
    }
    
    std::cout << "Vector before: ";
    for(int x : v) std::cout << x << " ";
    std::cout << std::endl;
    
    my_sort(v.begin(), v.end(), compare_func);
    
    std::cout << "Vector after (function): ";
    for(int x : v) std::cout << x << " ";
    std::cout << std::endl;
    
    std::vector<int> v2(10);
    for(int i = 0; i < 10; i++) {
        v2[i] = rand() % 100;
    }
    
    std::cout << "Vector before: ";
    for(int x : v2) std::cout << x << " ";
    std::cout << std::endl;
    
    my_sort(v2.begin(), v2.end(), LessThan());
    
    std::cout << "Vector after (functor): ";
    for(int x : v2) std::cout << x << " ";
    std::cout << std::endl;
    
    std::vector<int> v3(10);
    for(int i = 0; i < 10; i++) {
        v3[i] = rand() % 100;
    }
    
    std::cout << "Vector before: ";
    for(int x : v3) std::cout << x << " ";
    std::cout << std::endl;
    
    my_sort(v3.begin(), v3.end(), [](int a, int b) { return a < b; });
    
    std::cout << "Vector after (lambda): ";
    for(int x : v3) std::cout << x << " ";
    std::cout << std::endl << std::endl;
    
    std::deque<int> d(10);
    for(int i = 0; i < 10; i++) {
        d[i] = rand() % 100;
    }
    
    std::cout << "Deque before: ";
    for(int x : d) std::cout << x << " ";
    std::cout << std::endl;
    
    my_sort(d.begin(), d.end(), compare_func);
    
    std::cout << "Deque after: ";
    for(int x : d) std::cout << x << " ";
    std::cout << std::endl << std::endl;
    
    run_benchmarks();
    
    return 0;
}
