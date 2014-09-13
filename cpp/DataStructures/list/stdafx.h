// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <algorithm>
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <vector>

#include "containers.h"

template <class T>
void vectorSort(std::vector<T> &v);

template <class T>
void vectorSort(std::vector<T> &v, std::vector<size_t> &idx);

template <class T>
bool operator== (const std::vector<T> &v1, const std::vector<T> &v2)
{
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	if (s1 != s2) return false;
	for (size_t i = 0; i < s1; i++)
	{
		if (v1[i] != v2[i]) return false;
	}
	return true;
}

template<class T>
void printStl(const T &c)
{
	printf("Container:\n");
	for (typename T::const_iterator i = c.begin(); i != c.end(); ++i)
	{
		printf("  %d\n", *i);
	}
}

std::list<int> findPathR(const std::vector<std::vector<int> > &adjacencyMatrix, int start, int finish);
std::list<int> findPath(std::vector<std::vector<int> > &adjacencyMatrix, int start, int finish);
