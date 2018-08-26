
// MFCSinglePipeParentView.cpp : implementation of the CMFCSinglePipeParentView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSinglePipeParent.h"
#endif

#include "MFCSinglePipeParentDoc.h"
#include "MFCSinglePipeParentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSinglePipeParentView

IMPLEMENT_DYNCREATE(CMFCSinglePipeParentView, CView)

BEGIN_MESSAGE_MAP(CMFCSinglePipeParentView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	//-------我的代码
	ON_COMMAND(ID_MY_PIPE_READ, &CMFCSinglePipeParentView::OnMyPipeRead)
	ON_COMMAND(ID_MY_PIPE_WIRTE, &CMFCSinglePipeParentView::OnMyPipeWirte)
	ON_COMMAND(ID_MY_PIPE_CREATE, &CMFCSinglePipeParentView::OnMyPipeCreate)
	ON_COMMAND(ID_MY_NAMED_PIPE_CREATE, &CMFCSinglePipeParentView::OnMyNamedPipeCreate)
	ON_COMMAND(ID_MY_NAMED_PIPE_WRITE, &CMFCSinglePipeParentView::OnMyNamedPipeWrite)
	ON_COMMAND(ID_MY_NAMED_PIPE_READ, &CMFCSinglePipeParentView::OnMyNamedPipeRead)
	ON_COMMAND(ID_MY_MAILSLOT_SERVER, &CMFCSinglePipeParentView::OnMyMailslotServer)
END_MESSAGE_MAP()

// CMFCSinglePipeParentView construction/destruction

CMFCSinglePipeParentView::CMFCSinglePipeParentView()
	: m_hRead(0),m_hWrite(0)//初始化为0
{
	//-------我的代码
	 m_hNamedPipe=0;

}

CMFCSinglePipeParentView::~CMFCSinglePipeParentView()
{
	//-------我的代码
	if(m_hRead)
		CloseHandle(m_hRead);
	if(m_hWrite)
		CloseHandle(m_hWrite);

	if(m_hNamedPipe)
		CloseHandle(m_hNamedPipe);
 
}

BOOL CMFCSinglePipeParentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCSinglePipeParentView drawing

void CMFCSinglePipeParentView::OnDraw(CDC* /*pDC*/)
{
	CMFCSinglePipeParentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CMFCSinglePipeParentView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCSinglePipeParentView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCSinglePipeParentView diagnostics

#ifdef _DEBUG
void CMFCSinglePipeParentView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCSinglePipeParentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCSinglePipeParentDoc* CMFCSinglePipeParentView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSinglePipeParentDoc)));
	return (CMFCSinglePipeParentDoc*)m_pDocument;
}
#endif //_DEBUG

 
//------我的代码
void CMFCSinglePipeParentView::OnMyPipeRead()
{
	//管道没有数据时,去读会阻塞

	//char buf[200];//失败?????
	wchar_t buf[200];//OK
	DWORD readed;
	if(! ReadFile(m_hRead,buf,200,&readed,NULL))
	{
		AfxMessageBox(L"读Pipe失败");
		return ;
	} 
	//char* 是正常的中文,转换为wchar_t *   ?????????????
	/*
	//---
	wchar_t wBuf[100];
	const char * cBuf=buf;
	mbstate_t state;
	//mbsrtowcs(wBuf,&cBuf,100,&state);//不行
	//---
	//mbstowcs(wBuf,cBuf,100);//不行
	//---
	AfxMessageBox((wchar_t *)buf);//是wchar_t* 中文可以,char*中文不行
		
	//AfxMessageBox(CString(buf));//不行
	*/
	AfxMessageBox(buf);
	 
}

//------我的代码
void CMFCSinglePipeParentView::OnMyPipeWirte()
{
	//char* data="父进程测试数据";//不知道如把正确的中文char* -> wchar_t *????????
	wchar_t *data =L"父进程测试数据"; 
	DWORD writed;
	//if(! WriteFile(m_hWrite,data,strlen(data)+1,&writed,NULL))
	if(! WriteFile(m_hWrite,data,wcslen(data)*2 + 2,&writed,NULL))
	{
		AfxMessageBox(L"写Pipe失败");
		return ;
	} 
}

