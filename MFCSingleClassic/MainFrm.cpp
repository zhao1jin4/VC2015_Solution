
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "MFCSingleClassicDoc.h"//----我加的为View使用
#include "MFCSingleClassicView.h"//----我新加的,中有引用Doc,
#include "MainFrm.h"
#include "MyDialog.h"
#include <stdio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	
	//---我的代码
	ON_COMMAND(ID_SHOW, &CMainFrame::OnShow)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CMainFrame::OnUpdateEditCut)
	ON_COMMAND(IDM_MY_DYN_MENUITEM, &CMainFrame::OnMyDynMenuItem )//动态菜单的响应函数

	ON_COMMAND(ID_SHOWDIAG, &CMainFrame::OnShowMyDiag)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	//--------------我的代码
	m_bAutoMenuEnable=FALSE;//为菜单禁用
}

CMainFrame::~CMainFrame()
{
}

HICON m_animIcons[3];
void CALLBACK  AnimIconProc(HWND hWnd,UINT nMsg,UINT_PTR nIDEvent,DWORD dwTime)
{
	static int index=0;

	SetClassLong(hWnd,GCL_HICON,(LONG)m_animIcons[index++%3]);
}
extern CMFCSingleClassicApp theApp;
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//---------------------------以下是我的代码
	/*
	//CButton不能放在方法内部,当方法结束时,就销毁了,就显示不出
	m_button.Create(_T("test title"),BS_DEFPUSHBUTTON|WS_CHILD,CRect(0,0,100,100),this,100);//0,0显示在菜单下方,如有工具栏,则显示在上方
	m_button.ShowWindow(SW_SHOW);
	 */
	 
	//----菜单
/*
	CMenu* one=GetMenu();
	if(one==NULL)
		AfxMessageBox(_T("Menu is NULL"));
*/
//VS2010 在CMainFrame的OnCreate方法中返回的是NULL,
//原因是建立项目时在User Interface Features的界面中单选默认是Use a Menu bar and toolbar,侧在OnCreate方法中没有建立菜单
//应该选择 Use a classic menu
	
	//GetMenu()返回的是菜单栏,GetSubMenu(0)是文件菜单,再根据ID或位置来找
	//GetMenu()->GetSubMenu(0)->CheckMenuItem(0,MF_BYPOSITION|MF_CHECKED);//复选新建菜单
	GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_FILE_NEW,MF_BYCOMMAND|MF_CHECKED);//复选新建菜单


	GetMenu()->GetSubMenu(0)->SetDefaultItem(2,TRUE);//如TRUE,第一个表示是位置,如FALSE第一个表示ID
	GetMenu()->GetSubMenu(0)->SetDefaultItem(3,TRUE);//变粗体显示,按位置时注意分隔线也占一个位置

	
	mapRight.LoadBitmap(IDB_BITMAP_SEL);
	mapWrong.LoadBitmap(IDB_BITMAP_UNSEL);

	CString str;
	str.Format(_T("x=%d,y=%d"),GetSystemMetrics(SM_CXMENUCHECK),GetSystemMetrics(SM_CYMENUCHECK));
	//MessageBox(str);

	//GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(ID_FILE_OPEN,MF_BYCOMMAND,&mapRight,&mapWrong);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(1,MF_BYPOSITION,&mapRight,&mapWrong);
	//分隔线也是占一个index

	GetMenu()->GetSubMenu(0)->EnableMenuItem(2,MF_BYPOSITION|MF_DISABLED|MF_GRAYED);  //MF_DISABLED|MF_GRAYED要一起使用
	//CMainFrame构造函数中加 m_bAutoMenuEnable=FALSE;

	/*
	SetMenu(NULL);//删除当前菜单栏
	CMenu menu;//应该定义成类的成员
	menu.LoadMenu(IDR_MAINFRAME);//可动态换菜单
	SetMenu(&menu);

	menu.Detach();//如menu是局部变量 ,要使用Detach,HMENU和CWnd断开
	*/

	
	/* 	*/

	//动态菜单
	CMenu dynMenu;//如是局部变量,记得要Detach();
	dynMenu.CreatePopupMenu();//创建空的
	dynMenu.AppendMenu(MF_STRING,IDM_MY_DYN_MENUITEM,_T("动态菜单项1_有处理的"));//IDM_MY_DYN_MENUITEM 定义在Resource.h中
	dynMenu.AppendMenu(MF_STRING,1112,_T("动态菜单项2"));

	CMenu * bar=GetMenu();
	bar->AppendMenu(MF_POPUP ,(UINT_PTR) dynMenu.m_hMenu , _T("append动态菜单"));
	bar->InsertMenu(2,MF_POPUP|MF_BYPOSITION ,(UINT_PTR) dynMenu.m_hMenu , _T("insert动态菜单"));
	bar->GetSubMenu(0)->InsertMenu(ID_FILE_OPEN,MF_POPUP|MF_BYCOMMAND ,1113,_T("动态菜单项3"));//在指定位置前
	//bar->GetSubMenu(0)->DeleteMenu(1113,MF_BYCOMMAND);//
	bar->GetSubMenu(0)->DeleteMenu(ID_FILE_PRINT_PREVIEW,MF_BYCOMMAND);
	dynMenu.Detach();

	//-------------修改外观
	//SetWindowLong(m_hWnd,GWL_STYLE,WS_OVERLAPPEDWINDOW);//可以创建后修改外观
	SetWindowLong(m_hWnd,GWL_STYLE,GetWindowLong(m_hWnd,GWL_STYLE )& ~WS_MAXIMIZEBOX);//去最大化按钮

	::SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(NULL,IDI_ERROR));//在窗口创建之后修改

	m_animIcons[0]=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	m_animIcons[1]=LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDI_ICON2));//方式二,theApp要extern
	m_animIcons[2]=LoadIcon(::AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON3));//方式三,AfxGetApp()

	this->SetTimer(223,1000,AnimIconProc);//函数不能是类的函数

	return 0;
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	//----------------我的代码,修改外观
	cs.cy=200;
	cs.cx=500;

	cs.lpszName=_T("我的标题");//单文档,这里管理文件的标题,不是应用程序的标题
	//cs.style=~FWS_ADDTOTITE;
	cs.style&=~FWS_ADDTOTITLE;//去除FWS_ADDTOTITLE,lpszName就有效了,表示把文档的标题做为Frame的标题
	/*
	WNDCLASS wndcls;
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	wndcls.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);//应该在View中修改
	wndcls.hCursor=LoadCursor(NULL,IDC_HELP);//应该在View中修改
	wndcls.hIcon=LoadIcon(NULL,IDI_ERROR);
	wndcls.hInstance=AfxGetInstanceHandle();//得到当前应用程序的句柄
	wndcls.lpfnWndProc=::DefWindowProc;//使用全局的
	wndcls.lpszClassName=_T("my");
	wndcls.lpszMenuName=NULL;
	wndcls.style=CS_HREDRAW|CS_VREDRAW;
	::RegisterClass(&wndcls);
	cs.lpszClass=_T("my");//View类中PreCreateWindow也有相同的代码
	*/

	//cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,0,LoadIcon(NULL,IDI_WARNING));


	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG
 
