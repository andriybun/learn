#pragma once

#include <iostream>

namespace containers
{
	template <class T>
	class baseList
	{
	protected:
		struct listEl
		{
			T data;
			listEl* addr;
			listEl(listEl* addr, T data): addr(addr), data(data) {};
		};
	public:
		baseList(void) {};
		~baseList(void) {};
		virtual void print() = 0;
		virtual void push(T data) = 0;
		virtual T pop() = 0;
		virtual void reverse() = 0;
	};

	template <class T>
	class list : public baseList<T>
	{
		listEl* firstEl;
		listEl* lastEl;
		void updateStart(listEl* newStart);
	public:
		list(void);
		~list(void);
		void print();

		void push(T data);
		T pop();
		void reverse();

		class iterator
		{
		private:
			listEl* el;
		public:
			iterator();
			iterator(listEl * ptr);
			iterator(const iterator & other);
			iterator & operator= (const iterator & rhs);
			~iterator();
			bool operator== (const iterator & rhs);
			bool operator!= (const iterator & rhs);
			T operator* () const;
			iterator & operator++ ();
			void operator++ (int);
		};

		const iterator & begin();
		const iterator & end();
	private:
		iterator itBegin, itEnd;
	};

	template <class T>
	class stack : public baseList<T>
	{
		listEl* topEl;
		void updateTop(listEl* newTop);
	public:
		stack(void);
		~stack(void);
		void print();

		void push(T data);
		T pop();
		void reverse();

	//	class iterator
	//	{
	//	private:
	//		listEl* el;
	//	public:
	//		iterator();
	//		iterator(listEl * ptr);
	//		iterator(const iterator & other);
	//		iterator & operator= (const iterator & rhs);
	//		~iterator();
	//		bool operator== (const iterator & rhs);
	//		bool operator!= (const iterator & rhs);
	//		T operator* () const;
	//		iterator & operator++ ();
	//		void operator++ (int);
	//	};

	//	const iterator & begin();
	//	const iterator & end();
	//private:
	//	iterator itTop;
	};


}
