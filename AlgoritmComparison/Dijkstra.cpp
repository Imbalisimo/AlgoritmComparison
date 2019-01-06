#include "stdafx.h"
#include "Dijkstra.h"

void DijkstraAlgorithm::init(int horizontalSize, int verticalSize, int xStart,
	int yStart, int xFinish, int yFinish)
{
	this->horizontalSize = horizontalSize;
	this->verticalSize = verticalSize;
	Node* source = new Node(xStart, yStart, 0, 0);
	Node* destination = new Node(xFinish, yFinish, 0, 0);
	this->src = source;
	this->dest = destination;

	dist.assign(horizontalSize, std::vector<int>(verticalSize, INT_MAX));
	sptSet.assign(horizontalSize, std::vector<bool>(verticalSize, false));
	path = "";

	u.x = -10;
	u.y = -10;

	dir = 4;
	dx = { 0, 1, 0, -1 };
	dy = { -1, 0, 1, 0 };

	dist[src->getxPos()][src->getyPos()] = 0;
}

POINT DijkstraAlgorithm::minDistance()
{
	// Initialize min value
	int min = INT_MAX, min_indexX, min_indexY;
	POINT p;

	for (int i = 0; i < horizontalSize; i++)
		for (int j = 0; j < verticalSize; j++)
			if (sptSet[i][j] == false && dist[i][j] <= min)
				min = dist[i][j], min_indexX = i, min_indexY = j;

	p.x = min_indexX;
	p.y = min_indexY;
	return p;
}

bool DijkstraAlgorithm::nextStep()
{
	u = minDistance();

	if (dist[u.x][u.y] == INT_MAX)
		return false; // path not found

	if (!(u.x == dest->getxPos() && u.y == dest->getyPos()))
	{
		sptSet[u.x][u.y] = true;

		// update surrounding nodes' distance
		for (int counter = 0; counter < dir; ++counter)
		{
			int i = u.x + dx[counter], j = u.y + dy[counter];
			if (i >= 0 && i < horizontalSize && j >= 0 && j < verticalSize)
				if (!sptSet[i][j] && graph[i][j] != 0 && dist[u.x][u.y] != INT_MAX
					&& dist[u.x][u.y] + graph[i][j] < dist[i][j])
					dist[i][j] = dist[u.x][u.y] + graph[i][j];
		}

		return true;
	}
	else
	{
		makePath();

		return false; // path found
	}
}

void DijkstraAlgorithm::makePath()
{
	// make path!!!!!
	char c;
	int x = u.x, y = u.y;

	while (x != src->getxPos() || y != src->getyPos())
	{
		int distMeter = graph[x][y];
		int j;
		for (int i = 0; i < dir; ++i)
		{
			int xdx = x + dx[i];
			int ydy = y + dy[i];
			if (!(xdx < 0 || xdx >= horizontalSize || ydy<0 || ydy >= verticalSize))
				if (dist[x][y] == graph[x][y] + dist[xdx][ydy] && graph[xdx][ydy] != 0)
					j = i;
		}
		c = '0' + (j + dir / 2) % dir; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
		path = c + path;
		x += dx[j];
		y += dy[j];
	}
}

void DijkstraAlgorithm::clear()
{
	delete src;
	delete dest;
}

std::string DijkstraAlgorithm::getPath()
{
	return path;
}

void DijkstraAlgorithm::setGraph(std::vector<std::vector<int>> graph)
{
	this->graph = graph;
}

POINT DijkstraAlgorithm::getCurrentNode()
{
	return u;
}