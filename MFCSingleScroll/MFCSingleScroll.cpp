
// MFCSingleScroll.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCSingleScroll.h"
#include "MainFrm.h"

#include "MFCSingleScrollDoc.h"
#include "MFCSingleScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSingleScrollApp

BEGIN_MESSAGE_MAP(CMFCSingleScrollApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFCSingleScrollApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CMFCSingleScrollApp construction

CMFCSingleScrollApp::CMFCSingleScrollApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCSingleScroll.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMFCSingleScrollApp object

CMFCSingleScrollApp theApp;


// CMFCSingleScrollApp initialization

BOOL CMFCSingleScrollApp::InitInstance()
{
	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	//SetRegistryKey(_T("我的公司"));//我的修改
	//--------------我的代码   
	/*
	//----操作Windows/Win.ini文件
	::WriteProfileStringW(L"我的程序",L"李四",L"高级会员");

	CString str;
	::GetProfileStringW(L"我的程序",L"李四",L"空",str.GetBuffer(20),20);//GetBuffer()如要修改必须在调用其它CString方法前 ReleaseBuffer()
	AfxMessageBox(str);
	*/

	//----操作注册表,CWinApp类的
	/*
	this->WriteProfileStringW(L"我的软件",L"李四",L"高级会员");
	//默认位置 在 \HKEY_CURRENT_USER\Software\Local AppWizard-Generated Applications\MFCSingleScroll\我的软件
	//修改位置 在  \HKEY_CURRENT_USER\Software\我的公司\MFCSingleScroll\我的软件

	CString str;
	str=this->GetProfileString(L"我的软件",L"李四",L"空");//方法形式有变化
	AfxMessageBox(str);
	*/
	//--------------

	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	
	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFCSingleScrollDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMFCSingleScrollView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

// CMFCSingleScrollApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CMFCSingleScrollApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCSingleScrollApp customization load/save methods

void CMFCSingleScrollApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMFCSingleScrollApp::LoadCustomState()
{
}

void CMFCSingleScrollApp::SaveCustomState()
{
}

// CMFCSingleScrollApp message handlers



