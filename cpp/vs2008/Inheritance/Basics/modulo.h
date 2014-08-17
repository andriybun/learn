#pragma once
#include <climits>

class modulo
{
private:
	int mod;
	int value;

	void checkOverflow();
public:
	modulo(void);
	modulo(int val, int md);
	modulo(const modulo & other);
	modulo & operator= (const modulo & rhs);
	modulo & operator= (const int rhs);

	~modulo(void);

	modulo & operator+ (const modulo & other);
	modulo & operator+ (const int other);
	modulo & operator- (const modulo & other);
	modulo & operator- (const int other);
	modulo & operator* (const modulo & other);
	modulo & operator* (const int other);
	modulo & operator+= (const modulo & other);
	modulo & operator+= (const int other);
	modulo & operator-= (const modulo & other);
	modulo & operator-= (const int other);
	modulo & operator*= (const modulo & other);
	modulo & operator*= (const int other);

	friend modulo operator+ (const int val, const modulo & other);
	friend modulo operator- (const int val, const modulo & other);
	friend modulo operator* (const int val, const modulo & other);

	int getValue() const;
};
