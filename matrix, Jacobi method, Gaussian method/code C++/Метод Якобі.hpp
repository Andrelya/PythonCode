#ifndef ____________hpp
#define ____________hpp

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>

using namespace std;

typedef double calc_type;

template<typename T>
class Matrix1 {
public:
    T *matrix_pointer = nullptr;
    int n = 0;
    int m = 0;

    Matrix1() = default;

    Matrix1(int n, int m) : matrix_pointer(new T[n * m]), n(n), m(m) {
        fill_with_zeros();
    }

    void fill_with_zeros() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                at(i, j) = T();
            }
        }
    }

    bool is_diagonal(double eps) const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i != j && fabs(at(i, j)) >= eps) {
                    return false;
                }
            }
        }
        return true;
    }

    vector<calc_type> get_line(int line_index) const {
        vector<calc_type> ret(m, calc_type());
        for (int j = 0; j < m; ++j) {
            ret[j] = at(line_index, j);
        }
        return ret;
    }

    vector<calc_type> get_column(int column_index) const {
        vector<calc_type> ret(n, calc_type());
        for (int i = 0; i < n; ++i) {
            ret[i] = at(i, column_index);
        }
        return ret;
    }

    T &at(int i, int j) {
        return matrix_pointer[i * m + j];
    }

    T at(int i, int j) const {
        return matrix_pointer[i * m + j];
    }
};

void random_matrix(int rozmirnist, int chysla);
void print_input();

#endif /* ____________hpp */
