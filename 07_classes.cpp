#include <iostream>
#include <iomanip>
#include <array>


namespace terminal
{
    void log(const char *tekst)
    {
        std::cout << "--------------------------------------\n";
        std::cout << tekst << '\n';
        std::cout << "--------------------------------------\n";
    }
}


class MyClass
{
public: //access specifier, C++ style class default private, C style struct default public
    MyClass() //Constructor method
    {
        std::cout << "MyClass constructed\n";
    }
    ~MyClass() //Destructor method
    {
        std::cout << "MyClass destructed\n";
    }
};


int main()
{
    terminal::log("stack allocations");
    MyClass Object = MyClass();
    MyClass Object_carray[2];
    std::array<MyClass, 2> Object_stdarray = std::array<MyClass, 2>();

    terminal::log("heap allocations");
    MyClass *Object_ptr1 = new MyClass();
    MyClass *Object_ptr2 = new MyClass[2];
    std::array<MyClass, 2> *Object_stdarray_ptr = new std::array<MyClass, 2>();

    terminal::log("heap deallocations");
    delete Object_ptr1;
    delete[] Object_ptr2;
    delete Object_stdarray_ptr;
    Object_ptr1 = nullptr;
    Object_ptr2 = nullptr;
    Object_stdarray_ptr = nullptr;

    terminal::log("stack deallocations");
    return 0;
}