#include "stdafx.h"
#include "Node.h"

// Determine priority (in the priority queue)
bool operator<(const Node & a, const Node & b)
{
	return a.getPriority() > b.getPriority();
}

Node::Node(int xp, int yp, int d, int p)
{
	xPos = xp; yPos = yp; level = d; priority = p;
}

Node::Node() {}

//int Node::getxPos() const { return xPos; }
//int Node::getyPos() const { return yPos; }
//int Node::getLevel() const { return level; }
//int Node::getPriority() const { return priority; }

void Node::updatePriority(const int xDest, const int yDest)
{
	priority = level + estimate(xDest, yDest) * 10; // A*
}

void Node::updatePriority(const int & priority)
{
	this->priority = priority;
}

void Node::updateLevel(const int & lvl)
{
	level = lvl;
}

void Node::nextLevel(const int & i) // i: direction
{
	level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

const int Node::estimate(const int xDest, const int yDest) const
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	//d = static_cast<int>(sqrt(xd*xd + yd * yd));

	// Manhattan distance
	d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));

	return(d);
}