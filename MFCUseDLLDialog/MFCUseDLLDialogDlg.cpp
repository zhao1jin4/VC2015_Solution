
// MFCUseDLLDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCUseDLLDialog.h"
#include "MFCUseDLLDialogDlg.h"
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


// CMFCUseDLLDialogDlg dialog




CMFCUseDLLDialogDlg::CMFCUseDLLDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCUseDLLDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCUseDLLDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCUseDLLDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCUseDLLDialogDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CMFCUseDLLDialogDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CMFCUseDLLDialogDlg::OnBnClickedButtonOutput)
	ON_BN_CLICKED(IDC_BUTTON_MULTI, &CMFCUseDLLDialogDlg::OnBnClickedButtonMulti)
END_MESSAGE_MAP()


// CMFCUseDLLDialogDlg message handlers

BOOL CMFCUseDLLDialogDlg::OnInitDialog()
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

void CMFCUseDLLDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCUseDLLDialogDlg::OnPaint()
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
HCURSOR CMFCUseDLLDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/* */
//---��ʽ1
//extern int add(int a,int b);
//ConosleDLL.lib���Ƶ�MFCUseDLLDialog��ĿĿ¼��,��.hͬĿ¼�� 
//��MFCUseDLLDialog��Ŀ��ConosleDLL��Ŀ�������Ľ�������� Solution/DebugĿ¼��,�����ǿ����ҵ���

_declspec(dllimport) int add(int a,int b);//֪������dll��,�ٶȿ�

void CMFCUseDLLDialogDlg::OnBnClickedButtonAdd() //---links�м�ConosleDLL.lib,
{
	CString str;
	str.Format(L"a+b=%d",add(2,3));
	AfxMessageBox(str);

}
 
//---��ʽ2 ʹ��.h
//������û��ʹ�� #define MY_API
#include "../ConsoleDLL/MyMath.h" 
void CMFCUseDLLDialogDlg::OnBnClickedButtonSub() //---links�м� ConsoleDLL.lib
{
	CString str;
	str.Format(L"a-b=%d",subtract(2,3));
	AfxMessageBox(str);
}
void CMFCUseDLLDialogDlg::OnBnClickedButtonOutput() //---links�м� ConsoleDLL.lib
{
	 Point p;
	 p.output(20,20);
}
 void CMFCUseDLLDialogDlg::OnBnClickedButtonMulti()//---links�м� ConsoleDLL.lib
 {
	CString str;
	str.Format(L"a*b=%d",multi(2,3));//��def��
	AfxMessageBox(str);
 }

/*
//---��̬����dll,���ü� ConsoleDLL.lib,����#include, dumpbin -imports .exeû��.dll��
 void CMFCUseDLLDialogDlg::OnBnClickedButtonMulti()//���def�ļ��е�
 {
	typedef int (_stdcall *MathFunc )(int a,int b);//_stdcall ��λ��
	//HMODULE�ɺ�HINSTANCE����ʹ��
	HMODULE hModule=LoadLibrary(L"ConsoleDLL.dll");//Ҫ��.dll
	//MathFunc pMulti=(MathFunc)GetProcAddress(hModule,"multi");//������,ʹ��dumpbin -export .dll,ע�����ָı�
	MathFunc pMulti=(MathFunc)GetProcAddress(hModule,MAKEINTRESOURCEA(2));//����������ordinal���
	if(!pMulti)
		AfxMessageBox(L"��̬����dllʧ��");
	CString str;
	str.Format(L"a*b=%d",pMulti(4,5));
	AfxMessageBox(str);

	FreeLibrary(hModule);//����Ժ�ʹ����,����������
 }

void CMFCUseDLLDialogDlg::OnBnClickedButtonSub()//��̬����dll,�����ʵ��
{
}
void CMFCUseDLLDialogDlg::OnBnClickedButtonAdd()
{
}
void CMFCUseDLLDialogDlg::OnBnClickedButtonOutput() 
{
}
*/