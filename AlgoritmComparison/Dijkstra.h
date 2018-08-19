#pragma once
#include "stdafx.h"
#include "Node.h"
#include <limits.h>
#include <string>

class DijkstraAlgorithm
{
private:
	int horizontalSize; // horizontal size of the map
	int verticalSize; // vertical size size of the map
	Node *src, *dest;
	int **dist;    // dist[i] will hold the shortest distance from src to i
	bool **sptSet; // sptSet[i] will true if shortest distance from src to i is finalized
	int **graph; // map containing all nodes, 0 for unavailable, else for distance
	int dir;
	int *dx;
	int *dy;
	POINT u;
	std::string path;

	POINT minDistance();

	template <class T>
	T** create2dArray(int rows, int cols);
	template <class T>
	void clear2dArray(T** array);

public:
	void setGraph(int **graph);
	void init(int horizontalSize, int verticalSize, Node *src, Node *dest);

	bool nextStep();
	POINT getCurrentNode(); // POINT u
	void pathFind(const int & xStart, const int & yStart,
		const int & xFinish, const int & yFinish);
	void clear();

	std::string getPath();
};