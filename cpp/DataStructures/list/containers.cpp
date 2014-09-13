#include "stdafx.h"
#include "containers.h"

namespace containers
{
	template <class T>
	list<T>::list(void)
	{
		this->firstEl = NULL;
		this->lastEl = NULL;
		itEnd = iterator();
	}

	template <class T>
	list<T>::~list(void)
	{
		while (this->firstEl)
		{
			listEl* deleteMe = this->firstEl;
			this->firstEl = this->firstEl->addr;
			delete deleteMe;
		}
	}

	template <class T>
	void list<T>::print()
	{
		std::printf("List:\n");
		listEl* it = this->firstEl;
		while (it)
		{
			std::cout << it->data << std::endl;
			it = it->addr;
		}
	}

	template <class T>
	void list<T>::updateStart(listEl* newStart)
	{
		this->firstEl = newStart;
		this->itBegin = iterator(newStart);
	}

	template <class T>
	void list<T>::push(T data)
	{
		listEl* newEl = new listEl(NULL, data);
		if (!this->firstEl)
		{
			this->updateStart(newEl);
		}
		else
		{
			this->lastEl->addr = newEl;
		}
		this->lastEl = newEl;
	}

	template <class T>
	T list<T>::pop()
	{
		T result = this->firstEl->data;
		listEl* deleteMe = this->firstEl;
		this->updateStart(this->firstEl->addr);
		delete deleteMe;
		return result;
	}

	template<class T>
	void list<T>::reverse()
	{
		listEl* prev = NULL;
		listEl* curr = this->firstEl;
		this->lastEl = this->firstEl;
		while (curr)
		{
			listEl* next = curr->addr;
			curr->addr = prev;
			prev = curr;
			curr = next;
		}
		this->updateStart(prev);
	}

	template <class T>
	list<T>::iterator::iterator()
	{
		this->el = NULL;
	}

	template <class T>
	list<T>::iterator::iterator(listEl* ptr)
	{
		this->el = ptr;
	}

	template <class T>
	list<T>::iterator::iterator(const typename list<T>::iterator & other)
	{
		this->el = other.el;
	}

	template <class T>
	typename list<T>::iterator & list<T>::iterator::operator= (const typename list<T>::iterator & rhs)
	{
		if (this != &rhs)
		{
			this->el = rhs.el;
		}
		return *this;
	}

	template <class T>
	list<T>::iterator::~iterator()
	{
	}

	template <class T>
	bool list<T>::iterator::operator== (const typename list<T>::iterator & rhs)
	{
		return (this->el == rhs.el);
	}

	template <class T>
	bool list<T>::iterator::operator!= (const typename list<T>::iterator & rhs)
	{
		return (this->el != rhs.el);
	}

	template <class T>
	T list<T>::iterator::operator* () const
	{
		return (*this).el->data;
	}

	template <class T>
	typename list<T>::iterator & list<T>::iterator::operator++ ()
	{
		this->el = this->el->addr;
		return *this;
	}
	
	template <class T>
	void list<T>::iterator::operator++ (int)
	{
		this->el = this->el->addr;		
	}

	template <class T>
	const typename list<T>::iterator & list<T>::begin()
	{
		return itBegin;
	}

	template <class T>
	const typename list<T>::iterator & list<T>::end()
	{
		return itEnd;
	}

	//////////////////////////////////////////////////////////////////////////
	// Stack
	//////////////////////////////////////////////////////////////////////////

	template <class T>
	stack<T>::stack(void)
	{
		this->updateTop(NULL);
	}

	template <class T>
	stack<T>::~stack(void)
	{
		while (this->topEl)
		{
			listEl* deleteMe = this->topEl;
			this->updateTop(this->topEl->addr);
			delete deleteMe;
		}
	}

	template <class T>
	void stack<T>::updateTop(listEl* newTop)
	{
		this->topEl = newTop;
		//this->itBegin = iterator(newTop);
	}

	template <class T>
	void stack<T>::print()
	{
		listEl* curr = this->topEl;
		printf("Stack:\n");
		while (curr)
		{
			std::cout << curr->data << std::endl;
			curr = curr->addr;
		}
	}

	template <class T>
	void stack<T>::push(T data)
	{
		listEl* newEl = new listEl(this->topEl, data);
		this->updateTop(newEl);
	}

	template <class T>
	T stack<T>::pop()
	{
		T result = this->topEl->data;
		listEl* deleteMe = this->topEl;
		this->updateTop(this->topEl->addr);
		delete deleteMe;
		return result;
	}

	template <class T>
	void stack<T>::reverse()
	{
		listEl* prev = NULL;
		listEl* curr = this->topEl;
		while (curr)
		{
			listEl* next = curr->addr;
			curr->addr = prev;
			prev = curr;
			curr = next;
		}
		this->updateTop(prev);
	}

	template class baseList<int>;
	template class list<int>;
	template class stack<int>;
}
