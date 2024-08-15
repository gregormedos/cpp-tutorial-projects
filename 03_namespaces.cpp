#include <iostream>
#include <iomanip>


namespace hazelnut
{
    double x;
    void print(double);
}

namespace walnut
{
    double x;
    void print(double);
}


void hazelnut::print(double x)
{
    std::cout << std::fixed << std::setprecision(7) << std::setw(16) << x << '\n';
}

void walnut::print(double x)
{
    std::cout << std::scientific << std::setprecision(7) << std::setw(16) << x << '\n';
}


int main()
{
    double x = 0.001;
    hazelnut::x = 0.0001;
    walnut::x = 0.00001;

    hazelnut::print(x);
    hazelnut::print(hazelnut::x);
    hazelnut::print(walnut::x);
    walnut::print(x);
    walnut::print(hazelnut::x);
    walnut::print(walnut::x);

    return 0;
}