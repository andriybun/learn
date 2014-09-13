// stdafx.cpp : source file that includes just the standard includes
// list.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

template <class T>
void mergeSorted(std::vector<T> &v, int iBegin, int iMiddle, int iEnd, std::vector<size_t> &idx)
{
	// Function merges two previously sorted parts of vector v, so that the 
	// result is also sorted:
	// first starting with index iBegin and ending with iMiddle-1
	// second starting with index iMiddle and ending with iEnd-1
	
	// Vector to store merge sorted elements
	std::vector<T> vr(v.size());
	std::vector<size_t> idxr(idx);
	bool calcIdx = !idx.empty();

	// Indices to iterate over left and right parts of array respectively
	int i1 = iBegin, i2 = iMiddle;
	for (int j = iBegin; j < iEnd; j++)
	{
		if ((i2 == iEnd) || ((i1 < iMiddle) && (v[i1] < v[i2])))
		{
			if (calcIdx)
			{
				idxr[j] = idx[i1];
			}
			vr[j] = v[i1++];
		}
		else
		{
			if (calcIdx)
			{
				idxr[j] = idx[i2];
			}
			vr[j] = v[i2++];
		}
	}
	// Copy sorted elements to input vector
	for (int j = iBegin; j < iEnd; j++)
	{
		if (calcIdx)
		{
			idx[j] = idxr[j];
		}
		v[j] = vr[j];
	}
}

template <class T>
void split(std::vector<T> &v, int iBegin, int iEnd, std::vector<size_t> &idx = std::vector<size_t>())
{
	// The function splits vector v into two parts with (almost) equal sizes. Then calls itself recursively
	// for the divided parts. If input vector contains less than 2 elements - it's considered sorted.
	// After the algorithm exits from the recursive function, the corresponding part is already sorted.
	// Now we need to merge two sorted parts of an array.
	if (iEnd - iBegin < 2)
	{
		return;
	}
	int iMiddle = (iBegin + iEnd) / 2;
	split<T>(v, iBegin, iMiddle, idx);
	split<T>(v, iMiddle, iEnd, idx);
	mergeSorted<T>(v, iBegin, iMiddle, iEnd, idx);
}

template <class T>
void vectorSort(std::vector<T> &v)
{
	split<T>(v, 0, v.size());
}

template <class T>
void vectorSort(std::vector<T> &v, std::vector<size_t> &idx)
{
	if (!idx.empty()) throw "Error: index vector not empty";
	idx.resize(v.size());
	for (size_t i = 0; i < idx.size(); i++)
	{
		idx[i] = i;
	}
	split<T>(v, 0, v.size(), idx);
}

template void vectorSort<int>(std::vector<int> &v);
template void vectorSort<long long>(std::vector<long long> &v);
template void vectorSort<float>(std::vector<float> &v);
template void vectorSort<double>(std::vector<double> &v);

template void vectorSort<int>(std::vector<int> &v, std::vector<size_t> &idx);
template void vectorSort<long long>(std::vector<long long> &v, std::vector<size_t> &idx);
template void vectorSort<float>(std::vector<float> &v, std::vector<size_t> &idx);
template void vectorSort<double>(std::vector<double> &v, std::vector<size_t> &idx);

//////////////////////////////////////////////////////////////////////////
// Graph
//////////////////////////////////////////////////////////////////////////

std::list<int> findPathRecursive(const std::vector<std::vector<int> > &adjacencyMatrix, int start, int finish)
{
	static std::list<int> path, shortPath;
	size_t nVertices = adjacencyMatrix.size();
	static std::vector<int> distanceToVertice(nVertices, -1);
	if (distanceToVertice[start] == -1)
	{
		distanceToVertice[start] = 0;
	}
	path.push_back(start);
	for (size_t i = 0; i < nVertices; i++)
	{
		if (i != start)
		{
			if ((adjacencyMatrix[start][i] > 0) &&
				((distanceToVertice[i] == -1) ||
				(distanceToVertice[i] > distanceToVertice[start] + adjacencyMatrix[start][i])))
			{
				distanceToVertice[i] = distanceToVertice[start] + adjacencyMatrix[start][i];
				if (i == finish)
				{
					path.push_back(i);
					shortPath = path;
					path.pop_back();
				}
				else
				{
					findPathRecursive(adjacencyMatrix, i, finish);
				}
			}
		}
	}
	path.pop_back();
	return shortPath;
}

std::list<int> findPathR(const std::vector<std::vector<int> > &adjacencyMatrix, int start, int finish)
{
	// Number of vertices in graph
	size_t nVertices = adjacencyMatrix.size();
	// Check adjacency matrix for consistence
	for (size_t i = 0; i < nVertices; i++)
	{
		if (adjacencyMatrix[i].size() != nVertices) throw "Error: wrong structure of adjacency matrix";
	}
	return findPathRecursive(adjacencyMatrix, start, finish);
}

std::list<int> findPath(std::vector<std::vector<int> > &adjacencyMatrix, int start, int finish)
{
	int nVertices = adjacencyMatrix.size();
	std::vector<int> distance(nVertices, -1);
	std::list<int> path, shortPath;

	int curr = start;
	int near = 0;
	path.push_back(start);
	distance[curr] = 0;
	while (path.size() > 0)
	{
		int curr = path.back();
		int alt = distance[curr] + adjacencyMatrix[curr][near];
		if ((adjacencyMatrix[curr][near] > 0) && ((distance[near] == -1) || (alt < distance[near])))
		{
			distance[near] = alt;
			path.push_back(near);
			if (near == finish)
			{
				shortPath = path;
				//printStl(shortPath);
			}
			near = 0;
		}
		else
		{
			near++;
			if (near == nVertices)
			{
				near = path.back();
				path.pop_back();
			}
		}
	}
	printf("Distance to finish is %d\n", distance[finish]);
	return shortPath;
}