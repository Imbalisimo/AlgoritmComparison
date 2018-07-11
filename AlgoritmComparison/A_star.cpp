#include "stdafx.h"
#include "A_star.h"
#include <utility>
#include <type_traits>
#include <typeinfo>


void AStarAlgorithm::init(int horizontalPlaces, int verticalPlaces)
{
	horizontalSize = horizontalPlaces; // horizontal size of the map
	verticalSize = verticalPlaces; // vertical size size of the map
	map = create2dArray(horizontalSize, verticalSize);
	closed_nodes_map = create2dArray(horizontalSize, verticalSize);; // map of closed (tried-out) nodes
	open_nodes_map = create2dArray(horizontalSize, verticalSize);; // map of open (not-yet-tried) nodes
	dir_map = create2dArray(horizontalSize, verticalSize);; // map of directions
	dir = 4;
	dx = new int[dir] { 1, 0, -1, 0 };
	dy = new int[dir] { 0, 1, 0, -1 };
}

int** AStarAlgorithm::create2dArray(int rows, int cols) {
	int **arr = new int *[rows];
	if (arr)
		for (int i = 0; i < rows; i++)
			arr[i] = new int[cols];
	return arr;
}