#include <cstdio>
#include <iostream>

struct s
{
    int a, b, c;
    s(int ax, int bx, int cx): a(ax), b(bx), c(cx) {}
};

int main()
{
    int a = 5;
    std::cout << &a << std::endl;
    auto func = [&] () {std::cout << a << std::endl; std::cout << &a << std::endl;};
    func();
    std::cout << a << std::endl;
    s sInst(1, 2, 3);

}
