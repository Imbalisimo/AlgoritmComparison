#pragma once
#include "stdafx.h"
#include "A_star.h"
#include "Dijkstra.h"

class Comparison
{
private:
	AStarAlgorithm astar;
	DijkstraAlgorithm dijkstra;
	int xStart, yStart, xFinish, yFinish;
	int horizontalSize=60, verticalSize=60;
	int **graph;
	int dir;
	int *dx;
	int *dy;
	bool startFinish; // true for starting node flag, false for finish node flag
	bool started;

	void removeNode(int xPos, int yPos);

public:
	Comparison();
	~Comparison();
	int currentAlgorithm; // 1 for A*, 2 for Dijkstra

	int getxStart() { return xStart; }
	int getyStart() { return yStart; }
	int getxFinish() { return xFinish; }
	int getyFinish() { return yFinish; }
	int getHorizontalSize() { return horizontalSize; }
	int getVerticalSize() { return verticalSize; }
	int getGraphState(int x, int y);

	void updateStartFinishFlag();
	bool startFinishFlag();
	void updateStart(const int & xStart, const int & yStart);
	void updateFinish(const int & xFinish, const int & yFinish);
	void init(int horizontalSize, int verticalSize);
	int directionX(char c, int horizontalSize);
	int directionY(char c, int verticalSize);

	void initAlgorithm();
	void nextStep();
	POINT getCurrentNodeCoordinates();
	std::string getPath();
	void clear();
};