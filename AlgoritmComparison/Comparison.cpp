#include "Comparison.h"

Node Comparison::createNode(int xPos, int yPos)
{
	Node node(xPos, yPos, 0, 0);

	if (xPos != 0)
		node.left = &map[xPos - 1][yPos];
	node.right = NULL;
	if (yPos != 0)
		node.left = &map[xPos][yPos-1];
	node.up = NULL;

	map[xPos][yPos] = node;

	return node;
}

void Comparison::init(int horizontalSize, int verticalSize)
{
	this->horizontalSize = horizontalSize;
	this->verticalSize = verticalSize;
	map = new Node *[verticalSize];
	if (map)
		for (int i = 0; i < verticalSize; ++i)
			map[i] = new Node[horizontalSize];

	for(int i = 0; i < horizontalSize; ++i)
		for (int j = 0; j < verticalSize; ++j)
			map[i][j] = createNode(i, j);

	if (currentAlgorithm = 1)
		astar.init(horizontalSize, verticalSize, getxStart(), getyStart(),
			getxFinish(), getyFinish()), astar.nodeMap = &map;
	//else
	// Dijkstra

}

void Comparison::updateStart(const int & xStart, const int & yStart)
{
	this->xStart = xStart, this->yStart = yStart;
}
void Comparison::updateFinish(const int & xFinish, const int & yFinish)
{
	this->xFinish = xFinish, this->yFinish = yFinish;
}