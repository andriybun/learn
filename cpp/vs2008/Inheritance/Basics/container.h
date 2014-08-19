#pragma once

template <class T>
class container
{
protected:
	size_t size;
public:
	container(void);
	virtual ~container(void);

	size_t getSize() const;
	virtual void print() const;
};

template <class T>
class vector : public container<T>
{
public:
	class iterator
	{
	private:
		T * el;
	public:
		iterator();
		iterator(T * ptr);
		iterator(const iterator & other);
		iterator & operator= (const iterator & rhs);
		~iterator();
		bool operator== (const iterator & rhs);
		bool operator!= (const iterator & rhs);
		T operator* () const;
		iterator & operator++ ();
		void operator++ (int);
		iterator & operator-- ();
		void operator-- (int);
	};
protected:
	bool isAllocated;
	int * data;
	iterator itBegin, itEnd;
public:
	vector();
	vector(int num, T val = 0);
	virtual ~vector();

	const iterator & begin();
	const iterator & end();
	T & operator[] (size_t idx);

	virtual void print() const;

};