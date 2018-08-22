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
	algorithm = nullptr;
	graph.assign(horizontalSize, std::vector<int>(verticalSize, 1));

	dir = 4;

	started = false;
}

void Comparison::removeNode(int xPos, int yPos)
{
	graph[xPos][yPos] = 0;
}

void Comparison::remakeNode(int xPos, int yPos)
{
	graph[xPos][yPos] = 1;
}

std::string Comparison::getPath()
{
	if(algorithm==nullptr) return "";
	
	return algorithm->getPath();
}

void Comparison::initAlgorithm()
{
	if (algorithm == nullptr) return;

	algorithm->setGraph(graph);
	algorithm->init(horizontalSize, verticalSize, xStart, yStart, xFinish, yFinish);
	started = true;
}

void Comparison::nextStep()
{
	if (algorithm == nullptr) return;

	algorithm->nextStep();
}

POINT Comparison::getCurrentNodeCoordinates()
{
	POINT p;
	p.x = -1;
	p.y = -1;

	if (algorithm == nullptr) return p;

	return algorithm->getCurrentNode();
}

void Comparison::clear()
{
	if (algorithm == nullptr) return;

	algorithm->clear();

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
	/*dx[0] = 0;
	dx[1] = -xSize/horizontalSize;
	dx[2] = 0;
	dx[3] = xSize / horizontalSize;*/
	return dx[c%'0'];
}
int Comparison::directionY(char c, int ySize)
{
	dy.push_back(ySize / verticalSize);
	dy.push_back(0);
	dy.push_back(-ySize / verticalSize);
	dy.push_back(0);
	/*dy[0] = ySize / verticalSize;
	dy[1] = 0;
	dy[2] = -ySize / verticalSize;
	dy[3] = 0;*/
	return dy[c-'0'];
}

void Comparison::setCurrentAlgorithm(Algorithm *algorithm)
{
	this->algorithm = algorithm;
}