//------我的代码
void CMFCSinglePipeParentView::OnMyPipeCreate()
{
	SECURITY_ATTRIBUTES attr;
	attr.nLength=sizeof(SECURITY_ATTRIBUTES);
	attr.bInheritHandle=TRUE;
	attr.lpSecurityDescriptor=NULL;//使用默认的
	if(!CreatePipe(&m_hRead,&m_hWrite,&attr,0))//0使用默认大小
	{
		AfxMessageBox(L"建立Pipe失败");
		return ;
	}

	STARTUPINFO startInfo;
	ZeroMemory(&startInfo,sizeof(STARTUPINFO));//类似于memset
	startInfo.cb=sizeof(STARTUPINFO);//可以不调,一般是设的
	startInfo.dwFlags=STARTF_USESTDHANDLES;//如使用这个,只要设置hStdInput,hStdOutput,hStdError
	startInfo.hStdInput=m_hRead;//父进程的给子进程
	startInfo.hStdOutput=m_hWrite;
	startInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);

	PROCESS_INFORMATION processInfo;
	//当前目录是Solution的目录,即以 ./Debug/MFCSinglePipeParent 的方式来执行
	if(!CreateProcess(L"../Debug/MFCSinglePipeChild.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&startInfo,&processInfo))
	{	
		long error=GetLastError();//要在CloseHandle之前调用
		AfxMessageBox(L"建立子进程失败");
		CloseHandle(m_hRead);
		CloseHandle(m_hWrite);
		m_hRead=NULL;//防止析构时,再次关闭
		m_hWrite=NULL;
		return ;
	} 
	
	CloseHandle(processInfo.hThread);//子进程的内核对象,计数减一
	CloseHandle(processInfo.hProcess);//进程中的主线程
	 

}

//------命名的管道
void CMFCSinglePipeParentView::OnMyNamedPipeCreate()
{
	//pipe名字是必须的,点表示本机
	m_hNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\MyNamedPipe",
								PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,
								PIPE_TYPE_BYTE|PIPE_READMODE_BYTE ,1,1024,1024,0,NULL);
	if(INVALID_HANDLE_VALUE == m_hNamedPipe)
	{
		AfxMessageBox(L"CreateNamedPipe 失败");
		m_hNamedPipe=NULL;
		return ;
	}

	HANDLE hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	if(!hEvent)
	{
		AfxMessageBox(L"CreateNamedPipe 失败");
		CloseHandle(m_hNamedPipe);
		m_hNamedPipe=NULL;
		return;
	}

	OVERLAPPED lapped;
	ZeroMemory(&lapped,sizeof(OVERLAPPED));
	lapped.hEvent=hEvent;

	if(!ConnectNamedPipe(m_hNamedPipe,&lapped))//如果有FILE_FLAG_OVERLAPPED,必须设置OVERLAPPED的hEvent,操作完成有信号
	{
		if(ERROR_IO_PENDING != GetLastError())
		{
			AfxMessageBox(L"ConnectNamedPipe 失败");
			CloseHandle(m_hNamedPipe);
			m_hNamedPipe=NULL;
			CloseHandle(hEvent);

			return;
		}
		
	}
	if(WAIT_FAILED == WaitForSingleObject(hEvent,INFINITE))
	{
		AfxMessageBox(L"WaitForSingleObject 失败");
		CloseHandle(m_hNamedPipe);
		m_hNamedPipe=NULL;
		CloseHandle(hEvent);
		return;
	}
	CloseHandle(hEvent);//得到信息后就没用的
}

//------命名的管道
void CMFCSinglePipeParentView::OnMyNamedPipeWrite()
{
	 wchar_t *data =L"NamedPipe Server 测试数据"; 
	DWORD writed;
	if(! WriteFile(m_hNamedPipe,data,wcslen(data)*2 + 2,&writed,NULL))
	{
		AfxMessageBox(L"写NamedPipe失败");
		return ;
	} 
}

//------命名的管道
void CMFCSinglePipeParentView::OnMyNamedPipeRead()
{
	wchar_t buf[200];
	DWORD readed;
	if(! ReadFile(m_hNamedPipe,buf,200*2,&readed,NULL))
	{
		AfxMessageBox(L"读NamedPipe失败");
		return ;
	} 
	
	AfxMessageBox(buf);
	 
}

//-------我的代码 ,邮槽
void CMFCSinglePipeParentView::OnMyMailslotServer()
{
	 HANDLE hMailslot;
	 hMailslot = CreateMailslot(L"\\\\.\\mailslot\\MyMailSlot",0,MAILSLOT_WAIT_FOREVER,NULL);
	 if(INVALID_HANDLE_VALUE == hMailslot)
	 {
		AfxMessageBox(L"CreateMailslot 失败");
		return ;
	 }
	wchar_t buf[200];
	DWORD readed;
	if(! ReadFile(hMailslot,buf,200*2 ,&readed,NULL))//阻塞
	{
		AfxMessageBox(L"读 Mailslot 失败");
		CloseHandle(hMailslot);
		return ;
	}
	AfxMessageBox(buf);
	CloseHandle(hMailslot);
}
