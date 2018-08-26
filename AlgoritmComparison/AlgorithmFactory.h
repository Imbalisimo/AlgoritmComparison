#pragma once
#include "stdafx.h"
#include "A_star.h"
#include "Dijkstra.h"

enum AlgorithmID
{
	astar,
	dijkstra
};

class AlgorithmFactory
{
public:
	AlgorithmFactory();
	~AlgorithmFactory();

	Algorithm* create(AlgorithmID algorithmID);
};

