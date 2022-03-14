#ifndef Matrix1_hpp
#define Matrix1_hpp

#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <regex>
#include <cmath>

using namespace std;

struct Type_matrix{
    
    vector<vector<double>> value;
};

class Matrix {
    
private:
    Type_matrix ODZ(Type_matrix A){
        /*
            Замінює пропущені елементи на нуль.
         */
        
        int now = 0;
        int max = 0;
        
        for (auto i = A.value.begin(); i !=A.value.end(); i++){
            now = int((*i).size());
            if (now > max){max = now;}
        }

        for (auto i = A.value.begin(); i !=A.value.end(); i++){
            now = int((*i).size());
            while (now != max){
                (*i).push_back(0);
                now = int((*i).size());
            }
        }
        return A;
    }
    
    
    Type_matrix number_in_matrix(Type_matrix A, double number){
        /*
            Переводить число в матрицю
         */
        
        A = ODZ(A);
        double chyslo;
        vector<double> vect;
        Type_matrix C;
        
        for (int i = 0; i != A.value.size(); i++){
            for (int j = 0; j != A.value[0].size(); j++){
                if ( i == j)
                    chyslo = number;
                else
                    chyslo = 0;
                vect.push_back(chyslo);
            }
            C.value.push_back(vect);
            vect = {};
        }
        return C;
    }
    
 
    
    
    
    
    
public:

    //1
    Type_matrix assign(Type_matrix A){
        /*
            ПРИСВОЮЄМ МАТРИЦІ ЗНАЧЕННЯ ІНШОЇ МАТРИЦІ
         */
        
        A = ODZ(A);     // перевірка кількості елементів по рядку
        return A;
    }
    
    //2
    bool equality(Type_matrix A, Type_matrix B){
        /*
            ПЕРЕВІРКА РІВНОСТІ ДВОХ МАТРИЦЬ
         */
        
        A = ODZ(A);     // перевірка кількості елементів по рядку
        B = ODZ(B);     // перевірка кількості елементів по рядку
        
        if ((A.value.size() == B.value.size()) and (A.value[0].size() == B.value[0].size())){
            for (int i = 0; i != A.value.size(); i++){
                for (int j = 0; j != A.value[0].size(); j++){
                    if (A.value[i][j] != B.value[i][j]){return false;}
                }
            }
        }
        else{
            return false;
        }
        
        return true;
    }
    
    
    
    //3(1_1)
    Type_matrix sum(Type_matrix A, Type_matrix B){
        /*
            СУМА МАТРИЦЬ (при тому що розмірність матриць А і В рівна)!!!)
         */
        
        A = ODZ(A);     // перевірка кількості елементів по рядку
        B = ODZ(B);     // перевірка кількості елементів по рядку

        Type_matrix C ;
        double chyslo;
        vector<double> vect;

        if ((A.value.size() == B.value.size()) and (A.value[0].size() == B.value[0].size())){
            for (int i = 0; i != A.value.size(); i++){
                for (int j = 0; j != A.value[0].size(); j++){
                    chyslo = double(A.value[i][j]) + double(B.value[i][j]);
                    vect.push_back(chyslo);
                }
                C.value.push_back(vect);
                vect= {};
            }
        }
        else{
            C = { {{}} };
        }
        return C;
    }
    
    //3(1_2)
    Type_matrix sum(Type_matrix A, double number){
        /*
            СУМА МАТРИЦІ І ЧИСЛА
         ( при тому що розмірність матриці А --> n*n, бо число переводиться в квадратну матрицю)
         */
        
        A = ODZ(A);                 // перевірка кількості елементів по рядку
        Type_matrix C = { {{}} };
        if ( A.value.size() == A.value[0].size() ){
            Type_matrix B = number_in_matrix(A, number);
            C = sum(A, B);
        }
        return C;
    }
    
    //3(2_1)
    Type_matrix difference(Type_matrix A, Type_matrix B){
        /*
            РІЗНИЦЯ МАТРИЦЬ (при тому що розмірність матриць А і В рівна)!!!)
         */
        
        A = ODZ(A);     // перевірка кількості елементів по рядку
        B = ODZ(B);     // перевірка кількості елементів по рядку

        Type_matrix C ;
        double chyslo;
        vector<double> vect;
        

        if ((A.value.size() == B.value.size()) and (A.value[0].size() == B.value[0].size())){
            for (int i = 0; i != A.value.size(); i++){
                for (int j = 0; j != A.value[0].size(); j++){
                    chyslo = double(A.value[i][j]) - double(B.value[i][j]);
                    vect.push_back(chyslo);
                }
                C.value.push_back(vect);
                vect= {};
            }
        }
        else{
            C = { {{}} };
        }
        return C;
    }
    
