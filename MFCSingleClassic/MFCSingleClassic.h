
// MFCSingleClassic.h : main header file for the MFCSingleClassic application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCSingleClassicApp:
// See MFCSingleClassic.cpp for the implementation of this class
//

class CMFCSingleClassicApp : public CWinApp
{
public:
	CMFCSingleClassicApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCSingleClassicApp theApp;
