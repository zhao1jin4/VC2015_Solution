
// MFCSingleScrollView.cpp : implementation of the CMFCSingleScrollView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSingleScroll.h"
#endif

#include "MFCSingleScrollDoc.h"
#include "MFCSingleScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSingleScrollView

IMPLEMENT_DYNCREATE(CMFCSingleScrollView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCSingleScrollView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//ON_WM_PAINT()
	ON_COMMAND(ID_DRAW_SAVE, &CMFCSingleScrollView::OnDrawSave)
	ON_COMMAND(ID_DRAW_OPEN, &CMFCSingleScrollView::OnDrawOpen)
END_MESSAGE_MAP()

// CMFCSingleScrollView construction/destruction

CMFCSingleScrollView::CMFCSingleScrollView()
{
	// TODO: add construction code here
	m_start=0;
	m_metaFileDC.Create();
}

CMFCSingleScrollView::~CMFCSingleScrollView()
{
}

BOOL CMFCSingleScrollView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CMFCSingleScrollView drawing

void CMFCSingleScrollView::OnDraw(CDC* pDC)
{
	CMFCSingleScrollDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//------------�ҵĴ���
 
	
	//CBrush * brush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	//pDC->SelectObject(brush);
	/*CRect* rect;
	int i;
	for (i=0;i<m_allLine.GetSize();i++)
	{
		rect=(CRect*)m_allLine.GetAt(i);
		
		pDC->MoveTo(rect->left,rect->top);
		pDC->LineTo(rect->right,rect->bottom);
	}
	*/
	//----��ʽ��,����ʱ�򿴲���,Ҫˢ�µ�ʱ����Կ���
	/*
	//------
	HMETAFILE h_metatFile;
	h_metatFile=m_metaFileDC.Close();
	pDC->PlayMetaFile(h_metatFile);//ʹ��PDC
	
	m_metaFileDC.Create();
	
	m_metaFileDC.PlayMetaFile(h_metatFile);//������һ�ε�
	::DeleteMetaFile(h_metatFile);
	//------Enh
	*/
	//----��ʽ��
	/*
	CRect rect;
	GetClientRect (&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_compatibleDC,0,0,SRCCOPY);
	*/
	//----��ʽ��,ʹ���Լ��Ķ���
	int i;
	int len;
	//��ʽһ
	/*
	len=m_allLine.GetSize();
	for (i=0;i<len;i++)
	{
		MyShape* shape=(MyShape*)m_allLine.GetAt(i);
		shape->Draw(pDC);
	}*/

	//��ʽ��
	len=GetDocument()->m_allObj.GetSize();
	for (i=0;i<len;i++)
	{
		MyShape* shape=(MyShape*)GetDocument()->m_allObj.GetAt(i);
		shape->Draw(pDC);
	}
	// TODO: add draw code for native data here
}

void CMFCSingleScrollView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCSingleScrollView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCSingleScrollView diagnostics

#ifdef _DEBUG
void CMFCSingleScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCSingleScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCSingleScrollDoc* CMFCSingleScrollView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSingleScrollDoc)));
	return (CMFCSingleScrollDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCSingleScrollView message handlers

//---�ڴ��ڽ���֮���һ�������� ,OnDraw֮ǰ����
//������ĿʱҪѡ��MFC Standard ����ѡ��windows style,visual studio style ����ListView�ļ�
void CMFCSingleScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT,CSize(800,600));//���ڽ�����Ŀ�ǻ���View ���޸�Ϊ����ScrollView��Ҫ�����������ʱ�Ų��ᱨ���ͻ��й���������

}


void CMFCSingleScrollView::OnLButtonDown(UINT nFlags, CPoint point)
{
	  m_start=point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCSingleScrollView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//-------��ʽһ
	//CClientDC dc(this);
	//dc.MoveTo(m_start);
	//dc.LineTo(point);
	//Ҫ�ڱ���֮ǰ,����Scroll��View,�����ڹ������·�ʱ�ٻ�,ˢ��ʱλ���Ǵ��
	//OnPrepareDC(&dc);
	//dc.DPtoLP(&m_start);
	//dc.DPtoLP(&point);
	
	//CRect* rect=new CRect(m_start,point);
	//m_allLine.Add(rect);

	//-------��ʽ��
	//�������е��� Create()
	//m_metaFileDC.MoveTo(m_start);
	//m_metaFileDC.LineTo(point);

	//-------��ʽ��
	/*
	CClientDC dc(this);
	if(!m_compatibleDC.m_hDC)
	{
		m_compatibleDC.CreateCompatibleDC(&dc);
		CRect rect;
		GetClientRect(&rect);
		CBitmap map;
		map.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
		m_compatibleDC.SelectObject(&map);
		m_compatibleDC.BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);//��CreateCompatibleBitmap Ҫ��SelectObject֮��


	}
	//dc.MoveTo(m_start);//��Ϊ��Ҳ��ʾ
	//dc.LineTo(point);
	m_compatibleDC.MoveTo(m_start);
	m_compatibleDC.LineTo(point);
	*/
	//-------��ʽ�� ,ʹ���Լ��Ķ���
	CClientDC dc(this);
	MyShape *shape=new MyShape(T_LINE,m_start,point);//Ҫʹ��ָ��new,��Doc���е�DeleteContents�������ͷ�
	shape->Draw(&dc);

	//m_allLine.Add(shape);//��ʽһ
	GetDocument()->m_allObj.Add(shape);//��ʽ��

	CScrollView::OnLButtonUp(nFlags, point);
}

/*
void CMFCSingleScrollView::OnPaint()//��ʹ�ø����On��aint����
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

	OnPrepareDC(&dc);//�������е���
	OnDraw(&dc);//Ҫ�ֹ����� 
	// Do not call CScrollView::OnPaint() for painting messages
}
*/

	//��Ӧ��ʽ��
	void CMFCSingleScrollView::OnDrawSave()
	{
		//------
		HMETAFILE h_metaFile=m_metaFileDC.Close();
		CopyMetaFile(h_metaFile,L"myMetaFile.wmf");
		m_metaFileDC.Create();
		DeleteMetaFile(h_metaFile);
		//------Enh
		//�ļ�����չ��ʹ��.emf
	}

	//��Ӧ��ʽ��
	void CMFCSingleScrollView::OnDrawOpen()
	{
		//------
		HMETAFILE h_metaFile=GetMetaFile(L"myMetaFile.wmf");
		m_metaFileDC.PlayMetaFile(h_metaFile);
		DeleteMetaFile(h_metaFile);
		Invalidate();
		//------Enh

		//CRect rect(0,0,800,600);//��֪���ָ�� 
	}
