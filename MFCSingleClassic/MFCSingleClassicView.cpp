
// MFCSingleClassicView.cpp : implementation of the CMFCSingleClassicView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSingleClassic.h"
#endif

#include "MFCSingleClassicDoc.h"
#include "MFCSingleClassicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSingleClassicView

IMPLEMENT_DYNCREATE(CMFCSingleClassicView, CView)

BEGIN_MESSAGE_MAP(CMFCSingleClassicView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	
	//---------�ҵĴ���
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_COMMAND(IDM_TEST, &CMFCSingleClassicView::OnTest)//���ɵĲ˵�test
	ON_WM_RBUTTONDOWN()
	//ON_COMMAND(ID_SHOW, &CMFCSingleClassicView::OnShow)//�Ҽ��˵���Ĵ���
 
	
	ON_COMMAND(ID_NAVIGATION, &CMFCSingleClassicView::OnNavigation)
END_MESSAGE_MAP()

// CMFCSingleClassicView construction/destruction

CMFCSingleClassicView::CMFCSingleClassicView(): m_bDraw(false),m_strLine("")
	, m_nWidth(0)
{
	// TODO: add construction code here

}

CMFCSingleClassicView::~CMFCSingleClassicView()
{
}

BOOL CMFCSingleClassicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	//---�ҵĴ���,�Զ������
	//cs.lpszClass=_T("my");
	//cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,LoadCursor(NULL,IDC_HELP),(HBRUSH)GetStockObject(GRAY_BRUSH),0);


	return CView::PreCreateWindow(cs);
}

// CMFCSingleClassicView drawing

void CMFCSingleClassicView::OnDraw(CDC* pDC)
{
	CMFCSingleClassicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here


	//--------- �ҵĴ���
	//WM_PAINT��Ϣ����Ӧ����,���ڴ�С�ı�ʱ
	
	//CString str2("�ҵĴ����е��ı�����);
	CString str2=_T("�ҵĴ����е��ı�����");//������=
	pDC->TextOut(0,100,str2);

	CString str;
	str.LoadString(IDS_MY_STR);
	pDC->TextOut(50,50,str);

	CSize size=pDC->GetTextExtent(str);
	
	pDC->BeginPath();
	pDC->Rectangle(50,50,50+size.cx,50+size.cy);//��ɫ���
	pDC->EndPath();
	pDC->SelectClipPath(RGN_DIFF);//��ʾ�Ժ󻭵Ĳ���Ӱ��Path�е�ͼ��
	//pDC->SelectClipPath(RGN_AND);//��ʾ�Ժ󻭵�ֻ��Ӱ��Path�е�ͼ��
	for(int i=0;i<200;i+=10)
	{
		pDC->MoveTo(0,i);
		pDC->LineTo(300,i);
	
		pDC->MoveTo(i,0);
		pDC->LineTo(i,300);
	}


}


// CMFCSingleClassicView printing

BOOL CMFCSingleClassicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCSingleClassicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCSingleClassicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCSingleClassicView diagnostics

#ifdef _DEBUG
void CMFCSingleClassicView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCSingleClassicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCSingleClassicDoc* CMFCSingleClassicView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSingleClassicDoc)));
	return (CMFCSingleClassicDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCSingleClassicView message handlers


int CMFCSingleClassicView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	//--------- �ҵĴ���
	//m_button.Create(_T("test title"),BS_DEFPUSHBUTTON|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),GetParent(),100);//this,GetParent()��ָ��CMainFrame
		//m_button.ShowWindow(SW_SHOW);//���� WS_VISIBLE �Ͳ��õ������������
	//m_button.Create(_T("test title"),BS_RADIOBUTTON|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),GetParent(),100);//this,GetParent()
	m_button.Create(_T("test title"),BS_CHECKBOX|WS_CHILD|WS_VISIBLE,CRect(0,50,100,100),this,100);//this,GetParent()
	//m_button.Create(_T("test title"),BS_AUTO3STATE|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),GetParent(),100);//this,GetParent()

	/*
	//�����
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);//�õ�������Ϣ
	CreateSolidCaret(tm.tmAveCharWidth/3,tm.tmHeight);
	ShowCaret();
	*/
	
	//ͼ�β����
	caretmap.LoadBitmap(IDB_BITMAP1);
	CreateCaret(&caretmap);
	ShowCaret();

	SetTimer(1,1000,NULL);

	//------------�޸����

	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)LoadCursor(NULL,IDC_HELP));
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,(LONG)GetStockObject(GRAY_BRUSH));

	return 0;
}

