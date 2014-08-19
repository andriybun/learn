#include "modulo.h"

modulo::modulo(void)
{
	this->mod = INT_MAX;
	this->value = 1;
}


modulo::modulo(int val, int md)
{
	this->mod = md;
	this->value = val;
	checkOverflow();
}

modulo::modulo(const modulo & other)
{
	this->mod = other.mod;
	this->value = other.value;
	checkOverflow();
}

modulo & modulo::operator= (const modulo & rhs)
{
	if (this != &rhs)
	{
		this->mod = rhs.mod;
		this->value = rhs.value;
		checkOverflow();
	}
	return *this;
}

modulo & modulo::operator= (const int rhs)
{
	this->value = rhs;
	checkOverflow();
	return *this;
}
modulo & modulo::operator+ (const modulo & other)
{
	this->value = (this->value + other.value) % this->mod;
	return *this;
}

modulo & modulo::operator+ (const int other)
{
	this->value = (this->value + other) % this->mod;
	return *this;
}

modulo & modulo::operator- (const modulo & other)
{
	this->value = (this->value - other.value) % this->mod;
	return *this;
}

modulo & modulo::operator- (const int other)
{
	this->value = (this->value - other) % this->mod;
	return *this;
}

modulo & modulo::operator* (const modulo & other)
{
	this->value = (this->value * other.value) % this->mod;
	return *this;
}

modulo & modulo::operator* (const int other)
{
	this->value = (this->value * other) % this->mod;
	return *this;
}

modulo & modulo::operator+= (const modulo & other)
{
	*this = *this + other;
	return *this;
}

modulo & modulo::operator+= (const int other)
{
	*this = *this + other;
	return *this;
}

modulo & modulo::operator-= (const modulo & other)
{
	*this = *this - other;
	return *this;
}

modulo & modulo::operator-= (const int other)
{
	*this = *this - other;
	return *this;
}

modulo & modulo::operator*= (const modulo & other)
{
	*this = *this * other;
	return *this;
}

modulo & modulo::operator*= (const int other)
{
	*this = *this * other;
	return *this;
}

modulo::~modulo(void)
{

}

void modulo::checkOverflow()
{
	if (this->value > this->mod)
	{
		this->value = this->value % this->mod;
	}
}

int modulo::getValue() const
{
	return this->value;
}

modulo operator+ (const int val, const modulo & right)
{
	modulo left(val, right.mod);
	return modulo(left + right);
}

modulo operator- (const int val, const modulo & right)
{
	modulo left(val, right.mod);
	return modulo(left - right);
}

modulo operator* (const int val, const modulo & right)
{
	modulo left(val, right.mod);
	return modulo(left * right);
}