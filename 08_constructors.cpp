#include <iostream>
#include <cstring>


namespace terminal
{
    void log(const char *tekst)
    {
        std::cout << "--------------------------------------\n";
        std::cout << tekst << '\n';
        std::cout << "--------------------------------------\n";
    }
}


class String
{
private:
    char *m_data = nullptr;
    std::size_t m_size = 0;

public:
    String() : m_data(), m_size() //Default Constructor with member initializer list
    {
        std::printf("Created!\n");
    }
    String(const char *string) //Constructor
    {
        m_size = std::strlen(string);
        m_data = new char[m_size]; //allocation
        std::memcpy(m_data, string, m_size);
        std::printf("Created!\n");
    }
    String(const String &other) //Copy Constructor
    {
        m_size = other.m_size;
        m_data = new char[m_size]; //allocation
        std::memcpy(m_data, other.m_data, m_size);
        std::printf("Copied!\n");
    }
    String &operator=(const String &other) //Copy Assignemnt Operator
    {
        if (this != &other) {
            delete[] m_data; //deallocation of old memory
            m_size = other.m_size;
            m_data = new char[m_size]; //allocation of new memory
            std::memcpy(m_data, other.m_data, m_size);
            std::printf("Copied!\n");
        }

        return *this;
    }
    String(String &&other) //Move Constructor
    {
        m_size = other.m_size;
        m_data = other.m_data; //pointing and taking control over the data
        other.m_size = 0;
        other.m_data = nullptr; //making sure the data stays allocated after destruction of temporary rvalue
        std::printf("Moved!\n");
    }
    String &operator=(String &&other) //Move Assignment Operator
    {
        if (this != &other) {
            delete[] m_data; //deallocation of old memory
            m_size = other.m_size;
            m_data = other.m_data;
            other.m_size = 0;
            other.m_data = nullptr;
            std::printf("Moved!\n");
        }

        return *this;
    }
    ~String() //Destructor
    {
        delete[] m_data; //deallocation
        std::printf("Destroyed!\n");
    }

public:
    void print() const //Const Print for const correctness
    {
        for (std::size_t i=0; i<m_size; i++) {
            std::printf("%c", m_data[i]);
        }
        std::printf("\n");
    }
    std::size_t size() const { return m_size; } //Const Getter for const correctness
    char &at(std::size_t i)             { return m_data[i]; } //Getter and Setter
    const char &at(std::size_t i) const { return m_data[i]; } //Const Getter for const correctness
    char &operator[](std::size_t i)             { return at(i); } //Getter and Setter Operator
    const char &operator[](std::size_t i) const { return at(i); } //Const Getter Operator
};


class Entity
{
private:
    String m_name;
public:
    Entity(const String &name) : m_name(name) //Copy Constructor
    {}
    Entity(String &&name) : m_name(std::move(name)) //Move Constructor
    {}
    void print_name() { m_name.print(); }
};


int main()
{
    String string = String("Alice"); //lvalue
    String copied_string = String(); //lvalue
    String moved_string = String(); //lvalue
    Entity Alice = Entity(string); //passing a lvalue -> Copy data
    Entity Bob = Entity(String("Bob")); //passing a temporary rvalue -> Move data

    std::cout << "Alice: ";
    Alice.print_name();
    std::cout << "Bob: ";
    Bob.print_name();

    std::cout << "string: ";
    string.print();
    std::cout << "copied_string: ";
    copied_string.print();
    std::cout << "moved_string: ";
    moved_string.print();
    copied_string = string; //Copy
    moved_string = std::move(string); //Converting a lvalue into a temporary rvalue -> Move Semantics
    std::cout << "string: ";
    string.print();
    std::cout << "copied_string: ";
    copied_string.print();
    std::cout << "moved_string: ";
    moved_string.print();

    terminal::log("endprogram");
    return 0;
}