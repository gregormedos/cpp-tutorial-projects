#include <iostream>
#include <iomanip>


namespace terminal
{
    void log(const char *tekst)
    {
        std::cout << "--------------------------------------\n";
        std::cout << tekst << '\n';
        std::cout << "--------------------------------------\n";
    }
    void log(double x)
    {
        std::cout << std::scientific << std::setprecision(7) << std::setw(16) << x << '\n';
    }
}


int main()
{
    terminal::log("program");
    terminal::log(3.14159265359);
    
    terminal::log("endprogram");
    return 0;
}