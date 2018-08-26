
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MFCSingleScroll.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND(ID_FILE_WRITE, &CMainFrame::OnFileWrite)
	ON_COMMAND(ID_FILE_READ, &CMainFrame::OnFileRead)
	ON_COMMAND(MY_REG_WRITE, &CMainFrame::OnRegWrite)
	ON_COMMAND(MY_REG_READ, &CMainFrame::OnRegRead)
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
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


 


void CMainFrame::OnFileWrite()
{
	
	//---------Win32 API

	/* */
	HANDLE handle=CreateFile(L"中文名.txt",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	//--char 英文  OK
	//char* data ="english"; 
	//int charLen=strlen(data) +1 ;

	//--char* 中文 ,写OK
	//char* data ="english中文"; 
	//int charLen=strlen(data) +1 ;

	 
	//----wchar_t *中文 ,写当二进制文件做法,读是OK的,
	//用notepad++ 打开显示OK,但用"记事本"打开显示不对???
	//原因是notepad是以GBK编码打开的,但实际上是UTF8编码(wchar_t),不知道文件头中应该如何写编码让"记事本"可以认它?????
	
	//wchar_t* data =L"english中文";//共9个
	//int charLen=wcslen(data)*2;//是包括结尾符的

	//----强转 和上面是一样作用的 
	wchar_t* wData =L"english中文";//共9个
	char* data=(char*)wData;
	int charLen=wcslen(wData)*2 ;//是包括结尾符的

	DWORD actulLen;
	WriteFile(handle,data,charLen,&actulLen,NULL);
	
	CloseHandle(handle);
	


	//---------MFC
	/*
	CFile file(L"中文名.txt",CFile::modeCreate|CFile::modeWrite);//|CFile::modeNoTruncate|CFile::typeBinary 
	char * data="中华人民共和国";
	file.Write(data,strlen(data));
	file.Close();
	*/
	/*
	CFileDialog fileDlg(FALSE);
	fileDlg.m_ofn.lpstrTitle=L"我的保存对话框";
	//fileDlg.m_ofn.lpstrFilter=L"Text File(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";//加\0分隔,多个显示和过虑功能,以\0\0结尾
	fileDlg.m_ofn.lpstrFilter=L"All Files(*.*)\0*.*\0Text File(*.txt)\0*.txt\0\0";
	fileDlg.m_ofn.lpstrDefExt=L"txt";//对保存时的默认扩展名
	//fileDlg.GetFileName();
	if(IDOK==fileDlg.DoModal())
	{
		CFile file(fileDlg.GetFileName(),CFile::modeCreate|CFile::modeWrite);
		char * data="中华人民共和国";
		file.Write(data,strlen(data));
		file.Close();
	}*/


	//-------CArchive
	/*
	CFile file(L"serialize.bin",CFile::modeWrite|CFile::modeCreate);
	CArchive archive(&file,CArchive::store);
	int id=1001;
	CString name=L"李四";
	archive<<id<<name;//要用变量才知道是什么类型
	*/


}


void CMainFrame::OnFileRead()
{
	//---------Win32 API 
	/*  */
	 
	HANDLE handle=CreateFile(L"中文名.txt",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD actualLen;

	//--英文 OK
	//char data[100];
	//ReadFile(handle,&data,100,&actualLen,NULL);
	//data[actualLen]='\0'; 
	//MessageBox(CString(data));//只有英文可以 把char*到CString

	//--char *中文
	/*char data[100];
	ReadFile(handle,&data,100,&actualLen,NULL);//Debug时是得到的是正常中文
	data[actualLen]='\0';
	//MessageBox(CString(data)); //有中文是不行的,不知道如何char*中文->wchar_t* 中文 转换?????
	
	
	wchar_t wData[50];
	wmemset(wData,0,50);

	mbstate_t state;
	memset(&state,0,sizeof(state));
	
	//const char* con_char=data;
	const char* con_char="char*中文";

	//mbsrtowcs(wData,&con_char,50,&state);//char*是正常中文 ->转换到wchar_t* ,失败???
	//mbstowcs(wData,con_char,50);//,失败???

	wData[actualLen/2]='\0';
	MessageBox(CString(wData));
	 */

	

	//----wchar_t *中文 ,写当二进制文件做法,读是OK的,
	//用notepad++ 打开显示OK,但用"记事本"打开显示不对???
	//原因是notepad是以GBK编码打开的,但实际上是UTF8编码(wchar_t),不知道文件头中应该如何写编码让"记事本"可以认它?????
	
	wchar_t data[100];
	ReadFile(handle,&data,100,&actualLen,NULL);
	data[actualLen/2]='\0';
	MessageBox(CString(data)); 
  
	CloseHandle(handle);

	
	//---------MFC
	/*
	CFile file(L"中文名.txt",CFile::modeNoTruncate|CFile::modeRead);//|CFile::typeBinary 
	int len=file.GetLength();//得到文件长度
	char *data=new char[len+1];
	int readed=file.Read(data,len);
	data[readed+1]='\0';//可以有中文
	file.Close();
	MessageBox(CString(data));//不能有中文
	*/

	/*
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle=L"我的打开对话框";
	//fileDlg.m_ofn.lpstrFilter=L"Text File(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";//加\0分隔,多个显示和过虑功能,以\0\0结尾
	fileDlg.m_ofn.lpstrFilter=L"All Files(*.*)\0*.*\0Text File(*.txt)\0*.txt\0\0";
	if(IDOK==fileDlg.DoModal())
	{
		CFile file(fileDlg.GetFileName(),CFile::modeNoTruncate|CFile::modeRead);//|CFile::typeBinary 
		int len=file.GetLength();
		char *data=new char[len+1];
		int readed=file.Read(data,len);
		data[readed+1]='\0';//可以有中文
		file.Close();
		MessageBox(CString(data));//不能有中文
	}
	*/

	//-------CArchive
	 /*
	CFile file(L"serialize.bin",CFile::modeRead);
	CArchive archive(&file,CArchive::load);
	int id;
	CString name;
	archive>>id>>name;
	CString res;
	res.Format(L"id=%d,name=%s",id,name);
	MessageBox(res);
	*/

}
//---App类中也有注册表的程序

void CMainFrame::OnRegWrite()
{
	 //---Win32 API
	HKEY key;
	RegCreateKey(HKEY_LOCAL_MACHINE,L"SOFTWARE\\我的公司\\我的程序",&key);
	CString val=_T("不常用的没名字的值");
	RegSetValue(key,NULL,REG_SZ,val,val.GetLength());

	DWORD age=30;
	RegSetValueEx(key,L"年龄",NULL,REG_DWORD,(const BYTE*)&age,sizeof(DWORD));
	RegCloseKey(key);
}


void CMainFrame::OnRegRead()
{
	 //---Win32 API
	/*
	HKEY key;
	RegCreateKey(HKEY_LOCAL_MACHINE,L"SOFTWARE\\我的公司\\我的程序",&key);
	
	long len;
	RegQueryValue(key,NULL,NULL,&len);//为了得到长度
	wchar_t *val=new wchar_t[len];
	RegQueryValue(key,NULL,val,&len);//要传&len
	MessageBox(val);
	RegCloseKey(key);
	*/
	
	HKEY key;
	RegOpenKey(HKEY_LOCAL_MACHINE,L"SOFTWARE\\我的公司\\我的程序",&key);//和RegCreateKey类似
	DWORD len,type,val;
	RegQueryValueEx(key,L"年龄",NULL,&type,(LPBYTE)&val,&len);//可以得到类型
	CString str;
	str.Format(L"age=%d,type=%d,len=%d",val,type,len);
	MessageBox(str);
	RegCloseKey(key);
}
