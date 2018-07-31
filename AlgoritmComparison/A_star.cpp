#include "stdafx.h"
#include "A_star.h"
#include <utility>
#include <type_traits>
#include <typeinfo>

AStarAlgorithm::AStarAlgorithm(int a) :xStart(*&a), xFinish(*&a), yStart(*&a), yFinish(*&a)
{ }

int** AStarAlgorithm::create2dArray(int rows, int cols) {
	int **arr = new int *[rows];
	if (arr)
		for (int i = 0; i < rows; ++i)
			arr[i] = new int[cols];
	return arr;
}

void AStarAlgorithm::init(int horizontalPlaces, int verticalPlaces, const int & xStart, 
	const int & yStart, const int & xFinish, const int & yFinish)
{
	horizontalSize = horizontalPlaces; // horizontal size of the map
	verticalSize = verticalPlaces; // vertical size size of the map
	this->xStart = xStart, this->yStart = yStart, this->xFinish = xFinish, this->xFinish = yFinish;
	map = create2dArray(horizontalSize, verticalSize);
	closed_nodes_map = create2dArray(horizontalSize, verticalSize);; // map of closed (tried-out) nodes
	open_nodes_map = create2dArray(horizontalSize, verticalSize);; // map of open (not-yet-tried) nodes
	dir_map = create2dArray(horizontalSize, verticalSize);; // map of directions
	dir = 4;
	dx = new int[dir] { 0, 1, 0, -1 };
	dy = new int[dir] { -1, 0, 1, 0 };

	pqi = 0;
	// reset the node maps
	for (int y = 0; y<verticalSize; ++y)
	{
		for (int x = 0; x<horizontalSize; ++x)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	path = "";

	// create the start node and push into list of open nodes
	n0 = new Node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	x = n0->getxPos();
	y = n0->getyPos();
	open_nodes_map[x][y] = n0->getPriority(); // mark it on the open nodes map
}

bool AStarAlgorithm::nextStep()
{
	int i, j, xdx, ydy;
	char c;
	if (!pq[pqi].empty())
	{
		// get the current node with the highest priority from the list of open nodes
		n0 = new Node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;


		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];
			switch (i) // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
			{
			case 0:
				if (n0->up == NULL)
					continue;
			case 1:
				if (n0->right == NULL)
					continue;
			case 2:
				if (n0->down == NULL)
					continue;
			case 3:
				if (n0->left == NULL)
					continue;
			}

			if (!(xdx<0 || xdx>horizontalSize - 1 || ydy<0 || ydy>verticalSize - 1
				|| map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new Node(xdx, ydy, n0->getLevel(), n0->getPriority());
				m0->updateLevel(n0->getLevel());
				m0->updatePriority(xFinish, yFinish);

				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
				}
				else if (open_nodes_map[xdx][ydy]>m0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx && pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;

					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
			}
		}
		return true;
	}
	return false; // no route found
}

void AStarAlgorithm::pathFind(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish)
{
	while (nextStep());
}

std::string AStarAlgorithm::getPath()
{
	return path;
}

void AStarAlgorithm::setGraph(int **graph)
{
	this->graph = graph;
}

Node* AStarAlgorithm::getCurrentNode()
{
	return n0;
}