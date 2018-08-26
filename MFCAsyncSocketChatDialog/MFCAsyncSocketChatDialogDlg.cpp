
// MFCAsyncSocketChatDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAsyncSocketChatDialog.h"
#include "MFCAsyncSocketChatDialogDlg.h"
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


// CMFCAsyncSocketChatDialogDlg dialog




CMFCAsyncSocketChatDialogDlg::CMFCAsyncSocketChatDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCAsyncSocketChatDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_socket=0;//----我的代码
}
//-----------我的代码
CMFCAsyncSocketChatDialogDlg::~CMFCAsyncSocketChatDialogDlg()
{
	if(m_socket)
		closesocket(m_socket);
}
void CMFCAsyncSocketChatDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCAsyncSocketChatDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_SOCK_READ,&CMFCAsyncSocketChatDialogDlg::OnMyRecvSock)
	ON_BN_CLICKED(IDC_MY_SEND, &CMFCAsyncSocketChatDialogDlg::OnBnClickedMySend)
END_MESSAGE_MAP()


// CMFCAsyncSocketChatDialogDlg message handlers

BOOL CMFCAsyncSocketChatDialogDlg::OnInitDialog()
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

	MyInitSocket();//--------我的代码
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCAsyncSocketChatDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCAsyncSocketChatDialogDlg::OnPaint()
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
HCURSOR CMFCAsyncSocketChatDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//----------我的代码
LRESULT CMFCAsyncSocketChatDialogDlg::OnMyRecvSock(WPARAM wParam,LPARAM lParam)
{	
	//wParam表示哪个SOCKET,lParam高位是错误代码
	switch(LOWORD(lParam))//iEvent,如 FD_READ
	{
	case FD_READ:
		WSABUF buf;
		buf.len=200;
		buf.buf=new char[200];
		SOCKADDR_IN from;
		DWORD count=0;
		DWORD flag=0;
		int len=sizeof(SOCKADDR_IN);
		int ret=WSARecvFrom(m_socket,&buf,1,&count,&flag,(SOCKADDR*)&from,&len,NULL,NULL);
		if(SOCKET_ERROR==ret)
		{
			AfxMessageBox(L"WSARecvFrom 错误");
			delete[] buf.buf;//记得释放内存
			return false;
		}
		char * ip=inet_ntoa(from.sin_addr);
		wchar_t wIP[50];
		mbstowcs(wIP,ip,50);

		wchar_t wHost[50];
		hostent* ent=gethostbyaddr((char*)&from.sin_addr.S_un.S_addr,4,AF_INET);//AF_INET是IPv4,4个字节的IP地址
		mbstowcs(wHost,ent->h_name,50);;

		wchar_t *wContent = (wchar_t *)buf.buf;
		wchar_t wLineMsg[300];
		swprintf(wLineMsg,L"IP:%ls__host:%ls 说:%ls",wIP,wHost,wContent);//这里不能为%s,必须为%ls
		
		CString allMsg;
		GetDlgItemText(IDC_MY_RECV_TEXT,allMsg);
		allMsg +=wcscat(wLineMsg,L"\r\n");//Multiline设置为true
		SetDlgItemText(IDC_MY_RECV_TEXT,allMsg);
		delete[] buf.buf;//记得释放内存
		break;
	}
	return 1;
}
 
//----------我的代码
bool CMFCAsyncSocketChatDialogDlg::MyInitSocket(void)
{
	m_socket=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,0);
	if(INVALID_SOCKET== m_socket )
	{
		AfxMessageBox(L"socket 错误");
		int err=WSAGetLastError();// 没有WSAStartup,就不知道是什么错误
		showError(err);
		return false;
	}
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(6000);
	addr.sin_addr.S_un.S_addr=ADDR_ANY;

	int bindVal=bind(m_socket,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR==bindVal)
	{
		AfxMessageBox(L"bind 错误");
		return false;
	}
	int selVal=WSAAsyncSelect(m_socket,m_hWnd,UM_SOCK_READ,FD_READ);
	if(SOCKET_ERROR==selVal)
	{
		AfxMessageBox(L"WSAAsyncSelect 错误");
		return false;
	}
	return true;
}

//----------我的代码
void CMFCAsyncSocketChatDialogDlg::OnBnClickedMySend()
{
	SOCKADDR_IN toAddr;
	toAddr.sin_family=AF_INET;
	toAddr.sin_port=htons(6000);
	
	CString hostname;
	GetDlgItemText(IDC_MY_HOST_TEXT,hostname);
	if(hostname=="")
	{
		DWORD ip;
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(ip);
		toAddr.sin_addr.S_un.S_addr=htonl(ip);
	}else
	{
		const wchar_t* wHost=(wchar_t*)hostname.GetBuffer();
		char host[50];
		wcstombs(host,wHost,50);//要转换
		HOSTENT* hostEnt =gethostbyname(host);
		DWORD dest;
		dest=*((DWORD*)hostEnt->h_addr_list[0]);//h_addr_list是网络字节
		toAddr.sin_addr.S_un.S_addr=dest;//S_addr是unsinged long ,DWORD是 unsinged long
	}
	
	wchar_t userData[200];
	GetDlgItemText(IDC_MY_SEND_TEXT,userData,200);
	
	char* sendData=(char*)userData;//对英文的数据,这里debug时,只显示一个母,要sendData[2]
	int len=wcslen(userData)*2+2;
	
	WSABUF buf;
	buf.buf=sendData;
	buf.len=len;

	DWORD sendCount;
	int rtn=WSASendTo(m_socket,&buf,1,&sendCount,0,(SOCKADDR*)&toAddr,sizeof(SOCKADDR_IN),NULL,NULL);
	if(SOCKET_ERROR == rtn)
	{
		AfxMessageBox(L"WSASendTo 错误");
		int err=WSAGetLastError();
		showError(err);
		return ;
	}
	SetDlgItemText(IDC_MY_SEND_TEXT,L"");

}

void  CMFCAsyncSocketChatDialogDlg::showError(int err)
{
	switch (err)
		{
		case WSA_IO_PENDING://OK
			break;

		case WSAEACCES:
			break; 
		case WSAEADDRNOTAVAIL:
			break;
		case WSAEAFNOSUPPORT:
			break;
		case WSAECONNRESET:
			break;
		case WSAEDESTADDRREQ:
			break;
		case WSAEFAULT:
			break;
		case WSAEHOSTUNREACH:
			break; 
		case WSAEINPROGRESS:
			break;
		case WSAEINTR:
			break;
		case WSAEINVAL:
			break;
		case WSAEMSGSIZE:
			break;
		case WSAENETDOWN:
			break;
		case WSAENETRESET:
			break; 
		case WSAENETUNREACH:
			break;
		case WSAENOBUFS:
			break;
		case WSAENOTCONN:
			break;
		case WSAENOTSOCK:
			break;
		case WSAESHUTDOWN:
			break;
		case WSAEWOULDBLOCK:
			break; 
		case WSANOTINITIALISED:
			break;
	//	case WSA_IO_PENDING:
	//		break;
		case WSA_OPERATION_ABORTED:
			break;
	 
		}

}