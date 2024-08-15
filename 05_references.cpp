#include <iostream>
#include <iomanip>
#include <string>


namespace copy //copying more than 8 bytes is expensive
{
    void print_double(double); //sizeof(double) = 8 bytes
    void print_stdstring(std::string); //expensive as sizeof(std::string) grows
}

namespace pointers //C style
{
    void print_double(const double *); //8 bytes
    void print_stdstring(const std::string *); //8 bytes
}

namespace references //C++ style
{
    void print_double(const double &); //const lvalue reference, 8 bytes
    void print_double(double &&); //rvalue reference, 8 bytes
    void print_stdstring(const std::string &); //const lvalue reference, 8 bytes
    void print_stdstring(std::string &&); //rvalue reference, 8 bytes
}


void copy::print_double(double value_copy)
{
    std::cout << std::fixed << std::setprecision(7) << std::setw(16) << value_copy << '\n';
}

void copy::print_stdstring(std::string stdstring_copy)
{
    std::cout << std::setw(16) << stdstring_copy << '\n';
}

void pointers::print_double(const double *value_ptr)
{
    std::cout << std::fixed << std::setprecision(7) << std::setw(16) << *value_ptr << '\n'; //* operator for pointer dereferencing
}

void pointers::print_stdstring(const std::string *stdstring_ptr)
{
    std::cout << std::setw(16) << *stdstring_ptr << '\n'; //* operator for pointer dereferencing
}

void references::print_double(const double &value_ref)
{
    std::cout << std::fixed << std::setprecision(7) << std::setw(16) << value_ref << '\n';
}

void references::print_double(double &&value_ref)
{
    std::cout << std::fixed << std::setprecision(7) << std::setw(16) << value_ref << '\n';
}

void references::print_stdstring(const std::string &stdstring_ref)
{
    std::cout << std::setw(16) << stdstring_ref << '\n';
}

void references::print_stdstring(std::string &&stdstring_ref)
{
    std::cout << std::setw(16) << stdstring_ref << '\n';
}


int main()
{
    std::string Alice = std::string("Alice");
    std::string Bob = std::string("Bob");
    std::string *Ptr = &Alice;
    std::string &Ref = Bob;
    double pi = 3.14159265359;
    std::string stdstring = std::string("std string");

    std::cout << Alice << '\n';
    std::cout << Bob << '\n';
    std::cout << *Ptr << '\n';
    std::cout << Ref << '\n';
    Ptr = &Ref; //pointing to the address of the reference of Bob
    Ref = Alice; //assigning the value of Alice to the reference of Bob
    std::cout << Alice << '\n';
    std::cout << Bob << '\n';
    std::cout << *Ptr << '\n';
    std::cout << Ref << '\n';
    *Ptr = "Bob"; //dereferencing pointer and assigning a value to the pointed adress
    Alice = Ref; //assigning the value of the reference of Bob to the value of Alice
    std::cout << Alice << '\n';
    std::cout << Bob << '\n';
    std::cout << *Ptr << '\n';
    std::cout << Ref << '\n';
    Ptr = &Alice; //pointing to the adress of Alice
    Alice = "Alice"; //assigning a value to the value of Alice
    std::cout << Alice << '\n';
    std::cout << Bob << '\n';
    std::cout << *Ptr << '\n';
    std::cout << Ref << '\n';

    copy::print_double(pi); //copying a lvalue
    pointers::print_double(&pi); //passing a lvalue by address, & operator for lvalue address
    references::print_double(pi); //passing a lvalue by const lvalue reference

    copy::print_double(3.14159265359); //copying a rvalue
    references::print_double(3.14159265359); //passing a rvalue by rvalue reference

    copy::print_stdstring(stdstring); //copying a lvalue
    pointers::print_stdstring(&stdstring); //passing a lvalue by address, & operator for lvalue address
    references::print_stdstring(stdstring); //passing a lvalue by const lvalue reference

    copy::print_stdstring("string literal"); //copying a rvalue
    references::print_stdstring("string literal"); //passing a rvalue by rvalue reference
    
    return 0;
}