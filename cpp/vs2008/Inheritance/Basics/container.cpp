#include <iostream>
#include "container.h"

//////////////////////////////////////////////////////////////////////////
// Container class (base)
//////////////////////////////////////////////////////////////////////////

template <class T>
container<T>::container(void)
{
	this->size = 0;
}

template <class T>
container<T>::~container(void)
{
}

template <class T>
size_t container<T>::getSize() const
{
	return this->size;
}

template <class T>
void container<T>::print() const
{
	printf("> I'm container. My size is: %d\n", size);
}


//////////////////////////////////////////////////////////////////////////
// Vector class
//////////////////////////////////////////////////////////////////////////

template <class T>
vector<T>::vector(void)
{
	this->isAllocated = false;
	this->size = 0;
	itBegin = itEnd = vector<T>::iterator(0);
}

template <class T>
vector<T>::vector(int num, T val = 0)
{
	this->data = new T[num];
	this->isAllocated = true;
	this->size = num;
	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] = val;
	}
	itBegin = vector<T>::iterator(data);
	itEnd = vector<T>::iterator(data+this->size);
}

template <class T>
vector<T>::~vector(void)
{
	if (isAllocated)
	{
		delete [] data;
	}
}

template <class T>
typename const vector<T>::iterator & vector<T>::begin()
{
	return itBegin;
}

template <class T>
typename const vector<T>::iterator & vector<T>::end()
{
	return itEnd;
}

template <class T>
void vector<T>::print() const
{
	printf("> I'm vector. My size is: %d\n", size);
	if (isAllocated)
	{
		printf("> I contain following data:\n");
		for (size_t i = 0; i < this->size; i++)
		{
			printf("       %d\n", this->data[i]);
		}
	}
}

// Vector's iterator
template <class T>
vector<T>::iterator::iterator()
{
	this->el = NULL;
}

template <class T>
vector<T>::iterator::iterator(T* ptr)
{
	this->el = ptr;
}

template <class T>
vector<T>::iterator::iterator(const typename vector<T>::iterator & other)
{
	this->el = other.el;
}

template <class T>
typename vector<T>::iterator & vector<T>::iterator::operator= (const typename vector<T>::iterator & rhs)
{
	if (this != &rhs)
	{
		this->el = rhs.el;
	}
	return *this;
}

template <class T>
vector<T>::iterator::~iterator()
{

}

template <class T>
T & vector<T>::operator[] (size_t idx)
{
	return data[idx];
}

template <class T>
bool vector<T>::iterator::operator== (const typename vector<T>::iterator & rhs)
{
	return (this->el == rhs.el);
}

template <class T>
bool vector<T>::iterator::operator!= (const typename vector<T>::iterator & rhs)
{
	return (this->el != rhs.el);
}

template <class T>
T vector<T>::iterator::operator* () const
{
	return *(this->el);
}

template <class T>
typename vector<T>::iterator & vector<T>::iterator::operator++ ()
{
	(this->el)++;
	return *this;
}

template <class T>
void vector<T>::iterator::operator++ (int)
{
	++(*this);
}

template <class T>
typename vector<T>::iterator & vector<T>::iterator::operator-- ()
{
	(this->el)--;
	return *this;
}

template <class T>
void vector<T>::iterator::operator-- (int)
{
	--(*this);
}


// Instantiate
template class container<int>;
template class vector<int>;