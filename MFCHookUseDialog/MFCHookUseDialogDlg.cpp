
// MFCHookUseDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCHookUseDialog.h"
#include "MFCHookUseDialogDlg.h"
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


// CMFCHookUseDialogDlg dialog




CMFCHookUseDialogDlg::CMFCHookUseDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCHookUseDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHookUseDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCHookUseDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()




/* 
//�Ե�ǰ���̵������߳�
//--�ҵĴ���
HWND g_hWnd;
HHOOK g_hMouseHook;
HHOOK g_hKeyHook;
//--�ҵĴ���
LRESULT CALLBACK mouseHookFunc(int nCode,WPARAM wParam,LPARAM lParam)//�ص�����ԭ��
{
	return 1;//���ط�0,��ʾ��Ϣ�Ѿ�����,�������´���
}
//--�ҵĴ���
LRESULT CALLBACK keyHookFunc(int nCode,WPARAM wParam,LPARAM lParam)//�ص�����ԭ��
{
	if(VK_SPACE == wParam || VK_RETURN == wParam ) //�� WH_KEYBOARD,wParam��ʾ���������
		return 1; //���ط�0,��ʾ��Ϣ�Ѿ�����,�������´���
	if(VK_F4 == wParam && 1 ==(lParam>>29 & 0x01) )//��29λΪ1,��ʾalt��������
	{
		UnhookWindowsHookEx(g_hMouseHook);
		UnhookWindowsHookEx(g_hKeyHook);
		::PostMessage(g_hWnd,WM_CLOSE,0,0);//�첽,��ͬ��ʹ��SendMessage
		return 1;
	}
	return CallNextHookEx(g_hMouseHook,nCode,wParam,lParam);
}
*/

//--�ҵĴ��� def�ļ� _declspec(dllimport) ���Բ���
 void MyHook(HWND hWnd);


// CMFCHookUseDialogDlg message handlers

BOOL CMFCHookUseDialogDlg::OnInitDialog()
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
	//-----�ҵĴ���
	/* //�Ե�ǰ���̵������߳�
	g_hWnd=m_hWnd;
	g_hMouseHook=SetWindowsHookEx(WH_MOUSE,mouseHookFunc,NULL,GetCurrentThreadId());//��ǰ���̵��߳�dll�������ΪNULL
	g_hKeyHook=SetWindowsHookEx(WH_KEYBOARD,keyHookFunc,NULL,GetCurrentThreadId());//��ǰ���̵��߳�dll�������ΪNULL
	*/
	
	
	//�Ե�ǰ����������߳�,links�� ConsoleHookDLL.lib
	MyHook(m_hWnd);//�粻������,Ҫ�鿴DllMain��ʽ�Ƿ�����,�Ҳ�����cmd�����а�alt+f2,���Ӧ��Ҳ��ر�???,���ڼ��±��оͲ���
	/*
	//����ȫ��,����ʾ���
	int xScreen,yScreen;
	xScreen=GetSystemMetrics(SM_CXSCREEN);
	yScreen=GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(&wndTopMost,0,0,xScreen,yScreen,SWP_SHOWWINDOW);
	//�ҵĲ���ʱû�а취�л�����������,������Ϊ�Ǽ���,������XP��ԭ��????
	*/




	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCHookUseDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCHookUseDialogDlg::OnPaint()
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
HCURSOR CMFCHookUseDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

