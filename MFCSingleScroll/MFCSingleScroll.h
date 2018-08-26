
// MFCSingleScroll.h : main header file for the MFCSingleScroll application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCSingleScrollApp:
// See MFCSingleScroll.cpp for the implementation of this class
//

class CMFCSingleScrollApp : public CWinAppEx
{
public:
	CMFCSingleScrollApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCSingleScrollApp theApp;