    //3(2_2)
    Type_matrix difference(Type_matrix A, double number){
        /*
            РІЗНИЦЯ МАТРИЦІ І ЧИСЛА
          (при тому що розмірність матриці А --> n*n, бо число переводиться в квадратну матрицю)
         */
        
        A = ODZ(A);              // перевірка кількості елементів по рядку
        
        Type_matrix C = { {{}} };
        if ( A.value.size() == A.value[0].size() ){
            Type_matrix B = number_in_matrix(A, number);
            C = difference(A, B);
        }
        
        return C;
    }
    
    //3(3_1)
    Type_matrix multiplication(Type_matrix A, Type_matrix B){
        /*
            МНОЖЕННЯ МАТРИЦЬ (при тому що розмірність матриць А і В рівна)!!!)
         */
        
        A = ODZ(A);     // перевірка кількості елементів по рядку
        B = ODZ(B);     // перевірка кількості елементів по рядку

        Type_matrix C ;
        int size1 = int(A.value.size());
        int size2 = int(A.value.size());
        int size3 = int(A.value.size());
        int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
        double chyslo;
        double sum1 = 0;
        vector<double> vect;
        
        
        if ((A.value.size() == B.value.size()) and (A.value[0].size() == B.value[0].size()) and (A.value.size() == A.value[0].size())){
            while (size3){
                while (size1){
                    while (size2){
                        chyslo = A.value[a1][a2] * B.value[a3][a4];
                        sum1 += chyslo;
                        a2++;
                        a3++;
                        size2--;
                    }
                    size2 = int(A.value.size());
                    vect.push_back(sum1);
                    sum1 = 0;
                    a2   = 0;
                    a3   = 0;
                    a4++;
                    size1--;
                } // додаєм перший вектор
        
                size1 = int(A.value.size());
                C.value.push_back(vect);
                a4    = 0;
                a1++;
                vect  = {};
                size3--;
            }
        }
        else{
            C = { {{}} };
        }
        
        return C;
    }
    //3_(3_2)
    Type_matrix multiplication(Type_matrix A, double number){
        /*
            РІЗНИЦЯ МАТРИЦІ І ЧИСЛА ( при тому що розмірність матриці А --> n*n )
         */
        
        A = ODZ(A);              // перевірка кількості елементів по рядку
        
        Type_matrix C = { {{}} };;
        if ( A.value.size() == A.value[0].size() ){
            Type_matrix B = number_in_matrix(A, number);
            C = multiplication(A, B);
        }
        return C;
    }
    
    //4
    Type_matrix transposition(Type_matrix A){
        vector<double> vect;
        Type_matrix C;
        
        A = ODZ(A);              // перевірка кількості елементів по рядку

        if ( A.value.size() == A.value[0].size()){
            for (int i = 0; i != A.value.size(); i++){
                for (int j = 0; j != A.value[0].size(); j++){
                    vect.push_back(A.value[j][i]);
                }
                C.value.push_back(vect);
                vect = {};
            }
        }
        else{
            C = { {{}} };
        }
        return C;
    }
    
    
    //5(1)
    void output(Type_matrix A){
        /*
           виводить на екран матрицю
         */
        int max = 0;
        int s;
        vector<int> vect;
        A = ODZ(A);     // перевірка кількості елементів по рядку
        
        for (int i = 0; i != A.value[0].size(); i++){    // шукаєм найдовше число в кожному стовпці
            for (int j = 0; j != A.value.size(); j++){
                s = int((to_string((A.value[j][i]))).length());
                
                if (s > max){
                    max = s;
                }
            }
            vect.push_back(max);
            max = 0;
        }
        
        int number;
        cout << "Matrix: \n" << endl;
        for (int i = 0; i != A.value.size(); i++){
            cout << "   (  ";
            for (int j = 0; j != A.value[0].size(); j++){
                number = int((to_string((A.value[i][j]))).size());
                int a = vect[j] - number;
                while (a){
                    cout << " ";
                    a--;
                }
                cout << A.value[i][j] << "  ";
            }
            cout << ")\n";
        }
        cout << endl;
        
    }
    
    //5(2)
    Type_matrix input(){
        Type_matrix C;
        int number_line;
        cout << "Введи кількість рядків в матриці: ";
        cin >> number_line;
        int number_column;
        cout << "Введи кількість стовпців в матриці: ";
        cin >> number_column;
        int copy = number_column;
        int i = 1;
        int j = 1;
        double number;
        vector<double> vect;
        while (number_line){
            while (number_column){
                cout << "Введи елемент " << i << j << " : ";
                cin >> number;
                vect.push_back(number);
                number_column--;
                j++;
            }
            number_column = copy;
            C.value.push_back(vect);
            vect.clear();
            j = 1;
            i++;
            number_line--;
        }
        
        return C;
    }
};



#endif /* Matrix1_hpp */
