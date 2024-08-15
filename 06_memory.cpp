#include <iostream>
#include <iomanip>


int main()
{
    //dynamic memory allocation on the heap
    double *a = new double; //8 bytes
    double *b = new double[100]; //800 bytes

    //garbage collection
    delete a;
    delete[] b;
    a = nullptr;
    b = nullptr;

    return 0;
}