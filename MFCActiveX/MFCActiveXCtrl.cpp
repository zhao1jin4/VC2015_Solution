// MFCActiveXCtrl.cpp : Implementation of the CMFCActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "MFCActiveX.h"
#include "MFCActiveXCtrl.h"
#include "MFCActiveXPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMFCActiveXCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CMFCActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CMFCActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CMFCActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	//-----生成代码声明
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_BACKCOLOR()
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXCtrl, "myinterval", dispidmyinterval, m_myinterval, OnmyintervalChanged, VT_I2)//在VB中测试看不到myinterval属性?????,VC中可以看到,修改报错??/
	DISP_FUNCTION_ID(CMFCActiveXCtrl, "Hello", dispidHello, Hello, VT_EMPTY, VTS_NONE)//VB中也看不到????
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CMFCActiveXCtrl, COleControl)
	//------我的代码
	EVENT_STOCK_CLICK()//是右击XXXCtrl类->add->add Event,只在ActiveX Control Test Container中测试可以,VB中报错
	EVENT_CUSTOM_ID("NewMinute", eventidNewMinute, NewMinute, VTS_NONE)//只在ActiveX Control Test Container中测试可以,VB中报错
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
//是对右击控件->properites显示的对话框中的tab,要用ActiveX Control Test Container测试生效
BEGIN_PROPPAGEIDS(CMFCActiveXCtrl, 2)//这里个数,要修改
	PROPPAGEID(CMFCActiveXPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)//------我的代码,颜色属性的GUID
END_PROPPAGEIDS(CMFCActiveXCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMFCActiveXCtrl, "MFCACTIVEX.MFCActiveXCtrl.1",
	0x603943f6, 0x2da0, 0x4936, 0xbd, 0x18, 0xda, 0xe8, 0xb9, 0xba, 0xcb, 0xf5)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CMFCActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DMFCActiveX = { 0x21D17C7A, 0x5F34, 0x4930, { 0xAD, 0xBC, 0x8C, 0xBC, 0xD7, 0xF2, 0xDC, 0xB3 } };
const IID IID_DMFCActiveXEvents = { 0xDA6F834D, 0xB2A7, 0x44C4, { 0x80, 0x48, 0xF, 0xB3, 0x6, 0x21, 0x5D, 0x71 } };


// Control type information

static const DWORD _dwMFCActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMFCActiveXCtrl, IDS_MFCACTIVEX, _dwMFCActiveXOleMisc)



// CMFCActiveXCtrl::CMFCActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMFCActiveXCtrl

BOOL CMFCActiveXCtrl::CMFCActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MFCACTIVEX,
			IDB_MFCACTIVEX,
			afxRegApartmentThreading,
			_dwMFCActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CMFCActiveXCtrl::CMFCActiveXCtrl - Constructor

CMFCActiveXCtrl::CMFCActiveXCtrl()
{
	InitializeIIDs(&IID_DMFCActiveX, &IID_DMFCActiveXEvents);
	// TODO: Initialize your control's instance data here.
	m_myinterval=500;
	//m_Interval=500;//初始化
}



// CMFCActiveXCtrl::~CMFCActiveXCtrl - Destructor

CMFCActiveXCtrl::~CMFCActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CMFCActiveXCtrl::OnDraw - Drawing function

void CMFCActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.

	//注释它
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

	//ActiveX Control Test Container工具在 C:\Program Files\Microsoft Visual Studio 10.0\Samples\1033\VC2010Samples.zip\C++\MFC\ole\TstCon 是一个Solution项目
	//-----------我的代码
	CTime time=CTime::GetCurrentTime();//VS工具不提示有这个方法,但是有的
	if(0 == time.GetSecond()%10)
		NewMinute();//向容器发送事件发生通知
	CString timeStr=time.Format("%H:%M:%S");

	//加BackColor的Stock属性,展开XXXLib->图标"o-O"(不是Events结尾的),右击->add->add property
	//要在VB中测试,才可以看到属性并修改
	CBrush brush(TranslateColor(GetBackColor()));//GetBackColor得到用户设置的背景色属性,
	pdc->FillRect(rcBounds, &brush);
	pdc->SetTextColor(TranslateColor(GetForeColor()));
	pdc->SetBkMode(TRANSPARENT);
	pdc->TextOutW(0,0,timeStr);

}



// CMFCActiveXCtrl::DoPropExchange - Persistence support

void CMFCActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	
	PX_Short(pPX,L"myinterval",m_myinterval,800);//--持久化属性值,VB中看不到myinterval????

	// TODO: Call PX_ functions for each persistent custom property.
}



// CMFCActiveXCtrl::OnResetState - Reset control to default state

void CMFCActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CMFCActiveXCtrl::AboutBox - Display an "About" box to the user

void CMFCActiveXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_MFCACTIVEX);
	dlgAbout.DoModal();
}



// CMFCActiveXCtrl message handlers

//-----------我的代码
int CMFCActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//SetTimer(1,1000,NULL);//使用WM_TIMER消息处理
	//SetTimer(1,m_Interval,NULL);
	SetTimer(1,m_myinterval,NULL);

	return 0;
}

//-----------我的代码
void CMFCActiveXCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	//Invalidate();//
	if(AmbientUserMode())//如在运行时更新,设计的时候更新,ActiveX Control Test Container中,Option->Design Mode
		InvalidateControl();//与Invalidate()功能相同
	
	COleControl::OnTimer(nIDEvent);
}
  
void CMFCActiveXCtrl::Hello(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	AfxMessageBox(L"Hello");//只在ActiveX Control Test Container中测试才可看到方法名
	// TODO: Add your dispatch handler code here
}
 
void CMFCActiveXCtrl::OnmyintervalChanged(void)//外部修改属性时调用,如myinterval
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//-----------我的代码
	//wchar_t data[50];
	//swprintf(data,L"m_myinterval=%d",m_myinterval);
	//AfxMessageBox(data);
	if(m_myinterval<0 || m_myinterval>6000)
		m_myinterval = 6000;
	else
		m_myinterval = m_myinterval/1000*1000;//取整
	KillTimer(1);//标识
	SetTimer(1,m_myinterval,NULL);
	
	BoundPropertyChanged(3);//3是"o-O"图标类的 mynterval属性前的ID值,通知容器更新值
	//-----------我的代码

	SetModifiedFlag();
}
