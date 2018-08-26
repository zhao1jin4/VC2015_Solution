
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "MFCSingleClassicDoc.h"//----�Ҽӵ�ΪViewʹ��
#include "MFCSingleClassicView.h"//----���¼ӵ�,��������Doc,
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
	
	//---�ҵĴ���
	ON_COMMAND(ID_SHOW, &CMainFrame::OnShow)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CMainFrame::OnUpdateEditCut)
	ON_COMMAND(IDM_MY_DYN_MENUITEM, &CMainFrame::OnMyDynMenuItem )//��̬�˵�����Ӧ����

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
	//--------------�ҵĴ���
	m_bAutoMenuEnable=FALSE;//Ϊ�˵�����
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

	//---------------------------�������ҵĴ���
	/*
	//CButton���ܷ��ڷ����ڲ�,����������ʱ,��������,����ʾ����
	m_button.Create(_T("test title"),BS_DEFPUSHBUTTON|WS_CHILD,CRect(0,0,100,100),this,100);//0,0��ʾ�ڲ˵��·�,���й�����,����ʾ���Ϸ�
	m_button.ShowWindow(SW_SHOW);
	 */
	 
	//----�˵�
/*
	CMenu* one=GetMenu();
	if(one==NULL)
		AfxMessageBox(_T("Menu is NULL"));
*/
//VS2010 ��CMainFrame��OnCreate�����з��ص���NULL,
//ԭ���ǽ�����Ŀʱ��User Interface Features�Ľ����е�ѡĬ����Use a Menu bar and toolbar,����OnCreate������û�н����˵�
//Ӧ��ѡ�� Use a classic menu
	
	//GetMenu()���ص��ǲ˵���,GetSubMenu(0)���ļ��˵�,�ٸ���ID��λ������
	//GetMenu()->GetSubMenu(0)->CheckMenuItem(0,MF_BYPOSITION|MF_CHECKED);//��ѡ�½��˵�
	GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_FILE_NEW,MF_BYCOMMAND|MF_CHECKED);//��ѡ�½��˵�


	GetMenu()->GetSubMenu(0)->SetDefaultItem(2,TRUE);//��TRUE,��һ����ʾ��λ��,��FALSE��һ����ʾID
	GetMenu()->GetSubMenu(0)->SetDefaultItem(3,TRUE);//�������ʾ,��λ��ʱע��ָ���Ҳռһ��λ��

	
	mapRight.LoadBitmap(IDB_BITMAP_SEL);
	mapWrong.LoadBitmap(IDB_BITMAP_UNSEL);

	CString str;
	str.Format(_T("x=%d,y=%d"),GetSystemMetrics(SM_CXMENUCHECK),GetSystemMetrics(SM_CYMENUCHECK));
	//MessageBox(str);

	//GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(ID_FILE_OPEN,MF_BYCOMMAND,&mapRight,&mapWrong);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(1,MF_BYPOSITION,&mapRight,&mapWrong);
	//�ָ���Ҳ��ռһ��index

	GetMenu()->GetSubMenu(0)->EnableMenuItem(2,MF_BYPOSITION|MF_DISABLED|MF_GRAYED);  //MF_DISABLED|MF_GRAYEDҪһ��ʹ��
	//CMainFrame���캯���м� m_bAutoMenuEnable=FALSE;

	/*
	SetMenu(NULL);//ɾ����ǰ�˵���
	CMenu menu;//Ӧ�ö������ĳ�Ա
	menu.LoadMenu(IDR_MAINFRAME);//�ɶ�̬���˵�
	SetMenu(&menu);

	menu.Detach();//��menu�Ǿֲ����� ,Ҫʹ��Detach,HMENU��CWnd�Ͽ�
	*/

	
	/* 	*/

	//��̬�˵�
	CMenu dynMenu;//���Ǿֲ�����,�ǵ�ҪDetach();
	dynMenu.CreatePopupMenu();//�����յ�
	dynMenu.AppendMenu(MF_STRING,IDM_MY_DYN_MENUITEM,_T("��̬�˵���1_�д����"));//IDM_MY_DYN_MENUITEM ������Resource.h��
	dynMenu.AppendMenu(MF_STRING,1112,_T("��̬�˵���2"));

	CMenu * bar=GetMenu();
	bar->AppendMenu(MF_POPUP ,(UINT_PTR) dynMenu.m_hMenu , _T("append��̬�˵�"));
	bar->InsertMenu(2,MF_POPUP|MF_BYPOSITION ,(UINT_PTR) dynMenu.m_hMenu , _T("insert��̬�˵�"));
	bar->GetSubMenu(0)->InsertMenu(ID_FILE_OPEN,MF_POPUP|MF_BYCOMMAND ,1113,_T("��̬�˵���3"));//��ָ��λ��ǰ
	//bar->GetSubMenu(0)->DeleteMenu(1113,MF_BYCOMMAND);//
	bar->GetSubMenu(0)->DeleteMenu(ID_FILE_PRINT_PREVIEW,MF_BYCOMMAND);
	dynMenu.Detach();

	//-------------�޸����
	//SetWindowLong(m_hWnd,GWL_STYLE,WS_OVERLAPPEDWINDOW);//���Դ������޸����
	SetWindowLong(m_hWnd,GWL_STYLE,GetWindowLong(m_hWnd,GWL_STYLE )& ~WS_MAXIMIZEBOX);//ȥ��󻯰�ť

	::SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(NULL,IDI_ERROR));//�ڴ��ڴ���֮���޸�

	m_animIcons[0]=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	m_animIcons[1]=LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDI_ICON2));//��ʽ��,theAppҪextern
	m_animIcons[2]=LoadIcon(::AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON3));//��ʽ��,AfxGetApp()

	this->SetTimer(223,1000,AnimIconProc);//������������ĺ���

	return 0;
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	//----------------�ҵĴ���,�޸����
	cs.cy=200;
	cs.cx=500;

	cs.lpszName=_T("�ҵı���");//���ĵ�,��������ļ��ı���,����Ӧ�ó���ı���
	//cs.style=~FWS_ADDTOTITE;
	cs.style&=~FWS_ADDTOTITLE;//ȥ��FWS_ADDTOTITLE,lpszName����Ч��,��ʾ���ĵ��ı�����ΪFrame�ı���
	/*
	WNDCLASS wndcls;
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	wndcls.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);//Ӧ����View���޸�
	wndcls.hCursor=LoadCursor(NULL,IDC_HELP);//Ӧ����View���޸�
	wndcls.hIcon=LoadIcon(NULL,IDI_ERROR);
	wndcls.hInstance=AfxGetInstanceHandle();//�õ���ǰӦ�ó���ľ��
	wndcls.lpfnWndProc=::DefWindowProc;//ʹ��ȫ�ֵ�
	wndcls.lpszClassName=_T("my");
	wndcls.lpszMenuName=NULL;
	wndcls.style=CS_HREDRAW|CS_VREDRAW;
	::RegisterClass(&wndcls);
	cs.lpszClass=_T("my");//View����PreCreateWindowҲ����ͬ�Ĵ���
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
 
//----------�ҵĴ���
void CMainFrame::OnShow()//���Ҽ��˵��Ĵ�����
{
	// TODO: Add your command handler code here
	MessageBox(_T("MainFrame Popup"));
}

//----------�ҵĴ���
void CMainFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	//AfxMessageBox(_T(" menu cut is clicked !"));//�ڵ�edit����֮ǰ���� 

	/*
	if(ID_EDIT_CUT==pCmdUI->m_nID)//m_nID��Ա
		pCmdUI->Enable(FALSE);//����Cut�˵�,�����ڵ����˵�,��������������ʾ�Ĳ˵����е�,���й�������ťͬ������Ҳ��Ч,ֻҪȡ��ͬ��ID,
	*/
	if(2==pCmdUI->m_nIndex)//m_nIndex  ��Ա,�˵��͹������������ܲ�ͬ,�����ID
		pCmdUI->Enable(FALSE);
}
//----------�ҵĴ���
 void CMainFrame::OnMyDynMenuItem()//��̬�˵�����Ӧ����
 {
	AfxMessageBox(_T("�ҵĶ�̬�˵�����Ӧ����"));
 }

 /*
 //������virtual,ֻҪʵ��,�Ͳ������Ϣ���´��ݸ�View
 BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)//
 {
	 //�Զ�̬���ӵĲ˵�����ڼ�����
	 int menuItemId=LOWORD(wParam);//������ Menu Item Commnad ID
	 //if(menuItemId>xx && menuItemId< a.Size()){  }
	  
	 CMFCSingleClassicView *view=( CMFCSingleClassicView * )GetActiveView(); //������MainFrame�еõ�View������,�Ϳ��Է��ʳ�Ա

	 return CFrameWnd::OnCommand(wParam, lParam);
 }
 */

 //---------�ҵĴ���,��ʾ�Ի���
void CMainFrame::OnShowMyDiag()
{
	MyDialog dialog;//ģ̬���Ǿֲ�����
	dialog.DoModal();

	/*
	MyDialog* mydiaog=new MyDialog();//Ҫ����ʱ����
	mydiaog->Create(IDD_DIALOG1,this);//��ģ̬�����Ǿֲ�����,�ɶ���Ϊָ��
	mydiaog->ShowWindow(SW_SHOW);//��OKʱֻ������,Ҫ��дOnOK
	*/
}
