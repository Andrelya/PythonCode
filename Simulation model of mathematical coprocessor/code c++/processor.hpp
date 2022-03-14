#ifndef processor_hpp
#define processor_hpp

#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <random>
#include <math.h>
#include <fstream>

using namespace std;

vector<int> direct_code(int number);
vector<int> complementary_code(int number);

string output_number(vector<int> vect);
vector<int> addition(vector<int> vect1, vector<int> vect2);
void input();

#endif /* processor_hpp */
