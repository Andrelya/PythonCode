#include "Matrix1.hpp"
#include "Gaussian method.hpp"
#include "linear regression of the model.hpp"
#include "Метод Якобі.hpp"


int main() {
    Matrix mat;
    //Type_matrix A = mat.input();
    random_matrix(10, 1000);
    return 0;
}



/*
 
    2 ЗАВДАННЯ!!! (метод Гауса розв’язання СЛАР)
 
    1)resultat_with_input(); // вводим матрицю через термінал
 
  2)Matrix qwe;
    Type_matrix A = {    // штучний базис (-2;3;0)
        {
         
         {1, 2, 3, 4,},
         {5, 6, 7, 8,},
         {9, 10, 11, 12,},

        }
    };
    result2(A);
 
    
    3)Type_matrix B = {    // розвязок (7,186; -2,57; 6.39; 8,99)
        {
      
            {34, 54, 5, 65,233},
            {-45, 55, 23, -34,23},
            {4, 10, -45, 12, -234},
            {43, 54, 65, 12, 75},

        }
    };
    result2(B);
 
 
    
 
 
 
 
 
 
 
 
    3 ЗАВДАННЯ!!! (Метод Якобі для знаходження власних значень матриці)
 
    1) void random_matrix(int rozmirnist, int chysla);   // рандомні числа від -chysla до chysla і матриця найбільшої розмірності
    
    
    2)void print_input();  // вводим матрицю і розмірність з консолі
 
 
 
 
 
 
 
 
 
 
 
 
    4 ЗАВДАННЯ!!! (Знаходження параметрів лінійної регресійної моделі по заданим точкам)
    
    1)void outputt(int interval_number_x);        // рандомні кординати х від -interval_number_x до interval_number_x
    
    2)vect = {{1,6}, {2,5}, {3,7}, {4,10}};     // Відповідь: y = 1.4x + 3.5
    
    void outputt1(vector<Point> vect);

    
 */
