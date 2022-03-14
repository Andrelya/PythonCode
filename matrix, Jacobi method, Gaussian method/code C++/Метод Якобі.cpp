#include "Метод Якобі.hpp"

pair<int, int> chose_i_and_j(const Matrix1<calc_type> &matrix, int n, int previous_i, int previous_j,
                                  double eps) {
    int chosen_j = 1;
    int chosen_i = 0;
    
        calc_type max = -1.;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && fabs(matrix.at(i, j)) > max) {
                    max = fabs(matrix.at(i, j));
                    chosen_i = i;
                    chosen_j = j;
                }
            }
        }
    while(chosen_i == chosen_j || fabs(matrix.at(chosen_i, chosen_j)) < eps);
    
    return pair<int, int>(chosen_i, chosen_j);
}

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


std::vector<calc_type > jacobi_eigenvalue_algorithm(Matrix1<calc_type> &matrix, Matrix1<calc_type> &eigenvectors, int n,
                                                     double eps) {
    
    int prev_i = -1, prev_j = -1;
    while (!matrix.is_diagonal(eps)) {
        //cout << "qqqqq" << endl;
        pair<int, int> temp = chose_i_and_j(matrix, n, prev_i, prev_j, eps);
        int chosen_i = temp.first;
        int chosen_j = temp.second;

        calc_type cos, sin;
        calc_type x = -2*matrix.at(chosen_i, chosen_j);
        calc_type y = matrix.at(chosen_i, chosen_i) - matrix.at(chosen_j, chosen_j);
        if (fabs(y) < eps) {
            cos = sin = 1./sqrt(2);
        } else {
            cos = sqrt(1./2 + fabs(y)/(2*sqrt(x*x + y*y)));
            sin = sgn(x*y)*fabs(x)/(2*cos*sqrt(x*x + y*y));
        }

        vector<calc_type> line_i = matrix.get_line(chosen_i);
        vector<calc_type> line_j = matrix.get_line(chosen_j);
        for (int j = 0; j < n; ++j) {
            matrix.at(chosen_i, j) = line_i[j]*cos - line_j[j]*sin;
            matrix.at(chosen_j, j) = line_i[j]*sin + line_j[j]*cos;
        }

        vector<calc_type> column_i = matrix.get_column(chosen_i);
        vector<calc_type> column_j = matrix.get_column(chosen_j);
        for (int i = 0; i < n; ++i) {
            matrix.at(i, chosen_i) = column_i[i]*cos - column_j[i]*sin;
            matrix.at(i, chosen_j) = column_i[i]*sin + column_j[i]*cos;
        }

        vector<calc_type> eigenvector_column_i = eigenvectors.get_column(chosen_i);
        vector<calc_type> eigenvector_column_j = eigenvectors.get_column(chosen_j);
        for (int i = 0; i < n; ++i) {
            eigenvectors.at(i, chosen_i) = eigenvector_column_i[i]*cos - eigenvector_column_j[i]*sin;
            eigenvectors.at(i, chosen_j) = eigenvector_column_i[i]*sin + eigenvector_column_j[i]*cos;
        }

        prev_i = chosen_i;
        prev_j = chosen_j;
        
    }
    vector<calc_type> ret(n, calc_type(0));
    int i = 0;
    for (auto &it : ret) {
        it = matrix.at(i, i);
        i++;
    }
    return ret;
}

void print_eigenvalues(const vector<calc_type> &eigenvalues) {
    cout << "Власні числа: " << std::endl;
    int i = 1;
    for (auto &it : eigenvalues) {
        std::cout << "λ" << i++ << ": " << it << endl;
    }
}

void print_eigenvectors(const Matrix1<calc_type> &eigenvectors, int n) {
    cout << "\nВласні вектора:" << endl;
    for (int j = 0; j < n; ++j) {
        cout << "X" << j + 1 << ": ";
        for (int i = 0; i < n; ++i) {
            cout << eigenvectors.at(i, j) << " ";
        }
        cout << endl;
    }
    
}

void output_matrix(Matrix1<calc_type> matrix, int n){
    /*
       виводить на екран матрицю
     */
    
    int max = 0;
    int s;
    vector<int> vect;
    
    for (int i = 0; i != n; i++){    // шукаєм найдовше число в кожному стовпці
        for (int j = 0; j != n; j++){
            s = int((to_string((matrix.at(j, i)))).length());
            
            if (s > max){
                max = s;
            }
        }
        vect.push_back(max);
        max = 0;
    }
    
    int number;
    cout << "Matrix: \n" << endl;
    for (int i = 0; i != n; i++){
        cout << "   (  ";
        for (int j = 0; j != n; j++){
            number = int((to_string((matrix.at(i, j)))).size());
            int a = vect[j] - number;
            while (a){
                cout << " ";
                a--;
            }
            cout << matrix.at(i, j) << "  ";
        }
        cout << ")\n";
    }
    cout << endl;
}

void print_input(){
    cout << "Введи розмірність матриці: ";
    int n;
    cin >> n;
    Matrix1<calc_type> matrix(n, n);
    cout << "Введи матрицю:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix.at(i, j);
        }
    }
    
    cout << endl;
    output_matrix(matrix, n);
    cout << "Матриця " << n << "*" << n << endl;
    
    Matrix1<calc_type> eigenvectors(n, n);
    // матриця одинична
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            eigenvectors.at(i, j) = (i == j);
        }
    }

    vector<calc_type> eigenvalues = jacobi_eigenvalue_algorithm(matrix, eigenvectors, n, 1e-12);
    print_eigenvalues(eigenvalues);

    //print_eigenvectors(eigenvectors, n);
}

void random_matrix(int rozmirnist, int chysla){
    random_device rd;
    mt19937 mersenne(rd());
    
    
    vector<calc_type> eigenvalues;
    
    int number;
    cout << "Введи кількість матриць: " ;
    cin >> number;
    cout << endl;
    
    while (number){
        int rund_number1   = mersenne();
        int n              = abs(rund_number1) % (rozmirnist+1);    // розмірність матриці(max = 40)
        
        Matrix1<calc_type> matrix(n, n);
        
        if (n > 3){
            //cout << n << " --> ";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    int rund_number1   = mersenne();
                    double dimension      = rund_number1 % chysla; // числа в матриці від -1000 до 1000
                    matrix.at(i, j) = dimension;
                }
            }
            int k = 1;
            for (int i = 1; i != n; ++i) {
                for (int j = 0; j != k; ++j) {
                    matrix.at(i, j) = matrix.at(j, i);
                }
                k++;
            }
            
            cout << endl;
            output_matrix(matrix, n);
            cout << "Матриця " << n << " * " << n << endl;
            
            Matrix1<calc_type> eigenvectors(n, n);
            // матриця одинична
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    eigenvectors.at(i, j) = (i == j);
                }
            }
            
            
            eigenvalues = jacobi_eigenvalue_algorithm(matrix, eigenvectors, n, 1e-12);
            
            print_eigenvalues(eigenvalues);
            print_eigenvectors(eigenvectors, n);
            
            number--;
        }
    }
}
