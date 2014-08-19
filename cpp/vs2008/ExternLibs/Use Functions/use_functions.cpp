#include "functions.h"
#include "use_functions.h"

using namespace std;

double f(double x)
{
	return x;
}

int main(int argc, char* argv[])
{
	double a = 7.4;
	int b = 99;

	cout << "a + b = " << dll::MathFuncs::Add(a, b) << endl;
	cout << "a - b = " << dll::MathFuncs::Subtract(a, b) << endl;
	cout << "a * b = " << dll::MathFuncs::Multiply(a, b) << endl;
	cout << "a / b = " << dll::MathFuncs::Divide(a, b) << endl;

	try
	{
		cout << "a / 0 = " << dll::MathFuncs::Divide(a, 0) << endl; 
	}
	catch (const invalid_argument &e) 
	{
		cout << "Caught exception: " << e.what() << endl; 
	}

	cout << "Integral = " << dll::MathFuncs::Integral(&f, 1, 2, 1e-2) << endl;

	return 0;
}