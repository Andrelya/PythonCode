#ifndef linear_regression_of_the_model_hpp
#define linear_regression_of_the_model_hpp

#include "Matrix1.hpp"
#include "Gaussian method.hpp"
#include <random>

using namespace std;
typedef double coord_t;         // coordinate type
typedef double coord2_t;

struct Point {
    coord_t x, y;

    bool operator <(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

//vector<double> algoritm(vector<Point> vect);

void outputt(int interval_number_x);
void outputt1(vector<Point> vect);

#endif /* linear_regression_of_the_model_hpp */
