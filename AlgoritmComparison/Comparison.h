#pragma once
#include "stdafx.h"
#include "A_star.h"
#include "Dijkstra.h"

class Comparison
{
private:
	AStarAlgorithm astar;
	DijkstraAlgorithm dijkstra;
	int &xStart, &yStart, &xFinish, &yFinish;
	int horizontalSize, verticalSize;

	Node createNode(int xPos, int yPos);

public:
	void updateStart(const int & xStart, const int & yStart);
	void updateFinish(const int & xFinish, const int & yFinish);
	int getxStart() { return xStart; }
	int getyStart() { return yStart; }
	int getxFinish() { return xFinish; }
	int getyFinish() { return yFinish; }
	int currentAlgorithm; //1 for A*, 2 for Dijkstra
	Node **map;
	void init(int horizontalSize, int verticalSize);
};