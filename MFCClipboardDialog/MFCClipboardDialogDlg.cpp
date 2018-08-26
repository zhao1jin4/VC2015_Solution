
// MFCClipboardDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCClipboardDialog.h"
#include "MFCClipboardDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCClipboardDialogDlg dialog




CMFCClipboardDialogDlg::CMFCClipboardDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCClipboardDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClipboardDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCClipboardDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MY_COPY_BTN, &CMFCClipboardDialogDlg::OnBnClickedMyCopyBtn)
	ON_BN_CLICKED(IDC_MY_PASTE_BTN, &CMFCClipboardDialogDlg::OnBnClickedMyPasteBtn)
END_MESSAGE_MAP()


// CMFCClipboardDialogDlg message handlers

BOOL CMFCClipboardDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCClipboardDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCClipboardDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCClipboardDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCClipboardDialogDlg::OnBnClickedMyCopyBtn()
{
	CString userText;
	GetDlgItemText(IDC_MY_COPY_TEXT,userText);//变长的CString
	int strLen=userText.GetLength();

	if(OpenClipboard())//open, 如已经打开 再打就出错
	{
		EmptyClipboard();//清空已有的数把
		HANDLE hClip=GlobalAlloc(GMEM_MOVEABLE,strLen*2 + 2);//返回HGLOBAL就是HANDLE
	
		wchar_t * clipData=(wchar_t*)GlobalLock(hClip);//lock
		wcscpy(clipData,userText.GetBuffer());//中文
		GlobalUnlock(hClip);//unlock

		SetClipboardData(CF_UNICODETEXT,hClip);// CF_TEXT只对ASCII
		CloseClipboard();//close
	}
}


void CMFCClipboardDialogDlg::OnBnClickedMyPasteBtn()
{
	if(OpenClipboard())//open, 如已经打开 再打就出错
	{
		if(IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			HANDLE hClip=GetClipboardData(CF_UNICODETEXT);// CF_TEXT只对ASCII
		
			wchar_t * clipData=(wchar_t*)GlobalLock(hClip);//lock
			SetDlgItemText(IDC_MY_PASTE_TEXT,CString(clipData));
			GlobalUnlock(hClip);//unlock
		}
		CloseClipboard();//close  正确的置
	}
	
}
