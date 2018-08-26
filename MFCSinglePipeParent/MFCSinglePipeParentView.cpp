
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
	//-------�ҵĴ���
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
	: m_hRead(0),m_hWrite(0)//��ʼ��Ϊ0
{
	//-------�ҵĴ���
	 m_hNamedPipe=0;

}

CMFCSinglePipeParentView::~CMFCSinglePipeParentView()
{
	//-------�ҵĴ���
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

 
//------�ҵĴ���
void CMFCSinglePipeParentView::OnMyPipeRead()
{
	//�ܵ�û������ʱ,ȥ��������

	//char buf[200];//ʧ��?????
	wchar_t buf[200];//OK
	DWORD readed;
	if(! ReadFile(m_hRead,buf,200,&readed,NULL))
	{
		AfxMessageBox(L"��Pipeʧ��");
		return ;
	} 
	//char* ������������,ת��Ϊwchar_t *   ?????????????
	/*
	//---
	wchar_t wBuf[100];
	const char * cBuf=buf;
	mbstate_t state;
	//mbsrtowcs(wBuf,&cBuf,100,&state);//����
	//---
	//mbstowcs(wBuf,cBuf,100);//����
	//---
	AfxMessageBox((wchar_t *)buf);//��wchar_t* ���Ŀ���,char*���Ĳ���
		
	//AfxMessageBox(CString(buf));//����
	*/
	AfxMessageBox(buf);
	 
}

//------�ҵĴ���
void CMFCSinglePipeParentView::OnMyPipeWirte()
{
	//char* data="�����̲�������";//��֪�������ȷ������char* -> wchar_t *????????
	wchar_t *data =L"�����̲�������"; 
	DWORD writed;
	//if(! WriteFile(m_hWrite,data,strlen(data)+1,&writed,NULL))
	if(! WriteFile(m_hWrite,data,wcslen(data)*2 + 2,&writed,NULL))
	{
		AfxMessageBox(L"дPipeʧ��");
		return ;
	} 
}

//------�ҵĴ���
void CMFCSinglePipeParentView::OnMyPipeCreate()
{
	SECURITY_ATTRIBUTES attr;
	attr.nLength=sizeof(SECURITY_ATTRIBUTES);
	attr.bInheritHandle=TRUE;
	attr.lpSecurityDescriptor=NULL;//ʹ��Ĭ�ϵ�
	if(!CreatePipe(&m_hRead,&m_hWrite,&attr,0))//0ʹ��Ĭ�ϴ�С
	{
		AfxMessageBox(L"����Pipeʧ��");
		return ;
	}

	STARTUPINFO startInfo;
	ZeroMemory(&startInfo,sizeof(STARTUPINFO));//������memset
	startInfo.cb=sizeof(STARTUPINFO);//���Բ���,һ�������
	startInfo.dwFlags=STARTF_USESTDHANDLES;//��ʹ�����,ֻҪ����hStdInput,hStdOutput,hStdError
	startInfo.hStdInput=m_hRead;//�����̵ĸ��ӽ���
	startInfo.hStdOutput=m_hWrite;
	startInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);

	PROCESS_INFORMATION processInfo;
	//��ǰĿ¼��Solution��Ŀ¼,���� ./Debug/MFCSinglePipeParent �ķ�ʽ��ִ��
	if(!CreateProcess(L"../Debug/MFCSinglePipeChild.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&startInfo,&processInfo))
	{	
		long error=GetLastError();//Ҫ��CloseHandle֮ǰ����
		AfxMessageBox(L"�����ӽ���ʧ��");
		CloseHandle(m_hRead);
		CloseHandle(m_hWrite);
		m_hRead=NULL;//��ֹ����ʱ,�ٴιر�
		m_hWrite=NULL;
		return ;
	} 
	
	CloseHandle(processInfo.hThread);//�ӽ��̵��ں˶���,������һ
	CloseHandle(processInfo.hProcess);//�����е����߳�
	 

}

//------�����Ĺܵ�
void CMFCSinglePipeParentView::OnMyNamedPipeCreate()
{
	//pipe�����Ǳ����,���ʾ����
	m_hNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\MyNamedPipe",
								PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,
								PIPE_TYPE_BYTE|PIPE_READMODE_BYTE ,1,1024,1024,0,NULL);
	if(INVALID_HANDLE_VALUE == m_hNamedPipe)
	{
		AfxMessageBox(L"CreateNamedPipe ʧ��");
		m_hNamedPipe=NULL;
		return ;
	}

	HANDLE hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	if(!hEvent)
	{
		AfxMessageBox(L"CreateNamedPipe ʧ��");
		CloseHandle(m_hNamedPipe);
		m_hNamedPipe=NULL;
		return;
	}

	OVERLAPPED lapped;
	ZeroMemory(&lapped,sizeof(OVERLAPPED));
	lapped.hEvent=hEvent;

	if(!ConnectNamedPipe(m_hNamedPipe,&lapped))//�����FILE_FLAG_OVERLAPPED,��������OVERLAPPED��hEvent,����������ź�
	{
		if(ERROR_IO_PENDING != GetLastError())
		{
			AfxMessageBox(L"ConnectNamedPipe ʧ��");
			CloseHandle(m_hNamedPipe);
			m_hNamedPipe=NULL;
			CloseHandle(hEvent);

			return;
		}
		
	}
	if(WAIT_FAILED == WaitForSingleObject(hEvent,INFINITE))
	{
		AfxMessageBox(L"WaitForSingleObject ʧ��");
		CloseHandle(m_hNamedPipe);
		m_hNamedPipe=NULL;
		CloseHandle(hEvent);
		return;
	}
	CloseHandle(hEvent);//�õ���Ϣ���û�õ�
}

//------�����Ĺܵ�
void CMFCSinglePipeParentView::OnMyNamedPipeWrite()
{
	 wchar_t *data =L"NamedPipe Server ��������"; 
	DWORD writed;
	if(! WriteFile(m_hNamedPipe,data,wcslen(data)*2 + 2,&writed,NULL))
	{
		AfxMessageBox(L"дNamedPipeʧ��");
		return ;
	} 
}

//------�����Ĺܵ�
void CMFCSinglePipeParentView::OnMyNamedPipeRead()
{
	wchar_t buf[200];
	DWORD readed;
	if(! ReadFile(m_hNamedPipe,buf,200*2,&readed,NULL))
	{
		AfxMessageBox(L"��NamedPipeʧ��");
		return ;
	} 
	
	AfxMessageBox(buf);
	 
}

//-------�ҵĴ��� ,�ʲ�
void CMFCSinglePipeParentView::OnMyMailslotServer()
{
	 HANDLE hMailslot;
	 hMailslot = CreateMailslot(L"\\\\.\\mailslot\\MyMailSlot",0,MAILSLOT_WAIT_FOREVER,NULL);
	 if(INVALID_HANDLE_VALUE == hMailslot)
	 {
		AfxMessageBox(L"CreateMailslot ʧ��");
		return ;
	 }
	wchar_t buf[200];
	DWORD readed;
	if(! ReadFile(hMailslot,buf,200*2 ,&readed,NULL))//����
	{
		AfxMessageBox(L"�� Mailslot ʧ��");
		CloseHandle(hMailslot);
		return ;
	}
	AfxMessageBox(buf);
	CloseHandle(hMailslot);
}
