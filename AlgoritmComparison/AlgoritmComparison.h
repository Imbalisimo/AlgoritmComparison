
// AlgoritmComparison.h : main header file for the AlgoritmComparison application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAlgoritmComparisonApp:
// See AlgoritmComparison.cpp for the implementation of this class
//

class CAlgoritmComparisonApp : public CWinApp
{
public:
	CAlgoritmComparisonApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAlgoritmComparisonApp theApp;
