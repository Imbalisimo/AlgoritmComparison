#pragma once
#include "stdafx.h"
#include "Node.h"
#include <limits.h>

class DijkstraAlgorithm
{
private:
	int horizontalSize; // horizontal size of the map
	int verticalSize; // vertical size size of the map
	Node *src;
	int *dist;     // dist[i] will hold the shortest distance from src to i
	bool *sptSet; // sptSet[i] will true if shortest distance from src to i is finalized

	boolean nextStep();

public:
	void init(int horizontalSize, int verticalSize, Node *src);
	void pathFind(const int & xStart, const int & yStart,
		const int & xFinish, const int & yFinish);
};