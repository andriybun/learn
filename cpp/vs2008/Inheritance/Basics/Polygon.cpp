#include "Polygon.h"

Polygon::Polygon(void)
{
	width = 1;
	height = 1;
}

Polygon::Polygon(int a, int b)
{
	width = a;
	height = b;
}

Polygon::~Polygon(void)
{
}

void Polygon::set_values (int a, int b)
{
	width = a;
	height = b;
}