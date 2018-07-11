#pragma once
#include"stdafx.h"
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
	int **map;
	int **closed_nodes_map; // map of closed (tried-out) nodes
	int **open_nodes_map; // map of open (not-yet-tried) nodes
	int **dir_map; // map of directions
	int dir;
	int *dx;
	int *dy;

	int** create2dArray(int rows, int cols);

public:
	void init(int horizontalPlaces, int verticalPlaces);
};