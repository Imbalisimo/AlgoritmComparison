#pragma once
#include "stdafx.h"
#include "Node.h"
#include <queue>
#include <string>
#include <math.h>
#include <utility>
#include <type_traits>
#include <typeinfo>

class AStarAlgorithm
{
private:
	int horizontalSize; // horizontal size of the map
	int verticalSize; // vertical size size of the map
	int &xStart, &yStart, &xFinish, &yFinish;
	int **map;
	int **closed_nodes_map; // map of closed (tried-out) nodes
	int **open_nodes_map; // map of open (not-yet-tried) nodes
	int **dir_map; // map of directions
	int dir;
	int *dx;
	int *dy;
	std::string path;

	std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
	int pqi; // priority queue index
	Node* n0;
	Node* m0;
	int x, y;

	int** create2dArray(int rows, int cols);

public:
	Node* **nodeMap;
	void init(int horizontalPlaces, int verticalPlaces, const int & xStart,
		const int & yStart, const int & xFinish, const int & yFinish);
	boolean nextStep();
	void pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish);
};