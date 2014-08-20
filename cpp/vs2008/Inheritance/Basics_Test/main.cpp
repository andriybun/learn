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

#include <vector>
#include <algorithm>

bool is_prime(const int max)
{
	// We check numbers from 2 to sqrt(max). This is because if max can be
	// divided by i, then it can be divided by max / i. One of them must be 
	// less than or equal to sqrt(max). Thus time complexity of algorithm is
	// reduced from O(n) to O(sqrt(n))
	int i = 2;
	while (i * i <= max)
	{
		if (max % i == 0)
		{
			return false;
		}
		// First we check if 2 is divisor of max. If not we skip all even 
		// numbers. If any even number is divisor of max, then 2 is also its 
		// divisor
		i += (i == 2) ? 1 : 2;
	}	return true;}

void get_primes(std::vector<int> & output, const int max)
{
	// Clear the output vector, if passed not empty.
	// Another option would be to throw exception, but not sure if they are
	// allowed here according to guidelines
	if (!output.empty())
	{
		output.clear();
	}
	// Reserve enough memory for the output vector, to avoid further 
	// reallocations in case of very big max
	output.reserve(max);
	// Check all numbers from 2 to max for primality. Append all prime numbers
	// to output vector
	for (int i = 2; i <= max; i += (i == 2 ? 1 : 2))
	{
		if (is_prime(i))
		{
			output.push_back(i); 
		}
	}
}

void print_vector(const std::vector<int> & v)
{
	printf("Vector:\n");
	for (size_t i = 0; i < v.size(); i++)
	{
		printf("\t[%d] %d\n", i, v[i]);
	}
}

TEST(prime_zero_input, prime_test)
{
	std::vector<int> primes;
	EXPECT_NO_THROW(get_primes(primes, 0));
	EXPECT_TRUE(primes.empty());
}

TEST(prime_non_empty, prime_test)
{
	std::vector<int> primes(4, 0);
	EXPECT_NO_THROW(get_primes(primes, 10));
	EXPECT_EQ(primes.size(), 4);
}

TEST(prime_basic, prime_test)
{
	// TODO: test if all the returned numbers are prime
	std::vector<int> primes;
	get_primes(primes, 120);
	//print_vector(primes);

	std::sort(primes.begin(), primes.end());
	EXPECT_EQ(primes.size(), 30);
	EXPECT_EQ(primes[29], 113);

}
