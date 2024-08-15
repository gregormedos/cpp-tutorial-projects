#include <iostream>
#include <fstream>
#include <iomanip>


int main()
{
    std::ofstream output = std::ofstream();
    std::ifstream input = std::ifstream();
    std::string text = std::string();
    double tstep;
    double temp;
    double dens;
    double pres;

    output.open("filename.txt");
    output << std::setw(16) << "Time step" << std::setw(16) << 0.001 << '\n';
    output << std::setw(16) << "Temperature" << std::setw(16) << 0.1 << '\n';
    output << std::setw(16) << "Density" << std::setw(16) << 0.5 << '\n';
    output << std::setw(16) << "Pressure" << std::setw(16) << 1.013 << '\n';
    output.close();

    input.open("filename.txt");
    input >> text >> text >> tstep;
    input >> text >> temp;
    input >> text >> dens;
    input >> text >> pres;
    input.close();

    std::cout << std::setw(16) << tstep << '\n';
    std::cout << std::setw(16) << dens << '\n';
    std::cout << std::setw(16) << temp << '\n';
    std::cout << std::setw(16) << pres << '\n';

    return 0;
}