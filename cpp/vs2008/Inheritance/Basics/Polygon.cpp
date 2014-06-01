#include "Polygon.h"


//////////////////////////////////////////////////////////////////////////
// Polygon class
//////////////////////////////////////////////////////////////////////////

polygon::polygon(void)
{
	set_sides(1, 1);
}

polygon::polygon(int width_, int height_)
{
	set_sides(width_, height_);
}

polygon::~polygon(void)
{
}

void polygon::set_sides(int width_, int height_)
{
	set_width(width_);
	set_height(height_);
}

std::string polygon::get_name()
{
	return name;
}

void polygon::set_width(int width_)
{
	width = width_;
}

void polygon::set_height(int height_)
{
	height = height_;
}


//////////////////////////////////////////////////////////////////////////
// Derived classes
//////////////////////////////////////////////////////////////////////////
template <class real_t>
real_t rectangle<real_t>::get_area()
{
	return (real_t)width * (real_t)height;
}

template <class real_t>
void rectangle<real_t>::print_properties()
{
	std::cout << "***** Printing properties *****" << std::endl;
	std::cout << "My name is " << name << std::endl;
	std::cout << "My height is: " << height << std::endl;
	std::cout << "My width is:  " << width << std::endl;
}

template class rectangle<float>;
template class rectangle<double>;