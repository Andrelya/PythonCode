#include "linear regression of the model.hpp"


vector<Point> random_points(int interval_number_x){
    random_device rd;
    mt19937 mersenne(rd());
    
    int a;
    cout << "y = a*x + b" << endl;
    cout << "Введи a: ";
    cin >> a;
    
    int b;
    cout << "Введи b: ";
    cin >> b;
    
    int number_points;
    cout << "Введи кількість точок: ";
    cin >> number_points;
    
    vector<Point> points_rund;
    
    Point point1;
    while (number_points){
        int rund_number1 =  mersenne();
        double x = rund_number1 % (interval_number_x + 1);
        double y = a * x + b;
        point1 = {x, y};
        points_rund.push_back(point1);
        number_points--;
    }
    return points_rund;
}

void output_points(vector<Point> vect){
    cout << "[ ";
    for (auto i = vect.begin(); i != vect.end(); i++){
        cout << "(" << (*i).x << ", "<< (*i).y << "), ";
    }
    cout << "]";
}


vector<double> coefficients1(vector<Point> vect){
    double sum1 = 0;
    double sum2 = 0;
    double sum3 = 0;
    for (auto i = vect.begin(); i != vect.end(); i++){
        sum1 += 2;
        sum2 += 2 * (*i).x;
        sum3 += 2 * (*i).y;
    }
    
    vector<double> vector = {sum1, sum2, sum3};
    return vector;
}

vector<double> coefficients2(vector<Point> vect){
    double sum1 = 0;
    double sum2 = 0;
    double sum3 = 0;
    for (auto i = vect.begin(); i != vect.end(); i++){
        sum1 += 2 * (*i).x;
        sum2 += 2 * pow((*i).x,2);
        sum3 += 2 * (*i).y * (*i).x;
    }
    
    vector<double> vector = {sum1, sum2, sum3};
    return vector;
}

vector<double> algoritm(vector<Point> vect){
    vector<double> vect1 = coefficients1(vect);
    vector<double> vect2 = coefficients2(vect);
    Type_matrix A = {
        {
            {vect1[0], vect1[1], vect1[2]},
            {vect2[0], vect2[1], vect2[2]},
        }
    };
    vector<double> vect3 = result1(A);
    return vect3;
}

void outputt(int interval_number_x){
    vector<Point> vect = random_points(interval_number_x);
    output_points(vect); //вивід точок
    cout << endl;
    
    vector<double> vect1 = algoritm(vect);
    
    cout << "y = ";
    if (vect1[1] != 0){
        if (vect1[0] < 0){
            cout << vect1[1] << "x - " << abs(vect1[0]);
        }
        else if (vect1[0] > 0){
            cout << vect1[1] << "x + " << abs(vect1[0]);
        }
        else if (vect1[0] == 0){
            cout << vect1[1] << "x";
        }
    }
    else{
        if (vect1[0] < 0){
            cout << vect1[0];
        }
        else if (vect1[0] > 0){
            cout << vect1[0];
        }
        else if (vect1[0] == 0){
            cout << 0;
        }
    }
    cout << endl;
}

void outputt1(vector<Point> vect){
    /*
        vect = {{1,6}, {2,5}, {3,7}, {4,10}};
        Відповідь: y = 1.4x + 3.5
     */
    
    vector<double> vect1 = algoritm(vect);
    
    cout << "y = ";
    if (vect1[1] != 0){
        if (vect1[0] < 0){
            cout << vect1[1] << "x - " << abs(vect1[0]);
        }
        else if (vect1[0] > 0){
            cout << vect1[1] << "x + " << abs(vect1[0]);
        }
        else if (vect1[0] == 0){
            cout << vect1[1] << "x";
        }
    }
    else{
        if (vect1[0] < 0){
            cout << vect1[0];
        }
        else if (vect1[0] > 0){
            cout << vect1[0];
        }
        else if (vect1[0] == 0){
            cout << 0;
        }
    }
    cout << endl;
}
