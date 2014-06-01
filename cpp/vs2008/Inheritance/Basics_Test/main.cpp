#include <iostream>
#include "gtest/gtest.h"

#include "Polygon.h"

class rectangleTest : public ::testing::Test 
{
protected:
	virtual void SetUp() 
	{
		
	}

	rectangle<float> rect;
};

TEST_F(rectangleTest, TestRectangleArea)
{
	int width = 3;
	int height = 4;
	rectangle<float> rect(width, height);
	EXPECT_EQ(rect.get_area(), width * height);
	EXPECT_EQ(rect.get_area(), 2);
}

int main(int argc, char **argv)
{
	int width = 3;
	int height = 4;
	rectangle<float> rect(width, height);
	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

//int main(int argc, char **argv)
//{
//	rectangle<float> rect(4, 5);
//	std::cout << "The area of rectangle is: " << rect.get_area() << std::endl;
//	std::cout << "My name is " << rect.get_name() << std::endl;
//	rect.print_properties();
//	return 0;
//}