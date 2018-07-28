#pragma once
#include "stdafx.h"
#include "A_star.h"
#include "Dijkstra.h"

class Comparison
{
private:
	int xStart, yStart, xFinish, yFinish;
	int horizontalSize=60, verticalSize=60;
	int **graph;
	bool startFinish; // true for starting node flag, false for finish node flag

	void removeNode(int xPos, int yPos);

public:
	Comparison();
	int currentAlgorithm; // 1 for A*, 2 for Dijkstra
	AStarAlgorithm astar;
	DijkstraAlgorithm dijkstra;

	void initAlgorithm();
	void nextStep();
	POINT getCurrentNodeCoordinates();
	void updateStartFinishFlag();
	bool startFinishFlag();
	void updateStart(const int & xStart, const int & yStart);
	void updateFinish(const int & xFinish, const int & yFinish);
	int getxStart() { return xStart; }
	int getyStart() { return yStart; }
	int getxFinish() { return xFinish; }
	int getyFinish() { return yFinish; }
	int getHorizontalSize() { return horizontalSize; }
	int getVerticalSize() { return verticalSize; }
	void init(int horizontalSize, int verticalSize);
};