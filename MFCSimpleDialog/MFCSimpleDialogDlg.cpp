
// MFCSimpleDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSimpleDialog.h"
#include "MFCSimpleDialogDlg.h"
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


// CMFCSimpleDialogDlg dialog




CMFCSimpleDialogDlg::CMFCSimpleDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCSimpleDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSimpleDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
}

BEGIN_MESSAGE_MAP(CMFCSimpleDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MY_MSGSEND,&CMFCSimpleDialogDlg::OnMyRecvMsg)//自定义消息
	ON_BN_CLICKED(IDC_MY_SEND, &CMFCSimpleDialogDlg::OnBnClickedMySend)
END_MESSAGE_MAP()


//-------------我的代码
DWORD WINAPI CMFCSimpleDialogDlg::recvFunc(LPVOID lpParam)//socket 的接收,在线程中,不加static 
{
	HWND hwnd=((RECVPARAM*)lpParam)->hwnd;
	SOCKET sock=((RECVPARAM*)lpParam)->sock;
	 
	wchar_t recvData[100];
	wchar_t showData[200];
	SOCKADDR_IN from;
	int len=sizeof(SOCKADDR_IN);
	while(TRUE)
	{

		int recvVal=recvfrom(sock,(char*)recvData,100,0,(SOCKADDR*)&from,&len);//二进制数据以char*表示
		if(SOCKET_ERROR==recvVal)
		{
			AfxMessageBox(L"recvfrom创建失败");
		}
		 
		
		char * ip=inet_ntoa(from.sin_addr);
		wchar_t ipTrans[50];
		mbstowcs(ipTrans,ip,50);

		swprintf(showData,300,L"%ls 说:%ls",ipTrans,recvData);//这里不能为%s,必须为%ls
		::PostMessageW(hwnd,WM_MY_MSGSEND,NULL,(LPARAM)showData);
	}
	return 1;
}
void CMFCSimpleDialogDlg::myInitSocket()
{
	AfxSocketInit();//要加afxsock.h在stdafx.h
	
	m_mysock=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==m_mysock)
	{
		AfxMessageBox(L"socket创建失败");
		return ;
	}
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(6000);
	addr.sin_addr.S_un.S_addr=htonl(ADDR_ANY);

	int len=sizeof(SOCKADDR_IN);
	int bindVal=bind(m_mysock,(SOCKADDR*)&addr,len);
	if(SOCKET_ERROR == bindVal)
	{
		AfxMessageBox(L"bind败");
		return ;
	}
	RECVPARAM *recvParam=new RECVPARAM();
	recvParam->hwnd=m_hWnd;
	recvParam->sock=m_mysock;
	HANDLE handle=CreateThread(NULL,0,recvFunc,(LPVOID)recvParam,0,NULL);//函数名是static成员
	CloseHandle(handle);



}
 LRESULT CMFCSimpleDialogDlg::OnMyRecvMsg(WPARAM wParam,LPARAM lParam)//WM_消息的接收
 {
	UNREFERENCED_PARAMETER(wParam);
	wchar_t* msg=(wchar_t*)lParam;
	CString content;
	CString result;
	GetDlgItemText(IDC_MY_MSG_RECV,content);
	result=content;
	result+="\r\n";//MultiLine设为true
	result+=msg;
	SetDlgItemText(IDC_MY_MSG_RECV,result);
	return 1;
 }
// CMFCSimpleDialogDlg message handlers

BOOL CMFCSimpleDialogDlg::OnInitDialog()
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
	
	//--------我的代码
	m_btn1.m_pAnother=&m_btn2;
	m_btn2.m_pAnother=&m_btn1;


	myInitSocket();


	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CMFCSimpleDialogDlg::OnBnClickedMySend()//按发送的响应
{
	DWORD ip;
	CIPAddressCtrl* ipCtrl=(CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1);
	ipCtrl->GetAddress(ip);
	
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(6000);
	addr.sin_addr.S_un.S_addr=htonl(ip);

	wchar_t sendMsg[100];
	GetDlgItemText(IDC_MY_MSG_SND,sendMsg,100);
 
	int len=wcslen(sendMsg)*2 + 2;
	char* send=(char*)sendMsg;//对英文的数据,这里debug时,只显示一个母,要sendData[2]
	sendto(m_mysock,send,len,0,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));//二进制数据,以char* 表示
	SetDlgItemText(IDC_MY_MSG_SND,L"");
}

void CMFCSimpleDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCSimpleDialogDlg::OnPaint()
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
HCURSOR CMFCSimpleDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

