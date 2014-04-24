#include <cstdio>
#include "MyClass.h"

MyClass::MyClass()
{
    a = -1;
    b = -2;
    c = -3;
}

MyClass::MyClass(std::initializer_list<int> list)
{
    auto it = list.begin();
    a = *(it++);
    b = *(it++);
    c = *(it++);
}

void MyClass::PrintMembers()
{
    printf("a = %d\nb = %d\nc = %d\n", a, b, c);
}
