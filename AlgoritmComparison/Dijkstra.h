#pragma once
#include "stdafx.h"
#include "Node.h"
#include "Algorithm.h"
#include <limits.h>
#include <string>
#include <vector>

class DijkstraAlgorithm : public Algorithm
{
private:
	int horizontalSize; // horizontal size of the map
	int verticalSize; // vertical size size of the map
	Node *src, *dest;
	std::vector<std::vector<int>> dist; // dist[i] will hold the shortest distance from src to i
	std::vector<std::vector<bool>> sptSet; // sptSet[i] will true if shortest distance from src to i is finalized
	std::vector<std::vector<int>> graph; // map containing all nodes, 0 for unavailable, else for distance
	int dir;
	std::vector<int> dx;
	std::vector<int> dy;
	POINT u;
	std::string path;

	POINT minDistance();

public:
	void setGraph(std::vector<std::vector<int>> graph);
	void init(int horizontalSize, int verticalSize, int xStart,
		int yStart, int xFinish, int yFinish);

	bool nextStep();
	POINT getCurrentNode(); // POINT u
	void clear();

	std::string getPath();
};