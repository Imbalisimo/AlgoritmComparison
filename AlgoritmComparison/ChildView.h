
// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

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

};

