#include "stdafx.h"
#include "containers.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::vector<int> > adjacencyMatrix;
	size_t nVert = 10;
	adjacencyMatrix.resize(nVert);
	for (size_t i = 0; i < nVert; i++)
	{
		adjacencyMatrix[i].resize(nVert);
	}
	adjacencyMatrix[0][1] = 220;
	adjacencyMatrix[0][2] = 105;
	adjacencyMatrix[1][3] = 72;
	adjacencyMatrix[2][3] = 154;
	adjacencyMatrix[2][5] = 217;
	
	adjacencyMatrix[2][6] = 288;
	adjacencyMatrix[2][7] = 289;
	adjacencyMatrix[3][4] = 147;
	adjacencyMatrix[3][7] = 135;
	adjacencyMatrix[4][7] = 184;
	
	adjacencyMatrix[4][8] = 159;
	adjacencyMatrix[5][6] = 204;
	adjacencyMatrix[6][7] = 127;
	adjacencyMatrix[6][8] = 198;
	adjacencyMatrix[6][9] = 114;
	
	adjacencyMatrix[7][8] = 141;
	adjacencyMatrix[7][9] = 127;
	adjacencyMatrix[8][9] = 109;

	int start = 0;
	int finish = 9;

	std::list<int> shortPath = findPath(adjacencyMatrix, start, finish);
	// TODO: test extremes
	printStl(shortPath);

	//////////////////////////////////////////////////////////////////////////
	//containers::stack<int> lst;
	//for (int i = 0; i < 10; i++)
	//{
	//	lst.push(i);
	//}
	//lst.print();
	//lst.reverse();
	//lst.print();
	//lst.pop();
	//lst.print();

	//std::vector<int> v;
	//int vecSize = 10;
	//v.resize(vecSize);
	//for(int i = 0; i < vecSize; ++i)
	//{
	//	v[i] = rand() % 200 + 1;
	//}
	//std::vector<int> v2(v), v3(v);
	//std::vector<size_t> idx;
	//vectorSort(v, idx);
	//vectorSort(v3);
	//std::sort(v2.begin(), v2.end());
	//std::cout << "Vectors are equal = " << (v == v2) << std::endl;

	//////////////////////////////////////////////////////////////////////////
	//printf("Iter:\n");
	//containers::list<int>::iterator it = lst.begin();
	//while (it != lst.end())
	//{
	//	printf("%d\n", *it);
	//	++it;
	//}
	
	//listEl<int>* start = createList();
	//printf("Original:\n");
	//printList(start);
	//start = reverseList(start);
	//printf("Reversed:\n");
	//printList(start);
	//printf("Even elements:\n");
	//removeEvenElements(start);
	//printList(start);
	//printf("Removed elements:\n");
	//start = removeElements(start, 3);
	//printList(start);
	return 0;
}
