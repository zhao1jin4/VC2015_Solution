
// MFCSingleToolBarView.cpp : implementation of the CMFCSingleToolBarView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSingleToolBar.h"
#endif

#include "MFCSingleToolBarDoc.h"
#include "MFCSingleToolBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSingleToolBarView

IMPLEMENT_DYNCREATE(CMFCSingleToolBarView, CListView)

BEGIN_MESSAGE_MAP(CMFCSingleToolBarView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	//--以下是自己的
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_POINT, &CMFCSingleToolBarView::OnPoint)
	ON_COMMAND(IDM_RECTANGLE, &CMFCSingleToolBarView::OnRectangle)
	ON_COMMAND(IDM_LINE, &CMFCSingleToolBarView::OnLine)
	ON_COMMAND(IDM_ELLIPSE, &CMFCSingleToolBarView::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_SETTING, &CMFCSingleToolBarView::OnSetting)
	ON_COMMAND(IDM_CHOOSE_COLOR, &CMFCSingleToolBarView::OnChooseColor)
	ON_WM_ERASEBKGND()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCSingleToolBarView construction/destruction

CMFCSingleToolBarView::CMFCSingleToolBarView()
	: m_firstPoint(0)//可以传0
	, m_lineWith(1)
	, m_lineStyle(0)
	, m_color(RGB(255,0,0))
	
{
	// TODO: add construction code here

}

CMFCSingleToolBarView::~CMFCSingleToolBarView()
{
}

BOOL CMFCSingleToolBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CMFCSingleToolBarView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

void CMFCSingleToolBarView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCSingleToolBarView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCSingleToolBarView diagnostics

#ifdef _DEBUG
void CMFCSingleToolBarView::AssertValid() const
{
	CListView::AssertValid();
}

void CMFCSingleToolBarView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMFCSingleToolBarDoc* CMFCSingleToolBarView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSingleToolBarDoc)));
	return (CMFCSingleToolBarDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCSingleToolBarView message handlers
void CMFCSingleToolBarView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window	
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);	
}


//---------我的代码 状态栏显示鼠标位置
void CMFCSingleToolBarView::OnMouseMove(UINT nFlags, CPoint point)
{
	CString str;
	//str.Format(_T("x=%d,y=%d"),point.x,point.y);
	str.Format(L"x=%d,y=%d",point.x,point.y);

	//CMFCStatusBar statusBar= ((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar;//默认是protected 可以修改为public,后报错
	//statusBar.SetWindowTextW(str);
	
	//int index =statusBar.CommandToIndex(ID_SEPARATOR);//在ManFrm.h中有定义
	//statusBar.SetPaneText(index,str,TRUE);

	//这里不能使用((CMainFrame*)GetParent(),要使用(CMainFrame*)AfxGetMainWnd()
	//((CMainFrame*)AfxGetMainWnd())->SetMessageText(str);//OK,
	 //((CMainFrame*)AfxGetMainWnd())->GetMessageBar()->SetWindowText(str);//OK
	((CMainFrame*)AfxGetMainWnd())->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);//OK,CMMFCStatusBar,Create方法中默认ID

	CListView::OnMouseMove(nFlags, point);
}


void CMFCSingleToolBarView::OnPoint()
{
	m_drawType = T_POINT;

}


void CMFCSingleToolBarView::OnRectangle()
{
	m_drawType = T_RECTANGLE;
}


void CMFCSingleToolBarView::OnLine()
{
	 m_drawType = T_LINE;
}


void CMFCSingleToolBarView::OnEllipse()
{
 	m_drawType = T_ELLIPSE;
}


void CMFCSingleToolBarView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_firstPoint=point;
	//CListView::OnLButtonDown(nFlags, point);//要注释它,要不然,不会响应OnLButtonUp
}


void CMFCSingleToolBarView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	//PS_SOLID -- 0 还要对应界面的tab order
	//PS_DASH             1
	//PS_DOT              2
	CPen pen(m_lineStyle,m_lineWith,m_color);
	dc.SelectObject(&pen);

	CBrush * brush =CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(brush);
	//不知道修改了什么???,第一次菜单是但灰的,最开始是好的




	switch (m_drawType)
	{
	case T_POINT:
		dc.SetPixel(m_firstPoint.x,m_firstPoint.y,RGB(255,0,0));
		break;
	case T_LINE:
		dc.MoveTo(m_firstPoint);
		dc.LineTo(point);
		break;
	case T_ELLIPSE:
		dc.Ellipse(CRect(m_firstPoint,point));
		break;
	case T_RECTANGLE:
		dc.Rectangle(CRect(m_firstPoint,point));
		break;
	default:
		MessageBox(L"请在菜单中选择要画的图形");
	}


	CListView::OnLButtonUp(nFlags, point);
}


void CMFCSingleToolBarView::OnSetting()
{
	DrawSettingDlg dlg;
	dlg.m_nLineWidth=m_lineWith; //保存上次设置的值
	dlg.m_lineStyle=m_lineStyle;
	if(IDOK==dlg.DoModal())
	{
		m_lineWith=dlg.m_nLineWidth;
		m_lineStyle=dlg.m_lineStyle;
		
		Invalidate();//重画, 这里不会调用OnDraw,是因为Frame中有以WM_PAINT消息做处理
		/* 
		//这里测试时不把VS和弹出对框,挡在窗口前面
		CClientDC dc(this);
		dc.SelectObject(&m_font);
	
		LOGFONT t_font;
		m_font.GetLogFont(&t_font);
		CString strFont=t_font.lfFaceName;

		dc.TextOut(200,200,strFont);
		 */
	}
}


void CMFCSingleToolBarView::OnChooseColor()
{
	CMFCColorDialog dlg;//颜色选择话框
	dlg.SetCurrentColor(m_color);//修改颜色
	if(IDOK==dlg.DoModal())
	{
		m_color=dlg.GetColor();//得到颜色
	}
}


void CMFCSingleToolBarView::OnDraw(CDC* pDC)//自己加的,没用的被Frame给拦截了
{
	pDC->SelectObject(&m_font);
	
	LOGFONT t_font;
	m_font.GetLogFont(&t_font);
	CString strFont=t_font.lfFaceName;

	pDC->TextOutW(20,20,strFont);
}

 

//----------背景擦除消息,用于显示图片 
BOOL CMFCSingleToolBarView::OnEraseBkgnd(CDC* pDC)
{
	 CBitmap map;
  BOOL isOK=map.LoadBitmap(IDB_BITMAP1); // jpg格式会失败

  CDC dcCompatible;
  dcCompatible.CreateCompatibleDC(pDC);
  dcCompatible.SelectObject(&map);

  CRect rect;
  GetClientRect(&rect);
  pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);//1:1

  BITMAP map_data;
  map.GetBitmap(&map_data);
  pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,map_data.bmWidth,map_data.bmHeight,SRCCOPY);//缩放大小

	return TRUE;


  //return CListView::OnEraseBkgnd(pDC);
}
