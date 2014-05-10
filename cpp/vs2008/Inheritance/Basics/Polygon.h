#ifndef POLYGON_H_
#define POLYGON_H_

class Polygon
{
protected:
	int width, height;
public:
	Polygon();
	Polygon(int a, int b);
	~Polygon();
	void set_values (int a, int b);
};

#endif