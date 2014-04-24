#include <cstdio>
#include "MyClass.h"

int main()
{
    int my_array[5] = {1, 2, 3, 4, 5};

    // double the value of each element in my_array:
    for (int &x : my_array) 
    {
     	x *= 2;
    }

    for (int &x : my_array)
    {
        printf("%d\n", x);
    }

    MyClass myObj {1, 2, 3};
    myObj.PrintMembers();
}