//----------我的代码
void CMainFrame::OnShow()//是右键菜单的处理函数
{
	// TODO: Add your command handler code here
	MessageBox(_T("MainFrame Popup"));
}

//----------我的代码
void CMainFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	//AfxMessageBox(_T(" menu cut is clicked !"));//在点edit弹出之前调用 

	/*
	if(ID_EDIT_CUT==pCmdUI->m_nID)//m_nID成员
		pCmdUI->Enable(FALSE);//禁用Cut菜单,适用于弹出菜单,不可用于永久显示的菜单栏中的,如有工具栏按钮同样功能也生效,只要取相同的ID,
	*/
	if(2==pCmdUI->m_nIndex)//m_nIndex  成员,菜单和工具栏索引可能不同,最好用ID
		pCmdUI->Enable(FALSE);
}
//----------我的代码
 void CMainFrame::OnMyDynMenuItem()//动态菜单的响应函数
 {
	AfxMessageBox(_T("我的动态菜单的响应处理"));
 }

 /*
 //函数是virtual,只要实现,就不会把消息向下传递给View
 BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)//
 {
	 //对动态增加的菜单项放在集合中
	 int menuItemId=LOWORD(wParam);//低字是 Menu Item Commnad ID
	 //if(menuItemId>xx && menuItemId< a.Size()){  }
	  
	 CMFCSingleClassicView *view=( CMFCSingleClassicView * )GetActiveView(); //可以在MainFrame中得到View的引用,就可以仿问成员

	 return CFrameWnd::OnCommand(wParam, lParam);
 }
 */

 //---------我的代码,显示对话框
void CMainFrame::OnShowMyDiag()
{
	MyDialog dialog;//模态可是局部变量
	dialog.DoModal();

	/*
	MyDialog* mydiaog=new MyDialog();//要析构时销毁
	mydiaog->Create(IDD_DIALOG1,this);//非模态不能是局部变量,可定义为指针
	mydiaog->ShowWindow(SW_SHOW);//点OK时只是隐藏,要重写OnOK
	*/
}
