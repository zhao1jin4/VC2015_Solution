
// MFCAsyncSocketChatDialog.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MFCAsyncSocketChatDialog.h"
#include "MFCAsyncSocketChatDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAsyncSocketChatDialogApp

BEGIN_MESSAGE_MAP(CMFCAsyncSocketChatDialogApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCAsyncSocketChatDialogApp construction

CMFCAsyncSocketChatDialogApp::CMFCAsyncSocketChatDialogApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
  //----------------------�ҵĴ���

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
 
	wVersionRequested = MAKEWORD( 2, 2 );//ʹ��2.2�汾
 
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return ;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
			HIBYTE( wsaData.wVersion ) != 2) {
		WSACleanup( );
		return ; 
	}
	 
}
//--------�ҵĴ���
CMFCAsyncSocketChatDialogApp::~CMFCAsyncSocketChatDialogApp()
{
	 WSACleanup();
}
 

// The one and only CMFCAsyncSocketChatDialogApp object

CMFCAsyncSocketChatDialogApp theApp;


// CMFCAsyncSocketChatDialogApp initialization

BOOL CMFCAsyncSocketChatDialogApp::InitInstance()
{
	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CMFCAsyncSocketChatDialogDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

