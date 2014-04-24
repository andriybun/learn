#include <cstdio>
#include <iostream>

class base
{
private:
    int val;
public:
    base(): val(0) {};
    base(int v): val(v) {};
    int getVal() {return val;};
    virtual
    void saySomething();
};

void base::saySomething()
{
    printf("base class: val = %d\n", getVal());
}

class derived : public base
{
private:
    
public:
    derived(int v): base(v) {};
    virtual
    void saySomething() {printf("derived class: val = %d\n", getVal());};
};

int main()
{
    derived * dInst = new derived(1);
    base * bInst = dInst;
    bInst->saySomething();
    dInst->saySomething();
    delete dInst;
}
