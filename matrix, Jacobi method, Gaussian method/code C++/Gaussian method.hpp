#ifndef Gaussian_method_hpp
#define Gaussian_method_hpp


#include "Matrix1.hpp"

vector<double> result1(Type_matrix A);  // вектор результатів
void result2(Type_matrix A);            // вивід результатів
void resultat_with_input();


Type_matrix direct_bypass(Type_matrix A); // прямий обхід
Type_matrix reverse_bypass(Type_matrix A); // зворотній обхід
Type_matrix basis(Type_matrix A);          // для штучного базису
#endif /* Gaussian_method_hpp */
