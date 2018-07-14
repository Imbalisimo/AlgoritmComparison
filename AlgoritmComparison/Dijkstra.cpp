#include "stdafx.h"
#include "Dijkstra.h"

void DijkstraAlgorithm::init(int horizontalSize, int verticalSize, Node *src)
{
	this->horizontalSize = horizontalSize;
	this->verticalSize = verticalSize;
	this->src = src;

	dist = new int[verticalSize*horizontalSize];
	sptSet = new bool[verticalSize*horizontalSize];
	for (int i = 0; i < verticalSize*horizontalSize; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

//	dist[src->getxPos*src->getyPos] = 0;
}

boolean DijkstraAlgorithm::nextStep()
{
	return false;
}

void DijkstraAlgorithm::pathFind(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish)
{
	while (nextStep());
}