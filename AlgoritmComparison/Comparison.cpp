#include "stdafx.h"
#include "Comparison.h"

Comparison::Comparison()
{
	startFinish = true;
}

Comparison::~Comparison()
{
	delete algorithm;
}

void Comparison::init()
{
	horizontalSize = GetPrivateProfileInt(_T("size"), _T("horizontalSize"), 30, _T("algoComp.ini"));
	verticalSize = GetPrivateProfileInt(_T("size"), _T("verticalSize"), 15, _T("algoComp.ini"));

	time = GetPrivateProfileInt(_T("timer"), _T("time"), 50, _T("algoComp.ini"));

	algorithm = nullptr;
	graph.assign(horizontalSize, std::vector<int>(verticalSize, 1));

	dir = 4;

	xStart = -1;
	yStart = -1;
	xFinish = -1;
	yFinish = -1;

	lastNodeSelected.x = -1;
	lastNodeSelected.y = -1;
	started = false;

	algorithm= new DijkstraAlgorithm();
	path = "";
	lastCurrentNode.x = -1;
	lastCurrentNode.y = -1;
}

void Comparison::removeNode(int xPos, int yPos)
{
	if (!started)
		graph[xPos][yPos] = 0;
}

void Comparison::remakeNode(int xPos, int yPos)
{
	if (!started)
		graph[xPos][yPos] = 1;
}

bool Comparison::sameNode(POINT node)
{
	if (node.x == lastNodeSelected.x && node.y == lastNodeSelected.y)
		return true;
	else
	{
		lastNodeSelected = node;
		return false;
	}
}

std::string Comparison::getPath()
{
	if(algorithm==nullptr) return path;
	
	path = algorithm->getPath()=="" ? path : algorithm->getPath();
	if (path != "")
		started = false;

	return path;
}

void Comparison::setCurrentAlgorithm(Algorithm *algorithm)
{
	clear();
	path = "";
	lastCurrentNode.x = -1;
	lastCurrentNode.y = -1;
	this->algorithm = algorithm;
}

void Comparison::initAlgorithm()
{
	if (algorithm == nullptr) return;

	if (xStart != -1 && yStart != -1 && xFinish != -1 && yFinish != -1)
	{
		algorithm->setGraph(graph);
		algorithm->init(horizontalSize, verticalSize, xStart, yStart, xFinish, yFinish);
		started = true;
	}

}

bool Comparison::nextStep()
{
	if (algorithm == nullptr) return false;

	if (path != "")
	{
		algorithm->clear();
		algorithm->setGraph(graph);
		algorithm->init(horizontalSize, verticalSize, xStart, yStart, xFinish, yFinish);
		lastNodeSelected.x = -1;
		lastNodeSelected.y = -1;
		path = "";
	}

	if (!started)
	{
		initAlgorithm();
	}

	if (started)
		return algorithm->nextStep();
	else return false;
}

POINT Comparison::getCurrentNodeCoordinates()
{
	if (algorithm == nullptr) return lastCurrentNode;

	if (started)
		lastCurrentNode = algorithm->getCurrentNode();

	return lastCurrentNode;
}

void Comparison::clear()
{
	if (algorithm == nullptr) return;

	algorithm->clear();
	delete algorithm;

	started = false;
}

int Comparison::getGraphState(int x, int y)
{
	return graph[x][y];
}

void Comparison::updateStartFinishFlag()
{
	startFinish = !startFinish;
}

bool Comparison::startFinishFlag()
{
	return startFinish;
}

void Comparison::updateStart(const int & xStart, const int & yStart)
{
	if (!started)
		this->xStart = xStart, this->yStart = yStart;
}

void Comparison::updateFinish(const int & xFinish, const int & yFinish)
{
	if (!started)
		this->xFinish = xFinish, this->yFinish = yFinish;
}

int Comparison::directionX(char c, int xSize)
{
	dx.push_back(0);
	dx.push_back(-xSize / horizontalSize);
	dx.push_back(0);
	dx.push_back(xSize / horizontalSize);

	return dx[c%'0'];
}
int Comparison::directionY(char c, int ySize)
{
	dy.push_back(ySize / verticalSize);
	dy.push_back(0);
	dy.push_back(-ySize / verticalSize);
	dy.push_back(0);

	return dy[c-'0'];
}