//--------- �ҵĴ���
void CMFCSingleClassicView::OnLButtonDown(UINT nFlags, CPoint point)
{

	// TODO: Add your message handler code here and/or call default
	m_bDraw=true;
	m_startPoint=point;

	SetCaretPos(point);//�ƶ����
	m_strLine.Empty();//

//	MessageBox(_T("My View"));//View�Ḳ��CMainFrame


	CView::OnLButtonDown(nFlags, point);
}

//--------- �ҵĴ���
void CMFCSingleClassicView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDraw=false;
	// TODO: Add your message handler code here and/or call default
	
	/*  
	HDC m_hdc;
	m_hdc=::GetDC(m_hWnd);//m_hWnd,this���еģ�this��ָ��
	::MoveToEx(m_hdc,m_startPoint.x,m_startPoint.y,NULL);
	::LineTo(m_hdc,point.x,point.y);
	::ReleaseDC(m_hWnd,m_hdc);
	 */

	/*
	//ʹ��CDC
	CDC *h_cdc=GetDC();
	h_cdc->MoveTo(m_startPoint);
	h_cdc->LineTo(point);
	ReleaseDC(h_cdc);
	*/
	
	/*  
	//ʹ��CClientDC
	CClientDC dc(GetParent());//this����View�ڡ�Frame�ϣ�Ҳ�ɻ�View��
	dc.MoveTo(m_startPoint);
	dc.LineTo(point);
	*/

	/*
	CWindowDC dc(GetParent());//ʹ��CWindowDC  ��CClientDЧ��һ����
	//CWindowDC dc(GetDesktopWindow());//ʹ��GetDesktopWindow
	dc.MoveTo(m_startPoint);
	dc.LineTo(point);
	*/

	/*
	//CPen pen(PS_SOLID,2,RGB(0,255,0));
	//CPen pen(PS_DASH,1,RGB(0,255,0));//<=1
	CPen pen(PS_DOT,1,RGB(0,255,0));//<=1
	CClientDC dc(this);
	
	CPen* oldPen;
	oldPen=dc.SelectObject(&pen);
	
	dc.MoveTo(m_startPoint);
	dc.LineTo(point);
	dc.SelectObject(oldPen);
	*/

	/*
	CClientDC dc(this);
	//CBrush brush(RGB(255,0,0));
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP2);
	CBrush brush(&bitmap) ;

	dc.FillRect(CRect(m_startPoint,point),&brush);
	*/

	/*
	CClientDC dc(this);
	CBrush* transparent=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//͸����
	CBrush* oldBrush=dc.SelectObject(transparent);
	dc.Rectangle(CRect(m_startPoint,point));
	dc.SelectObject(oldBrush);
	*/



	CView::OnLButtonUp(nFlags, point);
}

//--------- �ҵĴ���
void CMFCSingleClassicView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_bDraw)
	{

		CClientDC dc(this);
		//dc.SetROP2(R2_MERGENOTPEN);
		dc.SetROP2(R2_BLACK);
		
		dc.MoveTo(m_startPoint);
		dc.LineTo(point);
		m_startPoint=point;

	}
	CView::OnMouseMove(nFlags, point);
}

