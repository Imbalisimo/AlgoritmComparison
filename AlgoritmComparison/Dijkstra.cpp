#include "stdafx.h"
#include "Dijkstra.h"

template <class T>
T** DijkstraAlgorithm::create2dArray(int rows, int cols) {
	T **arr = new T *[rows];
	if (arr)
		for (int i = 0; i < rows; ++i)
			arr[i] = new T[cols];
	return arr;
}

void DijkstraAlgorithm::init(int horizontalSize, int verticalSize, Node *src, Node *dest)
{
	this->horizontalSize = horizontalSize;
	this->verticalSize = verticalSize;
	this->src = src;
	this->dest = dest;

	dist = create2dArray<int>(verticalSize, horizontalSize);
	sptSet = create2dArray<bool>(verticalSize, horizontalSize);

	dir = 4;
	dx = new int[dir] { 0, 1, 0, -1 };
	dy = new int[dir] { -1, 0, 1, 0 };

	for (int i = 0; i < verticalSize; i++)
		for (int j = 0; i < horizontalSize; j++)
			dist[i][j] = INT_MAX, sptSet[i][j] = false;

	dist[src->getxPos][src->getyPos] = 0;
}

POINT DijkstraAlgorithm::minDistance()
{
	// Initialize min value
	int min = INT_MAX, min_indexX, min_indexY;
	POINT p;

	for (int i = 0; i < verticalSize; i++)
		for (int j = 0; i < horizontalSize; j++)
			if (sptSet[i][j] == false && dist[i][j] <= min)
				min = dist[i][j], min_indexX = i, min_indexY = j;

	p.x = min_indexX;
	p.y = min_indexY;
	return p;
}

bool DijkstraAlgorithm::nextStep()
{
	u = minDistance();

	if (dist[u.x][u.y] = INT_MAX)
		return false; // path not found

	if (!(u.x == dest->getxPos() && u.y == dest->getyPos()))
	{
		sptSet[u.x][u.y] = true;
		for (int i = u.x - 1; i <= u.x + 1; i += 2)
			for (int j = u.y - 1; j <= u.y + 1; j += 2)
				if (!sptSet[i][j] && graph[i][j] != 0 && dist[u.x][u.y] != INT_MAX
					&& dist[u.x][u.y] + graph[i][j] < dist[i][j])
					dist[i][j] = dist[u.x][u.y] + graph[i][j];

		return true;
	}
	else
	{
		// make path!!!!!
		char c;
		int x = u.x, y = u.y;
		path = "";
		while (x != src->getxPos || y != src->getyPos)
		{
			int distMeter = graph[x][y];
			int j;
			for (int i = 0; i < dir; ++i)
			{
				int xdx = x + dx[i];
				int ydy = y + dy[i];
				if (dist[x][y] == graph[x][y] + dist[xdx][ydy])
					j = i;
			}
				c = '0' + (j + dir / 2) % dir; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
				path = c + path;
				x += dx[j];
				y += dy[j];
		}

		return false; // path found
	}
}

void DijkstraAlgorithm::pathFind(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish)
{
	while (nextStep());
}

void DijkstraAlgorithm::setGraph(int **graph)
{
	this->graph = graph;
}

Node* DijkstraAlgorithm::getCurrentNode()
{
	return new Node(u.x, u.y, 0, 0);
}