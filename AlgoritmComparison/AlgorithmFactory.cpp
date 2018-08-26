#include "stdafx.h"
#include "AlgorithmFactory.h"


AlgorithmFactory::AlgorithmFactory()
{
}


AlgorithmFactory::~AlgorithmFactory()
{
}

Algorithm* AlgorithmFactory::create(AlgorithmID algorithmID)
{
	switch (algorithmID)
	{
	case astar: return new AStarAlgorithm();
	case dijkstra: return new DijkstraAlgorithm();
	}
}