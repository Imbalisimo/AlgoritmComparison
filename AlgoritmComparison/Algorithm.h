#pragma once
#include "stdafx.h"
#include <string>
#include <vector>

class Algorithm {
public:
	virtual void setGraph(std::vector<std::vector<int>> graph) = 0;
	virtual void init(int horizontalSize, int verticalSize, int xStart,
		int yStart, int xFinish, int yFinish) = 0;

	virtual bool nextStep() = 0;
	virtual POINT getCurrentNode() = 0;

	virtual std::string getPath() = 0;
	virtual void clear() = 0;
};