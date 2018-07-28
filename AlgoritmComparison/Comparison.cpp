#include "stdafx.h"
#include "Comparison.h"

Comparison::Comparison() : astar(0) 
{
	xStart = 0;
	yStart = 0;
	xFinish = 5;
	yFinish = 5;
	startFinish = true;
}

void Comparison::removeNode(int xPos, int yPos)
{
	graph[xPos][yPos] = 0;
}

void Comparison::init(int horizontalSize, int verticalSize)
{
	this->horizontalSize = horizontalSize;
	this->verticalSize = verticalSize;
	graph = new int *[horizontalSize];
	if (graph)
		for (int i = 0; i < horizontalSize; ++i)
			graph[i] = new int[verticalSize];

	for(int i = 0; i < horizontalSize; ++i)
		for (int j = 0; j < verticalSize; ++j)
			graph[i][j] = 1;

	if (currentAlgorithm = 1)
		astar.setGraph(graph), astar.init(horizontalSize, verticalSize, getxStart(), getyStart(),
			getxFinish(), getyFinish());
	else
		dijkstra.setGraph(graph), dijkstra.init(horizontalSize, verticalSize,
			new Node(xStart, yStart, 0, 0), new Node(xFinish, yFinish, 0, 0));
}

void Comparison::initAlgorithm()
{
	switch (currentAlgorithm)
	{
	case 1:
		astar.init(horizontalSize, verticalSize, xStart, yStart, xFinish, yFinish);
		break;
	case 2:
		dijkstra.init(horizontalSize, verticalSize, new Node(xStart, yStart, 0, 0),
			new Node(xFinish, yFinish, 0, 0));
		break;
	}
}

void Comparison::nextStep()
{
	switch (currentAlgorithm)
	{
	case 1:
		astar.nextStep();
		break;
	case 2:
		dijkstra.nextStep();
		break;
	}
}

POINT Comparison::getCurrentNodeCoordinates()
{
	POINT p;
	Node *n;
	switch (currentAlgorithm)
	{
	case 1:
		n = astar.getCurrentNode();
		p.x = n->getxPos();
		p.y = n->getyPos();
		break;
	case 2:
		n = dijkstra.getCurrentNode();
		p.x = n->getxPos();
		p.y = n->getyPos();
		break;
	}
	return p;
}

void Comparison::updateStartFinishFlag()
{
	startFinish = !startFinish;
}

bool Comparison::startFinishFlag()
{
	return startFinish;
}

void Comparison::updateStart(const int & xStart, const int & yStart)
{
	this->xStart = xStart, this->yStart = yStart;
}
void Comparison::updateFinish(const int & xFinish, const int & yFinish)
{
	this->xFinish = xFinish, this->yFinish = yFinish;
}