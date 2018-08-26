
// MFCHookUseDialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCHookUseDialogApp:
// See MFCHookUseDialog.cpp for the implementation of this class
//

class CMFCHookUseDialogApp : public CWinApp
{
public:
	CMFCHookUseDialogApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCHookUseDialogApp theApp;