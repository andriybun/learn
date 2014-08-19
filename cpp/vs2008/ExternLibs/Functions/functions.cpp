// Functions.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "functions.h"

#include <stdexcept>

using namespace std;

const double EPSILON = 1e-9;

inline double xmin(double a, double b)
{
	return (a < b ? a : b);
}

inline double xmax(double a, double b)
{
	return (a > b ? a : b);
}

double MathFuncs::Add(double a, double b)
{
	return a + b;
}

double MathFuncs::Subtract(double a, double b)
{
	return a - b;
}

double MathFuncs::Multiply(double a, double b)
{
	return a * b;
}

double MathFuncs::Divide(double a, double b)
{
	if (b == 0)
	{
		throw invalid_argument("b cannot be zero!");
	}

	return a / b;
}

double MathFuncs::Integral(double (*func)(double), double a, double b, double h)
{
	if (h <= 0)
	{
		throw invalid_argument("Integration step cannot be zero!");
	}
	if (a > b)
	{
		throw invalid_argument("Integration interval specified incorrectly!");
	}

	double x = a;
	double s = 0;
	while (x < b - EPSILON)
	{
		double nextX = xmin(x + h, b);
		s += (func(x) + func(nextX)) / 2 * h;
		x = nextX;
	}
	return s;
}