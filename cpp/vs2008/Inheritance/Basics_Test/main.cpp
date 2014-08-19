#include <iostream>
#include "gtest/gtest.h"

#include "polygon.h"
#include "modulo.h"
#include "container.h"

TEST(rectangleTest, TestRectangleArea)
{
	int width = 3;
	int height = 4;
	rectangle<float> rect(width, height);
	EXPECT_EQ(rect.get_area(), width * height);

	rect.print_properties();
}

TEST(moduloTest, testBasicOperations)
{
	int tmp = 2;
	modulo v(tmp, 27);

	// Simple tests
	v += 25;
	EXPECT_EQ(v.getValue(), 0);

	modulo u(47 + v);
	EXPECT_EQ(u.getValue(), 20);

	modulo w(50 - modulo(48, 27));
	EXPECT_EQ(w.getValue(), 2);

	v = 35;
	w = 37;
	u = v * w;

	EXPECT_EQ(u.getValue(), 26);

	// TODO: check if same modulo of operands
	//
}

TEST(containerTest, testInheritance)
{
	container<int> parent;
	parent.print();
	vector<int> vec(6, 11);
	vec.print();
	vec[0] = 94;
	vec[2] = 123;
	vector<int>::iterator it = vec.begin();
	while(it != vec.end())
	{
		printf("%d\n", *it);
		it++;
	}
}

TEST(vehiclesTest, testInheritance)
{
	vehicle* bmw = new car;
	bmw->print();
	vehicle* bombardier = new boat;
	bombardier->print();
	vehicle* luaz = new amphibian;
	luaz->print();
}

int main(int argc, char **argv)
{
	//int width = 3;
	//int height = 4;
	//rectangle<float> rect(width, height);
	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}