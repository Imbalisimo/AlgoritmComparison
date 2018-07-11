#pragma once

#include "stdafx.h"

class Node
{
private:
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority
	int dir;

public:
	Node(int xp, int yp, int d, int p);

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int & xDest, const int & yDest);

	// give better priority to going strait instead of diagonally
	/*void nextLevel(const int & i) // i: direction*/

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const;
};