
// MFCSinglePipeParent.h : main header file for the MFCSinglePipeParent application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCSinglePipeParentApp:
// See MFCSinglePipeParent.cpp for the implementation of this class
//

class CMFCSinglePipeParentApp : public CWinAppEx
{
public:
	CMFCSinglePipeParentApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCSinglePipeParentApp theApp;
