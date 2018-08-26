
// MFCAsyncSocketChatDialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCAsyncSocketChatDialogApp:
// See MFCAsyncSocketChatDialog.cpp for the implementation of this class
//

class CMFCAsyncSocketChatDialogApp : public CWinApp
{
public:
	CMFCAsyncSocketChatDialogApp();
	~CMFCAsyncSocketChatDialogApp();//手工加的

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCAsyncSocketChatDialogApp theApp;