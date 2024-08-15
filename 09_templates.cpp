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


namespace templates
{
    template<typename T>
    void print(T &&rvalue)
    {
        std::cout << rvalue << '\n';
    }
    template<typename T>
    void print(const T &lvalue)
    {
        std::cout << lvalue << '\n';
    }


    template<typename T, std::size_t N>
    class Array
    {
    private:
        T m_array[N];

    public:
        Array() : m_array()
        {}
        ~Array()
        {}

    public:
        std::size_t size() const { return N; }
        T &operator[](std::size_t i)             { return m_array[i]; }
        const T &operator[](std::size_t i) const { return m_array[i]; }
    };


    template<typename T>
    class Vector
    {
    private:
        T *m_data = nullptr;
        std::size_t m_size = 0;
        std::size_t m_capacity = 0;

    public:
        Vector() : m_data(), m_size(), m_capacity()
        {
            //allocate a block of memory for 2 elements
            ReAlloc(2);
        }
        ~Vector()
        {
            //deallocate all memory
            delete[] m_data;
        }

    public:
        void pushback(const T &newelement)
        {
            if (m_size >= m_capacity) {
                ReAlloc(m_capacity*2);
            }
            m_data[m_size] = newelement;
            m_size++;
        }
        void pushback(T &&newelement)
        {
            if (m_size >= m_capacity) {
                ReAlloc(m_capacity*2);
            }
            m_data[m_size] = std::move(newelement);
            m_size++;
        }
        std::size_t size() const { return m_size; }
        T &operator[](std::size_t i)             { return m_data[i]; }
        const T &operator[](std::size_t i) const { return m_data[i]; }

    private:
        void ReAlloc(std::size_t newcapacity)
        {
            if (newcapacity < m_size) {
                m_size = newcapacity;
            }
            //1. allocate a new block of memory
            //2. copy or better yet move old elements into new block
            //3. delete old block
            T *newblock = new T[newcapacity];
            for (std::size_t i=0; i<m_size; i++) {
                newblock[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = newblock;
            m_capacity = newcapacity;
            print("Allocating New Block");
        }
    };


    template<typename T, std::size_t N>
    void print_array(const Array<T, N> &array)
    {
        std::cout << "--------------------------------------\n";
        for (std::size_t i=0; i<array.size(); i++) {
            print(array[i]); //Type
        }
        std::cout << "--------------------------------------\n";
    }
    template<std::size_t N>
    void print_array(const Array<String, N> &array)
    {
        std::cout << "--------------------------------------\n";
        for (std::size_t i=0; i<array.size(); i++) {
            array[i].print(); //String
        }
        std::cout << "--------------------------------------\n";
    }


    template<typename T>
    void print_vector(const Vector<T> &vector)
    {
        std::cout << "--------------------------------------\n";
        for (std::size_t i=0; i<vector.size(); i++) {
            print(vector[i]); //Type
        }
        std::cout << "--------------------------------------\n";
    }
    void print_vector(const Vector<String> &vector)
    {
        std::cout << "--------------------------------------\n";
        for (std::size_t i=0; i<vector.size(); i++) {
            vector[i].print(); //String
        }
        std::cout << "--------------------------------------\n";
    }
}


int main()
{
    std::size_t i;
    templates::Array<int, 3> A = templates::Array<int, 3>();
    templates::Vector<int> B = templates::Vector<int>();
    templates::Array<String, 3> C = templates::Array<String, 3>();
    templates::Vector<String> D = templates::Vector<String>();

    templates::print(5);
    templates::print(5.5F);
    templates::print(5.7);
    templates::print("Hello!");

    templates::print_array(A);
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    templates::print_array(A);

    templates::print_vector(B);
    B.pushback(1);
    B.pushback(2);
    B.pushback(3);
    B.pushback(4);
    B.pushback(5);
    B.pushback(6);
    templates::print_vector(B);

    templates::print_array(C);
    C[0] = "abc";
    C[1] = "def";
    C[2] = "123";
    templates::print_array(C);

    templates::print_vector(D);
    D.pushback("abc");
    D.pushback("def");
    D.pushback("123");
    templates::print_vector(D);

    terminal::log("endprogram");
    return 0;
}