
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
	//------------我的代码
 
	
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
	//----方式二,画的时候看不到,要刷新的时候可以看到
	/*
	//------
	HMETAFILE h_metatFile;
	h_metatFile=m_metaFileDC.Close();
	pDC->PlayMetaFile(h_metatFile);//使用PDC
	
	m_metaFileDC.Create();
	
	m_metaFileDC.PlayMetaFile(h_metatFile);//保存上一次的
	::DeleteMetaFile(h_metatFile);
	//------Enh
	*/
	//----方式三
	/*
	CRect rect;
	GetClientRect (&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_compatibleDC,0,0,SRCCOPY);
	*/
	//----方式四,使用自己的对象
	int i;
	int len;
	//方式一
	/*
	len=m_allLine.GetSize();
	for (i=0;i<len;i++)
	{
		MyShape* shape=(MyShape*)m_allLine.GetAt(i);
		shape->Draw(pDC);
	}*/

	//方式二
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

//---在窗口建立之后第一个被调用 ,OnDraw之前调用
//建立项目时要选择MFC Standard ，如选择windows style,visual studio style 会有ListView文件
void CMFCSingleScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT,CSize(800,600));//对于建立项目是基于View ，修改为基于ScrollView的要加这个，运行时才不会报错，就会有滚动条出现

}


void CMFCSingleScrollView::OnLButtonDown(UINT nFlags, CPoint point)
{
	  m_start=point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCSingleScrollView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//-------方式一
	//CClientDC dc(this);
	//dc.MoveTo(m_start);
	//dc.LineTo(point);
	//要在保存之前,对有Scroll的View,否则在滚动到下方时再画,刷新时位置是错的
	//OnPrepareDC(&dc);
	//dc.DPtoLP(&m_start);
	//dc.DPtoLP(&point);
	
	//CRect* rect=new CRect(m_start,point);
	//m_allLine.Add(rect);

	//-------方式二
	//构造器中调用 Create()
	//m_metaFileDC.MoveTo(m_start);
	//m_metaFileDC.LineTo(point);

	//-------方式三
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
		m_compatibleDC.BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);//对CreateCompatibleBitmap 要在SelectObject之后


	}
	//dc.MoveTo(m_start);//是为了也显示
	//dc.LineTo(point);
	m_compatibleDC.MoveTo(m_start);
	m_compatibleDC.LineTo(point);
	*/
	//-------方式四 ,使用自己的对象
	CClientDC dc(this);
	MyShape *shape=new MyShape(T_LINE,m_start,point);//要使用指针new,在Doc类中的DeleteContents方法中释放
	shape->Draw(&dc);

	//m_allLine.Add(shape);//方式一
	GetDocument()->m_allObj.Add(shape);//方式二

	CScrollView::OnLButtonUp(nFlags, point);
}

/*
void CMFCSingleScrollView::OnPaint()//不使用父类的OnＰaint方法
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

	OnPrepareDC(&dc);//父类中有调用
	OnDraw(&dc);//要手工调用 
	// Do not call CScrollView::OnPaint() for painting messages
}
*/

	//对应方式二
	void CMFCSingleScrollView::OnDrawSave()
	{
		//------
		HMETAFILE h_metaFile=m_metaFileDC.Close();
		CopyMetaFile(h_metaFile,L"myMetaFile.wmf");
		m_metaFileDC.Create();
		DeleteMetaFile(h_metaFile);
		//------Enh
		//文件名扩展名使用.emf
	}

	//对应方式二
	void CMFCSingleScrollView::OnDrawOpen()
	{
		//------
		HMETAFILE h_metaFile=GetMetaFile(L"myMetaFile.wmf");
		m_metaFileDC.PlayMetaFile(h_metaFile);
		DeleteMetaFile(h_metaFile);
		Invalidate();
		//------Enh

		//CRect rect(0,0,800,600);//不知如何指定 
	}
