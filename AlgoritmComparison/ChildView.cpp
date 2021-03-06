
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "AlgoritmComparison.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "Comparison.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	EnableD2DSupport();
	algorithmComparison.init();
	/*AfxGetMainWnd()->GetMenu()->CheckMenuRadioItem(ID_ALGORITHMS_DIJKSTRA,
		ID_ALGORITHMS_A, ID_ALGORITHMS_DIJKSTRA, MF_BYCOMMAND);*/
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CChildView::OnDraw2d)
	ON_COMMAND(ID_DIJKSTRA, &CChildView::OnDijkstra)
	ON_COMMAND(ID_ASTAR, &CChildView::OnAstar)
	ON_COMMAND(ID_STEP, &CChildView::OnStep)
	ON_COMMAND(ID_ALGORITHMS_DIJKSTRA, CChildView::OnDijkstra)
	ON_COMMAND(ID_ALGORITHMS_A, CChildView::OnAstar)
	ON_COMMAND(ID_PROCEED_NEXTSTEP, CChildView::OnStep)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EXECUTE, &CChildView::OnExecute)
ON_WM_MOUSEMOVE()
ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	AfxGetMainWnd()->GetMenu()->CheckMenuRadioItem(ID_ALGORITHMS_DIJKSTRA,
		ID_ALGORITHMS_A, ID_ALGORITHMS_DIJKSTRA, MF_BYCOMMAND);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// Do not call CWnd::OnPaint() for painting messages
}

afx_msg LRESULT CChildView::OnDraw2d(WPARAM wParam, LPARAM lParam)
{
	CHwndRenderTarget* m_pRenderTarget = (CHwndRenderTarget*)lParam;
	ASSERT_VALID(m_pRenderTarget);
	
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

	// Draw a grid background.
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);

	CD2DSolidColorBrush m_pLightSlateGrayBrush(m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::Gray), NULL, TRUE);

	for (float x = 0; x < width; x += (width+0.0) / algorithmComparison.getHorizontalSize())
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			&m_pLightSlateGrayBrush,
			0.5f
		);
	}

	for (float y = 0; y < height; y += (height+0.0) / algorithmComparison.getVerticalSize())
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			&m_pLightSlateGrayBrush,
			0.5f
		);
	}

	D2D1_RECT_F nodeCurrent = D2D1::RectF(
		rtSize.width / algorithmComparison.getHorizontalSize()*algorithmComparison.getCurrentNodeCoordinates().x,
		rtSize.height / algorithmComparison.getVerticalSize()*algorithmComparison.getCurrentNodeCoordinates().y,
		rtSize.width / algorithmComparison.getHorizontalSize()*(algorithmComparison.getCurrentNodeCoordinates().x + 1),
		rtSize.height / algorithmComparison.getVerticalSize()*(algorithmComparison.getCurrentNodeCoordinates().y + 1)
	);
	CD2DSolidColorBrush m_pYellowBrush(m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::Yellow), NULL, TRUE);
	m_pRenderTarget->FillRectangle(nodeCurrent, &m_pYellowBrush);

	D2D1_RECT_F nodePath = nodeCurrent;
	std::string path = algorithmComparison.getPath();
	for (int i = path.length()-1; i >=0; --i)
	{
		nodePath = D2D1::RectF(
			nodePath.left + algorithmComparison.directionX(path[i], rtSize.width),
			nodePath.top + algorithmComparison.directionY(path[i], rtSize.height),
			0,
			0);
		nodePath = D2D1::RectF(
			nodePath.left,
			nodePath.top,
			nodePath.left + rtSize.width / algorithmComparison.getHorizontalSize(),
			nodePath.top + rtSize.height / algorithmComparison.getVerticalSize()
		);
		CD2DSolidColorBrush m_pPurpleBrush(m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::Purple), NULL, TRUE);
		m_pRenderTarget->FillRectangle(nodePath, &m_pPurpleBrush);
	}

	D2D1_RECT_F nodeStart = D2D1::RectF(
		rtSize.width / algorithmComparison.getHorizontalSize()*algorithmComparison.getxStart(),
		rtSize.height / algorithmComparison.getVerticalSize()*algorithmComparison.getyStart(),
		rtSize.width / algorithmComparison.getHorizontalSize()*(algorithmComparison.getxStart() + 1),
		rtSize.height / algorithmComparison.getVerticalSize()*(algorithmComparison.getyStart() + 1)
	);
	CD2DSolidColorBrush m_pGreenBrush(m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::Green), NULL, TRUE);
	m_pRenderTarget->FillRectangle(nodeStart, &m_pGreenBrush);

	D2D1_RECT_F nodeFinish = D2D1::RectF(
		rtSize.width / algorithmComparison.getHorizontalSize()*algorithmComparison.getxFinish(),
		rtSize.height / algorithmComparison.getVerticalSize()*algorithmComparison.getyFinish(),
		rtSize.width / algorithmComparison.getHorizontalSize()*(algorithmComparison.getxFinish() + 1),
		rtSize.height / algorithmComparison.getVerticalSize()*(algorithmComparison.getyFinish() + 1)
	);
	CD2DSolidColorBrush m_pRedBrush(m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::Red), NULL, TRUE);
	m_pRenderTarget->FillRectangle(nodeFinish, &m_pRedBrush);

	for(int i=0;i<algorithmComparison.getHorizontalSize();++i)
		for (int j = 0; j < algorithmComparison.getVerticalSize(); ++j)
			if (algorithmComparison.getGraphState(i, j) == 0)
			{
				D2D1_RECT_F nodeNone = D2D1::RectF(
					rtSize.width / algorithmComparison.getHorizontalSize()*i,
					rtSize.height / algorithmComparison.getVerticalSize()*j,
					rtSize.width / algorithmComparison.getHorizontalSize()*(i + 1),
					rtSize.height / algorithmComparison.getVerticalSize()*(j + 1)
				);
				CD2DSolidColorBrush m_pDarkGreyBrush(m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::DarkGray), NULL, TRUE);
				m_pRenderTarget->FillRectangle(nodeNone, &m_pDarkGreyBrush);
			}

	CString str;
	str = std::to_wstring(algorithmComparison.getStepNumber()).c_str();
	D2D1_RECT_F textBox = D2D1::RectF(0, 0, 50, 50);
	CD2DSolidColorBrush m_pBlackBrush(m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::Black), NULL, TRUE);
	m_pRenderTarget->DrawTextW(str, textBox, &m_pBlackBrush, 0, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);

	return TRUE;
}


