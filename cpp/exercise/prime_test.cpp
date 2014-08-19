#include <vector>
#include <algorithm>
#include <climits>
#include "gtest/gtest.h"

bool is_prime(const int max)
{
    // Simple cases: 1 and less are not primes
    if (max <= 1) return false;
    // Even numbers: only 2 is prime
    if (max % 2 == 0)
    {
	return max == 2;
    }
    // Next we check all odd numbers until sqrt(max). This is because if max 
    // can be divided by i, then it can be divided by max / i. One of them must 
    // be less than or equal to sqrt(max). Thus time complexity of algorithm is
    // reduced from O(n) to O(sqrt(n))
    unsigned int i = 3;
    while (i * i <= max)
    {
        if (max % i == 0)
        {
            return false;
        }
        i += 2;
    }
    return true;
}

namespace option
{
    void get_primes(std::vector<int> & output, const int max)
    {
	// Clear the output vector, if passed not empty.
	// Another option would be to throw exception, but not sure if they are
	// allowed here according to guidelines
	if (!output.empty())
	    {
		output.clear();
	    }
	// Check all numbers from 2 to max for primality. Append all prime numbers
	// to output vector
	for (unsigned int i = 2; i <= max; i += (i == 2 ? 1 : 2))
	    {
		if (is_prime(i))
		    {
			output.push_back(i); 
		    }
	    }
    }
}

inline int calc_sieve_idx(int i)
{
    return (i - 3) / 2;
}

void get_primes(std::vector<int> & output, const int max)
{
    // Clear the output vector, if passed not empty.
    // Another option would be to throw exception, but not sure if they are
    // allowed here according to guidelines
    if (!output.empty())
    {
        output.clear();
    }
    // Prime numbers can only be greater than 1
    if (max < 2) return;
    // 2 is a prime number
    output.push_back(2);
    // Initialize sieve of Eratosthenes vector. To save memory, I use it only 
    // for odd numbers starting with 3. As even numbers are not prime per se. 
    // Its elements can take values: 0 - corresponding number is composite, 
    // 1 - the number is prime
    std::vector<char> sieve(max / 2 - 1, 1);
    unsigned int i = 3;
    // The idea is to find out all primes until sqrt(max) and filter out all
    // their multiples. Multiples of prime numbers greater than sqrt(max) 
    // will not affect the result. Thus time complexity of this part of the 
    // algorithm is reduced from O(n) to O(sqrt(n))
    while (i * i <= max)
    {
	// Here I use function sieve_idx to find for every given number its 
	// index in the sieve vector. 
	if (sieve[calc_sieve_idx(i)])
	{
	    // If sieve[sieve_idx(i)] is one at this point, this means, that
	    // i is a prime number. It is appended to the output vector.
	    output.push_back(i);
	    unsigned int k = i * i;
	    // I also filter out all multiples of i by setting corresponding 
	    // elements of sieve vector to zeros
	    while (k <= max)
	    {
		if (k % 2 != 0) sieve[calc_sieve_idx(k)] = 0;
		k += i;
	    }
	}
	i += 2;
    }
    // Having done the previous part, the algorithm for filling sieve of 
    // Eratosthenes is completed. Now only filling the vector with result
    // by running through sieve and finding out numbers ones, which 
    // correspond to prime numbers
    unsigned int sieve_idx = calc_sieve_idx(i);
    while (i <= max)
    {
	if (sieve[sieve_idx])
	{
	    output.push_back(i);
	}
	sieve_idx++;
	i += 2;
    }
}

TEST(prime_test, empty_output)
{
    // Check if function works fine for numbers less than 2. In such case 
    // empty vector must be returned
    std::vector<int> primes1, primes0, primesMin;
    EXPECT_NO_THROW(get_primes(primes1, 1));
    EXPECT_TRUE(primes1.empty());
    EXPECT_NO_THROW(get_primes(primes0, 0));
    EXPECT_TRUE(primes0.empty());
}

TEST(prime_test, non_empty_input)
{
    // Check what happens, if output vector is not empty. In case of
    // exceptions macro EXPECT_THROW would be used
    std::vector<int> primes(4, 0);
    EXPECT_NO_THROW(get_primes(primes, 10));
    EXPECT_EQ(primes.size(), 4);
}

TEST(prime_test, basic)
{
    std::vector<int> primes;
    get_primes(primes, 120);

    std::sort(primes.begin(), primes.end());
    EXPECT_EQ(primes.size(), 30);
    EXPECT_EQ(primes[29], 113);

    for (size_t i = 0; i < primes.size(); i++)
    {
	EXPECT_TRUE(is_prime(primes[i]));
    }

}

TEST(prime_test, speed)
{
    std::vector<int> primes;
    EXPECT_NO_THROW(get_primes(primes, 10000000));
}

TEST(prime_test, speed_optional)
{
    std::vector<int> primes;
    EXPECT_NO_THROW(option::get_primes(primes, 10000000));
}

TEST(prime_test, stress)
{
    std::vector<int> primesMin, primesMax;
    EXPECT_NO_THROW(get_primes(primesMin, INT_MIN));
    EXPECT_TRUE(primesMin.empty());
    EXPECT_NO_THROW(get_primes(primesMax, INT_MAX));
    EXPECT_FALSE(primesMax.empty());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
