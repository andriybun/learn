#include <string>
#include <cstdio>

class Computer
{
public:
    virtual void Run() = 0;
    virtual void Stop() = 0;
    virtual void Say()
    {
	printf("I'm computer\n");
    }
};

class Laptop: public Computer
{
public:
    virtual void Run(){mHibernating = false;}
    virtual void Stop(){mHibernating = true;}
    virtual void Say()
    {
	printf("I'm laptop\n");
    }    
private:
    bool mHibernating; // Whether or not the machine is hibernating
};

class Desktop: public Computer
{
public:
    virtual void Run(){mOn = true;}
    virtual void Stop(){mOn = false;}
    virtual void Say()
    {
	printf("I'm desktop\n");
    }
private:
    bool mOn; // Whether or not the machine has been turned on
};

class ComputerFactory
{
public:
    enum computerT
    {
	laptop,
	desktop
    };

    static Computer *NewComputer(computerT cType)
    {
	switch (cType)
	{
	case laptop:
	    return new Laptop;
	case desktop:
	    return new Desktop;
	}
	return NULL;
    }
};


int main()
{
    Computer* lp = new Laptop();
    Computer* desktop = ComputerFactory::NewComputer(ComputerFactory::desktop);
    desktop->Say();
    delete lp;
    return 0;
}