void CChildView::OnDijkstra()
{
	KillTimer(timer);
	algorithmComparison.setCurrentAlgorithm(algorithmFactory.create(dijkstra));
	AfxGetMainWnd()->GetMenu()->CheckMenuRadioItem(ID_ALGORITHMS_DIJKSTRA,
		ID_ALGORITHMS_A, ID_ALGORITHMS_DIJKSTRA, MF_BYCOMMAND);
}


void CChildView::OnAstar()
{
	KillTimer(timer);
	algorithmComparison.setCurrentAlgorithm(algorithmFactory.create(astar));
	AfxGetMainWnd()->GetMenu()->CheckMenuRadioItem(ID_ALGORITHMS_DIJKSTRA,
		ID_ALGORITHMS_A, ID_ALGORITHMS_A, MF_BYCOMMAND);
}

void CChildView::OnStep()
{
	algorithmComparison.nextStep();

	Invalidate();
}

void CChildView::OnExecute()
{
	KillTimer(timer);
	timer = SetTimer(timer, algorithmComparison.getTime(), NULL);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (!algorithmComparison.nextStep())
	{
		Invalidate();
		UpdateWindow();
		KillTimer(timer);
	}

	Invalidate();

	if(!algorithmComparison.getPath().empty())
		KillTimer(timer);

	CWnd::OnTimer(nIDEvent);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	ScreenToClient(&mousePosition);

	RECT rc;
	GetClientRect(&rc);

	if (algorithmComparison.startFinishFlag())
		algorithmComparison.updateStart(
			mousePosition.x * algorithmComparison.getHorizontalSize() / rc.right,
			mousePosition.y * algorithmComparison.getVerticalSize() / rc.bottom);
	else
		algorithmComparison.updateFinish(
			mousePosition.x * algorithmComparison.getHorizontalSize() / rc.right,
			mousePosition.y * algorithmComparison.getVerticalSize() / rc.bottom);

	algorithmComparison.updateStartFinishFlag();
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	ScreenToClient(&mousePosition);

	RECT rc;
	GetClientRect(&rc);

	int row = mousePosition.x * algorithmComparison.getHorizontalSize() / rc.right;
	int col = mousePosition.y * algorithmComparison.getVerticalSize() / rc.bottom;

	algorithmComparison.setRequiredNodeWeight(algorithmComparison.getGraphState(row, col) == 0 ? 1 : 0);
	algorithmComparison.changeNodeState(row, col);

	Invalidate();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (GetAsyncKeyState(VK_RBUTTON) < 0)
	{
		RECT rc;
		GetClientRect(&rc);

		int row = point.x * algorithmComparison.getHorizontalSize() / rc.right;
		int col = point.y * algorithmComparison.getVerticalSize() / rc.bottom;

		POINT node;
		node.x = row;
		node.y = col;

		if (!algorithmComparison.sameNode(node))
			algorithmComparison.changeNodeState(row, col);

		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}

