#include "stdafx.h"
#include "Comparison.h"

Comparison::Comparison()
{
	startFinish = true;
}

Comparison::~Comparison()
{
	for (int i = 0; i < horizontalSize; ++i)
		delete[] graph[i];

	delete[] graph;
	delete[] dx;
	delete[] dy;
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

	dir = 4;
	dx = new int[dir];
	dy = new int[dir];

	for(int i = 0; i < horizontalSize; ++i)
		for (int j = 0; j < verticalSize; ++j)
			graph[i][j] = 1;

	currentAlgorithm = 0;

	/*if (currentAlgorithm = 1)
		astar.setGraph(graph), astar.init(horizontalSize, verticalSize, getxStart(), getyStart(),
			getxFinish(), getyFinish());
	else
		dijkstra.setGraph(graph), dijkstra.init(horizontalSize, verticalSize,
			new Node(xStart, yStart, 0, 0), new Node(xFinish, yFinish, 0, 0));*/

	started = false;
}

std::string Comparison::getPath()
{
	switch (currentAlgorithm)
	{
	case 1:
		return astar.getPath();
	case 2:
		return dijkstra.getPath();
	default:
		return "";
	}
}

void Comparison::initAlgorithm()
{
	switch (currentAlgorithm)
	{
	case 1:
		astar.setGraph(graph);
		astar.init(horizontalSize, verticalSize, xStart, yStart, xFinish, yFinish);
		started = true;
		break;
	case 2:
		dijkstra.setGraph(graph);
		dijkstra.init(horizontalSize, verticalSize, new Node(xStart, yStart, 0, 0),
			new Node(xFinish, yFinish, 0, 0));
		started = true;
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
	p.x = -1;
	p.y = -1;
	switch (currentAlgorithm)
	{
	case 1:
		p = astar.getCurrentNode();
		break;
	case 2:
		p = dijkstra.getCurrentNode();
		break;
	}
	return p;
}

void Comparison::clear()
{
	switch (currentAlgorithm)
	{
	case 1:
		astar.clear();
		break;
	case 2:
		dijkstra.clear();
		break;
	}
		started = false;
		currentAlgorithm = 0;
}

int Comparison::getGraphState(int x, int y)
{
	return graph[x][y];
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
	if (!started)
		this->xStart = xStart, this->yStart = yStart;
}
void Comparison::updateFinish(const int & xFinish, const int & yFinish)
{
	if (!started)
		this->xFinish = xFinish, this->yFinish = yFinish;
}

int Comparison::directionX(char c, int xSize)
{
	dx[0] = 0;
	dx[1] = xSize/horizontalSize;
	dx[2] = 0;
	dx[3] = -xSize / horizontalSize;
	return dx[c%'0'];
}
int Comparison::directionY(char c, int ySize)
{
	dy[0] = -ySize / verticalSize;
	dy[1] = 0;
	dy[2] = ySize / verticalSize;
	dy[3] = 0;
	return dy[c-'0'];
}