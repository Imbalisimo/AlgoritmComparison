
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Comparison.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	Comparison algorithmComparison;

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPaint();

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg LRESULT OnDraw2d(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDijkstra();
	afx_msg void OnAstar();
	afx_msg void OnExecute();
	afx_msg void OnStep();
};

