#include <iostream>
#include <cassert>
#include <cmath>
#include <random>

template<typename T>
class Subvector {
private:
    T* mas;
    unsigned int top;
    unsigned int capacity;
public:
    Subvector() : mas(nullptr), top(0), capacity(0) {}
    explicit Subvector(unsigned int n) : capacity(n), top(n) {
        mas = new T[n]();
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
    T& operator[](unsigned int index) {
        return mas[index];
    }
    const T& operator[](unsigned int index) const {
        return mas[index];
    }
    unsigned int size() const { return top; }
    unsigned int get_capacity() const { return capacity; }
};

template<typename T>
class Matrix {
    Subvector<T> data;
    unsigned rows_count;
    unsigned cols_count;

public:
    Matrix(unsigned rows, unsigned cols, const T& value = T{})
        : rows_count(rows), cols_count(cols), data(rows * cols)
    {
        for (unsigned i = 0; i < rows * cols; i++)
            data[i] = value;
    }

    static Matrix Identity(unsigned rows, unsigned cols) {
        Matrix I(rows, cols, T{});
        unsigned min_dim = (rows < cols) ? rows : cols;
        for (unsigned i = 0; i < min_dim; i++)
            I(i, i) = 1;
        return I;
    }

    static Matrix getSpecificDeterminant(unsigned n, T det) {
        Matrix A = Identity(n, n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.1, 2.0);

        if (n == 1) {
            A(0, 0) = det;
        } else {
            T product = 1.0;
            for (unsigned i = 0; i < n; ++i) {
                T value = (i == 0) ? det / product : dis(gen);
                A(i, i) = value;
                product *= value;
            }
            if (std::abs(product - det) > 1e-6) {
                A(n-1, n-1) = det / product * A(n-1, n-1);
            }
        }
        return A;
    }

    unsigned rows() const { return rows_count; }
    unsigned cols() const { return cols_count; }

    Matrix& transpose() {
        Matrix temp(cols_count, rows_count);
        for (unsigned r = 0; r < rows_count; r++)
            for (unsigned c = 0; c < cols_count; c++)
                temp(c, r) = (*this)(r, c);
        *this = temp;
        return *this;
    }

    Matrix transpose() const {
        Matrix R(cols_count, rows_count);
        for (unsigned r = 0; r < rows_count; r++)
            for (unsigned c = 0; c < cols_count; c++)
                R(c, r) = (*this)(r, c);
        return R;
    }

    T& operator()(unsigned row, unsigned col) {
        assert(row < rows_count && col < cols_count);
        return data[row * cols_count + col];
    }

    T operator()(unsigned row, unsigned col) const {
        assert(row < rows_count && col < cols_count);
        return data[row * cols_count + col];
    }
};

template<typename T>
T determinant(const Matrix<T>& A)
{
    assert(A.rows() == A.cols());
    unsigned n = A.rows();
    Matrix<T> temp = A;
    T det = 1;
    for (unsigned i = 0; i < n; i++) {
        unsigned pivot = i;
        while (pivot < n && std::abs(temp(pivot, i)) < 1e-12)
            pivot++;
        if (pivot == n)
            return T{};
        if (pivot != i) {
            for (unsigned c = 0; c < n; c++)
                std::swap(temp(i, c), temp(pivot, c));
            det = -det;
        }
        det *= temp(i, i);
        T diag = temp(i, i);
        for (unsigned r = i + 1; r < n; r++) {
            T k = temp(r, i) / diag;
            for (unsigned c = i; c < n; c++)
                temp(r, c) -= k * temp(i, c);
        }
    }
    return det;
}

void test(unsigned n, double det_value) {
    Matrix<double> A = Matrix<double>::getSpecificDeterminant(n, det_value);
    Matrix<double> AT = A.transpose();
    double d1 = determinant(A);
    double d2 = determinant(AT);
    std::cout << "Matrix " << n << "x" << n
              << " det(A)=" << d1
              << " det(A^T)=" << d2
              << std::endl;
}

int main() {
    Matrix<double> m1(10, 10);
    test(5, 7.0);
    test(50, 3.0);
    test(200, 2.0);
    return 0;
}
