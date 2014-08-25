#include <cstdio>
#include <exception>

using namespace std;

struct my_exception : public exception
{
    int data;
    my_exception(int _data): data(_data) {};
    const char * what () const throw ()
    {
	return "C++ Exception";
    }
};

void func_throws()
{
    printf("Throwing exception\n");
    throw my_exception(747); //"Simple throw\n";
}

int main()
{
    try
    {
	func_throws();
    }
    catch (const char* msg)
    {
	printf("%s", msg);
    }
    catch (my_exception &e)
    {
	printf("Caught: %s with parameter [%d]\n", e.what(), e.data);
    }
    catch (...)
    {
	printf("Default exception\n");
    }   
    return 0;
}
