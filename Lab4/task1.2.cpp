#include <iostream>
#include <deque>
#include <vector>
#include <string>

template <typename T, typename Container = std::deque<T>>
class MyStack {
protected:
    Container c;

public:
    void push(const T& val) { c.push_back(val); }
    void pop() { if (!c.empty()) c.pop_back(); }

    T& top() { return c.back(); }
    const T& top() const { return c.back(); }

    size_t size() const { return c.size(); }
    bool empty() const { return c.empty(); }
};

template <>
class MyStack<char, std::string> {
private:
    std::string c;

public:
    void push(char val) { c.push_back(val); }
    void pop() { if (!c.empty()) c.pop_back(); }

    char& top() { return c.back(); }
    const char& top() const { return c.back(); }

    size_t size() const { return c.size(); }
    bool empty() const { return c.empty(); }
};

int main() {
    MyStack<int> s_int;
    s_int.push(10);

    MyStack<double, std::vector<double>> s_vec;
    s_vec.push(3.14);

    MyStack<char, std::string> s_str;
    s_str.push('F');
    s_str.push('P');

    std::cout << "Top: " << s_str.top() << ", Size: " << s_str.size() << std::endl;

    return 0;
}