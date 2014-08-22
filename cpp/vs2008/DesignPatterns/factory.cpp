#include <string>
#include <cstdio>

class Computer
{
public:
    virtual void Run() = 0;
    virtual void Stop() = 0;
};

class Laptop: public Computer
{
public:
    virtual void Run(){mHibernating = false;}
    virtual void Stop(){mHibernating = true;}
private:
    bool mHibernating; // Whether or not the machine is hibernating
};

class Desktop: public Computer
{
public:
    virtual void Run(){mOn = true;}
    virtual void Stop(){mOn = false;}
private:
    bool mOn; // Whether or not the machine has been turned on
};

class ComputerFactory
{
public:
    static Computer *NewComputer(const std::string &description)
    {
	if(description == "laptop")
	    return new Laptop;
	if(description == "desktop")
	    return new Desktop;
	return NULL;
    }
};


int main()
{
    Computer * lp = new Laptop();
    delete lp;
    return 0;
}
