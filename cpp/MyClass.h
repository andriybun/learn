#include <initializer_list>

class MyClass {
private:
    int a;
    int b;
    int c;
public:
    MyClass();
    MyClass(std::initializer_list<int> list);
    void PrintMembers();
};

