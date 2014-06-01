#ifndef POLYGON_H_
#define POLYGON_H_

#include <iostream>
#include <string>

class polygon
{
protected:
	std::string name;
	int width, height;
public:
	polygon();
	polygon(int width_, int height_);
	~polygon();
	void set_sides(int width_, int height_);
	void set_width(int width_);
	void set_height(int height_);
	std::string get_name();
};

class properties_printer
{
public:
	virtual void print_properties() {};
};

template<class real_t>  
class rectangle : public polygon, public properties_printer
{
public:
	rectangle() : polygon() {name = "Rectangle";};
	rectangle(int width_, int height_) : polygon(width_, height_) {name = "Rectangle";};
	real_t get_area();
	void print_properties();
};

#endif