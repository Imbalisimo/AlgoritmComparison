#pragma once
#include "stdafx.h"
#include "Node.h"
#include "Algorithm.h"
#include <queue>
#include <string>
#include <math.h>
#include <utility>
#include <type_traits>
#include <typeinfo>

class AStarAlgorithm : public Algorithm
{
private:
	int horizontalSize; // horizontal size of the map
	int verticalSize; // vertical size size of the map
	int xStart, yStart, xFinish, yFinish;
	std::vector<std::vector<int>> map;
	std::vector<std::vector<int>> closed_nodes_map; // map of closed (tried-out) nodes
	std::vector<std::vector<int>> open_nodes_map; // map of open (not-yet-tried) nodes
	std::vector<std::vector<int>> dir_map; // map of directions
	int dir;
	std::vector<int> dx;
	std::vector<int> dy;
	std::string path;

	std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
	int pqi; // priority queue index
	Node* n0;
	Node* m0;
	int x, y;
	std::vector<std::vector<int>> graph;

	void makePath();

public:
	void setGraph(std::vector<std::vector<int>> graph);
	void init(int horizontalSize, int verticalSize, int xStart,
		int yStart, int xFinish, int yFinish);

	bool nextStep();
	POINT getCurrentNode(); // n0
	void clear();

	std::string getPath();
};