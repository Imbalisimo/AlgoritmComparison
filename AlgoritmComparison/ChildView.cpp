
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "AlgoritmComparison.h"
#include "ChildView.h"
#include "Comparison.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	EnableD2DSupport();
	algorithmComparison.init(30, 15);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CChildView::OnDraw2d)
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

	D2D1_RECT_F rectangle1 = D2D1::RectF(
		rtSize.width / 2 - 50.0f,
		rtSize.height / 2 - 50.0f,
		rtSize.width / 2 + 50.0f,
		rtSize.height / 2 + 50.0f
	);

	D2D1_RECT_F rectangle2 = D2D1::RectF(
		rtSize.width / 2 - 100.0f,
		rtSize.height / 2 - 100.0f,
		rtSize.width / 2 + 100.0f,
		rtSize.height / 2 + 100.0f
	);

	// Draw a filled rectangle.
	m_pRenderTarget->FillRectangle(rectangle1, &m_pLightSlateGrayBrush);

	return TRUE;
}
