#pragma once
#include "stdafx.h"
#include "Algorithm.h"
#include "AlgorithmFactory.h"

class Comparison
{
private:
	Algorithm * algorithm;
	int xStart, yStart, xFinish, yFinish;
	int horizontalSize, verticalSize;
	std::vector<std::vector<int>> graph;
	int dir;
	std::vector<int> dx;
	std::vector<int> dy;
	bool startFinish; // true for starting node flag, false for finish node flag
	bool readyToStart;
	bool started;
	POINT lastNodeSelected;
	int time;

	std::string path;
	POINT lastCurrentNode;

	void initAlgorithm();
	void clear();
public:
	Comparison();
	~Comparison();

	int getxStart() { return xStart; }
	int getyStart() { return yStart; }
	int getxFinish() { return xFinish; }
	int getyFinish() { return yFinish; }
	int getHorizontalSize() { return horizontalSize; }
	int getVerticalSize() { return verticalSize; }
	int getGraphState(int x, int y);
	int getTime() { return time; }

	void removeNode(int xPos, int yPos);
	void remakeNode(int xPos, int yPos);

	void updateStartFinishFlag();
	bool startFinishFlag();
	void updateStart(const int & xStart, const int & yStart);
	void updateFinish(const int & xFinish, const int & yFinish);
	void setCurrentAlgorithm(Algorithm* algorithm);
	bool sameNode(POINT node);
	void init();
	int directionX(char c, int horizontalSize);
	int directionY(char c, int verticalSize);

	bool nextStep();
	POINT getCurrentNodeCoordinates();
	std::string getPath();
};