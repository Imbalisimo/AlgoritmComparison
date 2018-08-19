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

template <class T>
void DijkstraAlgorithm::clear2dArray(T** array)
{
	for (int i = 0; i < horizontalSize; ++i)
		delete[] array[i];

	delete[] array;
}

void DijkstraAlgorithm::init(int horizontalSize, int verticalSize, Node *src, Node *dest)
{
	this->horizontalSize = horizontalSize;
	this->verticalSize = verticalSize;
	this->src = src;
	this->dest = dest;

	dist = create2dArray<int>(horizontalSize, verticalSize);
	sptSet = create2dArray<bool>(horizontalSize, verticalSize);
	path = "";

	dir = 4;
	dx = new int[dir] { 0, 1, 0, -1 };
	dy = new int[dir] { -1, 0, 1, 0 };

	for (int i = 0; i < horizontalSize; i++)
		for (int j = 0; j < verticalSize; j++)
			dist[i][j] = INT_MAX, sptSet[i][j] = false;

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
				if (!(xdx < 0 || xdx >= horizontalSize || ydy<0 || ydy>verticalSize))
					if (dist[x][y] == graph[x][y] + dist[xdx][ydy]&&graph[xdx][ydy]!=0)
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

void DijkstraAlgorithm::clear()
{
	clear2dArray(dist);
	clear2dArray(sptSet);

	delete[] dx;
	delete[] dy;

	delete src;
	delete dest;
}

std::string DijkstraAlgorithm::getPath()
{
	return path;
}

void DijkstraAlgorithm::setGraph(int **graph)
{
	this->graph = graph;
}

POINT DijkstraAlgorithm::getCurrentNode()
{
	return u;
}