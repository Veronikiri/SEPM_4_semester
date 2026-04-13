template<typename T>
class Subvector {
private:
    T* mas;
    unsigned int top;
    unsigned int capacity;

public:
    Subvector() : mas(nullptr), top(0), capacity(0) {}
    explicit Subvector(unsigned int n) : capacity(n), top(0) {
        mas = new T[n];
    }
    ~Subvector() {
        delete[] mas;
    }
    Subvector(const Subvector& other) : top(other.top), capacity(other.capacity) {
        mas = new T[capacity];
        for (unsigned int i = 0; i < top; ++i) {
            mas[i] = other.mas[i];
        }
    }
    Subvector(Subvector&& other) : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }
    Subvector& operator=(const Subvector& other) {
        if (this != &other) {
            delete[] mas;
            capacity = other.capacity;
            top = other.top;
            mas = new T[capacity];
            for (unsigned int i = 0; i < top; ++i) {
                mas[i] = other.mas[i];
            }
        }
        return *this;
    }
    Subvector& operator=(Subvector&& other) {
        if (this != &other) {
            delete[] mas;
            mas = other.mas;
            top = other.top;
            capacity = other.capacity;
            other.mas = nullptr;
            other.top = 0;
            other.capacity = 0;
        }
        return *this;
    }
    bool push_back(const T& d) {
        if (top == capacity) {
            unsigned int new_cap = (capacity == 0) ? 1 : capacity * 2;
            T* new_mas = new T[new_cap];
            for (unsigned int i = 0; i < top; ++i) {
                new_mas[i] = mas[i];
            }
            delete[] mas;
            mas = new_mas;
            capacity = new_cap;
        }
        mas[top++] = d;
        return true;
    }
    T pop_back() {
        if (top == 0) return T{};
        return mas[--top];
    }
    bool resize(unsigned int new_capacity) {
        if (new_capacity == capacity) return true;
        T* new_mas = new T[new_capacity];
        unsigned int copy_size = (top < new_capacity) ? top : new_capacity;
        for (unsigned int i = 0; i < copy_size; ++i) {
            new_mas[i] = mas[i];
        }
        delete[] mas;
        mas = new_mas;
        capacity = new_capacity;
        top = copy_size;
        return true;
    }
    void shrink_to_fit() {
        if (top == capacity) return;
        if (top == 0) {
            delete[] mas;
            mas = nullptr;
            capacity = 0;
            return;
        }
        T* new_mas = new T[top];
        for (unsigned int i = 0; i < top; ++i) {
            new_mas[i] = mas[i];
        }
        delete[] mas;
        mas = new_mas;
        capacity = top;
    }
    void clear() {
        top = 0;
    }
    T& operator[](unsigned int index) {
        return mas[index];
    }
    const T& operator[](unsigned int index) const {
        return mas[index];
    }
    unsigned int size() const { return top; }
    unsigned int get_capacity() const { return capacity; }
};
