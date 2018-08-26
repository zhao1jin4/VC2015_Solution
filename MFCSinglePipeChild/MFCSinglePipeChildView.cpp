
// MFCSinglePipeChildView.cpp : implementation of the CMFCSinglePipeChildView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSinglePipeChild.h"
#endif

#include "MFCSinglePipeChildDoc.h"
#include "MFCSinglePipeChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSinglePipeChildView

IMPLEMENT_DYNCREATE(CMFCSinglePipeChildView, CView)

BEGIN_MESSAGE_MAP(CMFCSinglePipeChildView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	//-------�ҵĴ���
	ON_COMMAND(ID_MY_CHILD_PIPE_READ, &CMFCSinglePipeChildView::OnMyChildPipeRead)
	ON_COMMAND(ID_MY_CHILD_PIPE_WIRTE, &CMFCSinglePipeChildView::OnMyChildPipeWirte)
	ON_COMMAND(ID_MY_NAMED_PIPE_CONN, &CMFCSinglePipeChildView::OnMyNamedPipeConn)
	ON_COMMAND(ID_MY_NAMED_PIPE_READ, &CMFCSinglePipeChildView::OnMyNamedPipeRead)
	ON_COMMAND(ID_MY_NAMED_PIPE_WRITE, &CMFCSinglePipeChildView::OnMyNamedPipeWrite)
	ON_COMMAND(ID_MY_MAILSLOT_CLIENT, &CMFCSinglePipeChildView::OnMyMailslotClient)
END_MESSAGE_MAP()

// CMFCSinglePipeChildView construction/destruction

CMFCSinglePipeChildView::CMFCSinglePipeChildView()
{
	//-------�ҵĴ���
	m_hRead=NULL;
	m_hWrite=NULL;
	m_hNamedPipe=NULL;
}

CMFCSinglePipeChildView::~CMFCSinglePipeChildView()
{
	//-------�ҵĴ���
	if(m_hRead)
		CloseHandle(m_hRead);
	if(m_hWrite)
		CloseHandle(m_hWrite);
	if(m_hNamedPipe)
		CloseHandle(m_hNamedPipe);
}

BOOL CMFCSinglePipeChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCSinglePipeChildView drawing

void CMFCSinglePipeChildView::OnDraw(CDC* /*pDC*/)
{
	CMFCSinglePipeChildDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CMFCSinglePipeChildView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCSinglePipeChildView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCSinglePipeChildView diagnostics

#ifdef _DEBUG
void CMFCSinglePipeChildView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCSinglePipeChildView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCSinglePipeChildDoc* CMFCSinglePipeChildView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSinglePipeChildDoc)));
	return (CMFCSinglePipeChildDoc*)m_pDocument;
}
#endif //_DEBUG
 
//-------�ҵĴ���
void CMFCSinglePipeChildView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_hRead=GetStdHandle(STD_INPUT_HANDLE);
	m_hWrite=GetStdHandle(STD_OUTPUT_HANDLE);
}

//-------�ҵĴ���
void CMFCSinglePipeChildView::OnMyChildPipeRead()
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
	AfxMessageBox((wchar_t *)buf);//
		
	//AfxMessageBox(CString(buf));//����

	AfxMessageBox(wBuf);
	*/
	AfxMessageBox(buf);
	 
}

//-------�ҵĴ���
void CMFCSinglePipeChildView::OnMyChildPipeWirte()
{
	//char* data="�ӽ��̲�������";//��֪�������ȷ������char* -> wchar_t *????????
	wchar_t *data =L"�ӽ��̲�������";
	DWORD writed;
	//if(! WriteFile(m_hWrite,data,strlen(data)+1,&writed,NULL))
	if(! WriteFile(m_hWrite,data,wcslen(data)*2 + 2,&writed,NULL))
	{
		AfxMessageBox(L"дPipeʧ��");
		return ;
	} 
}

//-------�ҵĴ��� ,�����ܵ�
void CMFCSinglePipeChildView::OnMyNamedPipeConn()
{
	if(!WaitNamedPipe(L"\\\\127.0.0.1\\pipe\\MyNamedPipe",NMPWAIT_WAIT_FOREVER))
	{
		AfxMessageBox(L"WaitNamedPipe ʧ��");
		return ;
	}

	m_hNamedPipe=CreateFile(L"\\\\127.0.0.1\\pipe\\MyNamedPipe",GENERIC_READ|GENERIC_WRITE,0,NULL,
				OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);//ʹ��OPEN_EXISTING
	if(INVALID_HANDLE_VALUE==m_hNamedPipe)
	{
		AfxMessageBox(L"�����ܵ� CreateFile ʧ��");
		return ;
	}

}

//-------�ҵĴ��� ,�����ܵ�
void CMFCSinglePipeChildView::OnMyNamedPipeRead()
{
	 wchar_t buf[200];//OK
	DWORD readed;
	if(! ReadFile(m_hNamedPipe,buf,200,&readed,NULL))
	{
		AfxMessageBox(L"�� NamedPipe ʧ��");
		return ;
	} 
	AfxMessageBox(buf);
	 
}

//-------�ҵĴ��� ,�����ܵ�
void CMFCSinglePipeChildView::OnMyNamedPipeWrite()
{ 
	wchar_t *data =L"NamedPipe Client ��������";
	DWORD writed;
	if(! WriteFile(m_hNamedPipe,data,wcslen(data)*2 + 2,&writed,NULL))
	{
		AfxMessageBox(L"д NamedPipe ʧ��");
		return ;
	} 
}

//-------�ҵĴ��� ,�ʲ�
void CMFCSinglePipeChildView::OnMyMailslotClient()
{
	 HANDLE hMailslot;
	 
	 //������127.0.0.1,��Ϊ�ǻ���UDP�ǹ㲥�ķ�ʽ,����ʹ��* ,������������������������յ�
	 hMailslot = CreateFile(L"\\\\*\\mailslot\\MyMailSlot",GENERIC_WRITE,FILE_SHARE_READ,NULL,
				OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);//OPEN_EXISTING,ֻ��GENERIC_WRITE, FILE_SHARE_READ
	if(INVALID_HANDLE_VALUE  == hMailslot)
	{
		AfxMessageBox(L"�ʲ� CreateFile ʧ��");
		return ;
	}
	wchar_t *data =L"Mailslot Client ��������";
	DWORD writed;
	if(! WriteFile(hMailslot,data,wcslen(data)*2 + 2 ,&writed,NULL))
	{
		AfxMessageBox(L"д Mailslot ʧ��");
		return ;
	} 
	CloseHandle(hMailslot);
}
