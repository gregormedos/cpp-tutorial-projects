#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>


void stdstring_print(const std::string &string) //passing a const lvalue reference : 8 bytes
{
    std::cout << std::setw(16) << string << '\n';
}

void stdstring_append(std::string &string, std::string &&suffix) //passing a lvalue reference : 8 bytes, passing a rvalue reference : 8 bytes
{
    string += suffix;
}

void stdarray_double3_print(const std::array<double, 3> &array) //passing a const lvalue reference : 8 bytes
{
    //range-based for loop
    for (double elem : array) {
        std::cout << std::fixed << std::setprecision(7) << std::setw(16) << elem;
    }
    std::cout << '\n';
}

void stdvector_double_print(const std::vector<double> &vector) //passing a const lvalue reference : 8 bytes
{
    //range-based for loop
    for (double elem : vector) {
        std::cout << std::fixed << std::setprecision(7) << std::setw(16) << elem;
    }
    std::cout << '\n';
}

void stdvector_double_mult_scalar(std::vector<double> &vector, double scalar) //passing a lvalue reference : 8 bytes, passing a copy : 8 bytes
{
    for (int i=0; i<vector.size(); i++) {
        vector[i] = scalar * vector[i];
    }
}


int main()
{
    //declaration and definition
    std::string s = std::string("abc"); //dynamic array of chars
    std::array<double, 3> a = {1.0, 2.0, 3.0}; //static array of doubles
    std::vector<double> v = {4.0, 5.0 , 6.0}; //dynamic array of doubles

    stdstring_print(s);
    stdstring_append(s,"def"); //implicit conversion from string literal LVALUE into std::string RVALUE
    stdstring_print(s);
    
    stdarray_double3_print(a);

    stdvector_double_print(v);
    v.push_back(7.0); //passing a double constant literal as a rvalue reference : 8 bytes
    stdvector_double_print(v);
    stdvector_double_mult_scalar(v, 2.0); //passing a double constant literal as a copy : 8 bytes
    stdvector_double_print(v);

    return 0;
}