//--------- �ҵĴ���
void CMFCSingleClassicView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	CFont font;
	font.CreatePointFont(200, _T("����"));
	CFont* oldFont=dc.SelectObject(&font);//��������



	if('\r'==nChar)// enter
	{
		m_strLine.Empty();
		m_startPoint.y+=tm.tmHeight;
	}else if ('\b'==nChar)// 0x08 backspace
	{
		COLORREF oldColor=dc.SetTextColor(dc.GetBkColor());
		dc.TextOut(m_startPoint.x,m_startPoint.y,m_strLine);
		
		m_strLine = m_strLine.Left(m_strLine.GetLength()-1);
		dc.SetTextColor(oldColor);
	}else
	{
		//m_strLine += nChar;//����
		m_strLine += (WCHAR)nChar;//���� 
	}
	CPoint pt;
	CSize sz=dc.GetTextExtent(m_strLine);
	pt.x=m_startPoint.x+ sz.cx;
	pt.y=m_startPoint.y;

	SetCaretPos(pt);
	dc.TextOut(m_startPoint.x,m_startPoint.y,m_strLine);

	dc.SelectObject(oldFont);



	CView::OnChar(nChar, nRepCnt, nFlags);
}

//--------- �ҵĴ���
void CMFCSingleClassicView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	m_nWidth+=5;
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	CRect rect;
	rect.left=0;
	rect.top=100;
	rect.right=m_nWidth;
	rect.bottom=rect.top+tm.tmHeight;
	
	dc.SetTextColor(RGB(0,255,0));
	CString str2=_T("�ҵĴ����е��ı�����");//������=
	dc.DrawText(str2,&rect,DT_LEFT);

	rect.top=150;
	rect.bottom=rect.top+tm.tmHeight;
	dc.DrawText(str2,&rect,DT_RIGHT);

	CSize sz=dc.GetTextExtent(str2);
	if(m_nWidth>sz.cx)
	{
			m_nWidth=0;
	}
	 

	CView::OnTimer(nIDEvent);
}


//--------- �ҵĴ���
void CMFCSingleClassicView::OnTest()
{
		AfxMessageBox(_T("View Test is Clicked"));
}


/*
void CMFCSingleClassicView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
}
*/
//--------- �ҵĴ���
void CMFCSingleClassicView::OnRButtonDown(UINT nFlags, CPoint point)
{
	 
	//�Ҽ��˵�
	CMenu menu;
	menu.LoadMenu(IDR_MENU_RIGHT);
	CMenu * popupMenu=menu.GetSubMenu(0);

	ClientToScreen(&point);
	//popupMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	popupMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,GetParent());
	//�Ӵ������յ�,��û����Ӧ�Ž���������(��ȻҪown ָ�򸸴���)
	
	

	CView::OnRButtonDown(nFlags, point);
}


//void CMFCSingleClassicView::OnShow()
//{
//	MessageBox(_T("View Popup"));
//}

//---�ҵĴ���,�˵��� "��" �Ĵ���
void CMFCSingleClassicView::OnNavigation()
{
	// TODO: Add your command handler code here
	NavigationSheet sheet(_T("��"),NULL,0);
	sheet.SetWizardMode();//��DoModal֮ǰ����,�ɱ�ǩҳ(Tab) -> ��
	if(ID_WIZFINISH ==sheet.DoModal())//����ʱ,�ǰ���ɰ�ťʱ
	{
		int occupation=sheet.m_page1.m_occupation;
		CString workLocation=sheet.m_page1.m_workLocation;
		//CComboBox * combox=(CComboBox * )sheet.m_page3.GetDlgItem(IDC_COMBO1);//����������,�Ѿ�����
	  	
		CString result=_T("view��,�����,��ѡ���:");
		wchar_t * num=new wchar_t[10];
		swprintf(num,L"%ld",occupation);
		result += CString(num);
		result+=_T(",")+workLocation;
		 
		MessageBox(result);
	}
	
}
