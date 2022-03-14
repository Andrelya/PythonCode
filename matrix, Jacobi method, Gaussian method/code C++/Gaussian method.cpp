#include "Matrix1.hpp"
#include "Gaussian method.hpp"


Type_matrix input1(){
    /*
        Вводим матрицю
     */
    int number_value;
    cout << "Введи кількість невідомих змінних: ";
    cin >> number_value;
    int number_equality;
    cout << "Введи кількість рівностей: ";
    cin >> number_equality;
    
    double number;
    vector<double> vect;
    Type_matrix C;
    int i = 1;
    int j = 1;
    int k = 1;
    int copy = number_value;
    while (number_equality){
        while (number_value){
            cout << "Введи елемент " << i << j << " : ";
            cin >> number;
            vect.push_back(number);
            number_value--;
            j++;
        }
        cout << "Введи вільний член " << k << " : ";
        cin >>  number;
        vect.push_back(number);
        
        
        number_value = copy;
        C.value.push_back(vect);
        vect.clear();
        j = 1;
        k++;
        i++;
        number_equality--;
    }
    return C;
}

vector<int> rang(Type_matrix A){
    /*
        Знаходимо ранг матриці.
     */
    int rang1 = 0;   // розширена матриця
    int column = int(A.value[0].size());
    for (auto i = A.value.begin(); i != A.value.end(); i++){
        for (auto j = 0; j != (column); j++){
            if ((*i)[j] != 0){
                rang1++;
                break;
            }
        }
    }
    int rang2 = 0;   //  матриця коефіцієнтів
    for (auto i = A.value.begin(); i != A.value.end(); i++){
        for (auto j = 0; j != (column - 1); j++){
            if ((*i)[j] != 0){
                rang2++;
                break;
            }
        }
    }
    vector<int> vect = {rang1, rang2};
    return vect;
}

Type_matrix basis(Type_matrix A){
    /*
        Зводим матрицю, щоб були одинички
     */
    Type_matrix C;
    vector<double> vect1;
    
    int k    = 0;
    int line = int(A.value.size());
    int column = int(A.value[0].size());
    for (int i = 0; i != line; i++){
        for (int j = 0; j != column; j++){
            if (A.value[i][k] != 0){
                double number = A.value[i][j] / A.value[i][k];
                vect1.push_back(number);
                //cout << number << " --> ";
            }
            else{
                vect1.push_back(0);
                k++;
            }
        }
        C.value.push_back(vect1);
        vect1 = {};
        k = 0;
    }
    
    return C;
}

vector<double> output1(Type_matrix A){
    vector<double> vect;
    int line   = int(A.value.size());
    int column = int(A.value[0].size()) - 1;
    int y = 2;
    
    vect.push_back(A.value[0][column] / A.value[0][0]);
    for (int i = 1; i != line; i++){
       
        vect.push_back(A.value[i][column]);
        y++;
    }
    return vect;
}

vector<double> output2(Type_matrix A){
    
    
    Type_matrix B = basis(A);
    int column = int(A.value[0].size()) - 1;
    int line = int(A.value.size());
    
    vector<double> vect1;
    for  (int i = 0; i != column; i++){
        vect1.push_back(0);
    }
    
    for (int i = 0; i != line; i++){
        for (int j = 0; j != column; j++){
            if (B.value[i][j] == 1){
                vect1[j] = B.value[i][column];
                break;
            }
        }
    }
    return vect1;
}


Type_matrix direct_bypass(Type_matrix A){
    /*
        Метод Гауса.
     */
    
    Matrix qwe;
    Type_matrix C;
    
    int q      = 0;
    int k      = 0;
    int z      = 0;
    int x      = 1;
    int line   = int(A.value.size());
    int column = int(A.value[0].size());
    
    vector<double> vect;
    //Утворюєм матрицю (line*column) з нулів.
    for (int i = 0; i != line; i++){
        for (int j = 0; j != column; j++){
            vect.push_back(0);
        }
        C.value.push_back(vect);
        vect = {};
    }
    
    //ПРЯМИЙ ОБХІД (Зведення до нижнього трикутника)
    while (k != (line-1)){
        for (int i = k; i != line; i++){
            for (int j = 0; j != column; j++){
                if (A.value[q][k] != 0){
                    C.value[i][j] = (A.value[i][j] / A.value[q][k]);
                }
            }
            q++;
        }
        A = qwe.assign(C);
        k++;
        q = k;
        
        for (int i = x; i != line; i++){
            for (int j = 0; j != column; j++){
                C.value[i][j] = A.value[i][j] - A.value[z][j];
               
            }
            
        }
        A = qwe.assign(C);
        x++;
        z++;
    }
    
    
    return A;
}

Type_matrix reverse_bypass(Type_matrix A){
    Matrix qwe;
    Type_matrix C;
    int line = int(A.value.size());
    int column = int(A.value[0].size());
    int k = line - 1;
    int q = line - 1;
    int x = line - 2;
    int z = line - 1;
    
    vector<double> vect;
    //Утворюєм матрицю (line*column) з нулів.
    for (int i = 0; i != line; i++){
        for (int j = 0; j != column; j++){
            vect.push_back(0);
        }
        C.value.push_back(vect);
        vect = {};
    }
    
    //ЗВОРОТНІЙ ОБХІД (Зведення до верхнього трикутника)
    while (k != 0){
        for (int i = k; i != -1; i--){
            for (int j = 0; j != column; j++){
                if (A.value[q][k] != 0){
                    C.value[i][j] = (A.value[i][j] / A.value[q][k]) ;
                }
            }
            q--;
        }
        A = qwe.assign(C);
        k--;
        q = k;
        
        for (int i = x; i != -1; i--){
            for (int j = 0; j != column; j++){
                C.value[i][j] = A.value[i][j] - A.value[z][j];
            }
        }
        A = qwe.assign(C);
        x--;
        z--;
    }
    
    return A;
}

vector<double> result1(Type_matrix A){
    
    Type_matrix C  = direct_bypass(A);
    Type_matrix B  = reverse_bypass(C);

    vector<int> vect = rang(B);  // ранг матриці {розширена, не розширена}
    
    int line       = int(A.value.size());
    int column     = int(A.value[0].size()) - 1;
    //cout << "Ранг: " << rang1 << endl;
    
    vector<double> vect1;
    if ((vect[0] == line) and (vect[0] == column) and (vect[0] == vect[1])){
        vect1 = output1(B);
    }
    else if(vect[0] != vect[1]){
        cout << "Ранг розширеної матриці не рівний з рангом основної матриці" << endl;
        cout << "Розвязку не має!!!" << endl;
    }
    else if ((vect[0] == vect[1]) and ((vect[0] != column) or (vect[0] != line))){
        vect1 = output2(B);
    }
    return vect1;
}

void result2(Type_matrix A){
    Matrix matr;
    matr.output(A);
    
    vector<double> vect = result1(A);
    for (int i = 0; i != vect.size(); i++){
        cout << "x" << (i + 1) << " = " << vect[i] << endl;
    }
}

void resultat_with_input(){
    Type_matrix A = input1();
    
    Matrix matr;
    matr.output(A);
    
    vector<double> vect = result1(A);
    for (int i = 0; i != vect.size(); i++){
        cout << "x" << (i + 1) << " = " << vect[i] << endl;
    }
    
}


