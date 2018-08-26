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
	//-----���ɴ�������
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_BACKCOLOR()
	DISP_PROPERTY_NOTIFY_ID(CMFCActiveXCtrl, "myinterval", dispidmyinterval, m_myinterval, OnmyintervalChanged, VT_I2)//��VB�в��Կ�����myinterval����?????,VC�п��Կ���,�޸ı���??/
	DISP_FUNCTION_ID(CMFCActiveXCtrl, "Hello", dispidHello, Hello, VT_EMPTY, VTS_NONE)//VB��Ҳ������????
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CMFCActiveXCtrl, COleControl)
	//------�ҵĴ���
	EVENT_STOCK_CLICK()//���һ�XXXCtrl��->add->add Event,ֻ��ActiveX Control Test Container�в��Կ���,VB�б���
	EVENT_CUSTOM_ID("NewMinute", eventidNewMinute, NewMinute, VTS_NONE)//ֻ��ActiveX Control Test Container�в��Կ���,VB�б���
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
//�Ƕ��һ��ؼ�->properites��ʾ�ĶԻ����е�tab,Ҫ��ActiveX Control Test Container������Ч
BEGIN_PROPPAGEIDS(CMFCActiveXCtrl, 2)//�������,Ҫ�޸�
	PROPPAGEID(CMFCActiveXPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)//------�ҵĴ���,��ɫ���Ե�GUID
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
	//m_Interval=500;//��ʼ��
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

	//ע����
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

	//ActiveX Control Test Container������ C:\Program Files\Microsoft Visual Studio 10.0\Samples\1033\VC2010Samples.zip\C++\MFC\ole\TstCon ��һ��Solution��Ŀ
	//-----------�ҵĴ���
	CTime time=CTime::GetCurrentTime();//VS���߲���ʾ���������,�����е�
	if(0 == time.GetSecond()%10)
		NewMinute();//�����������¼�����֪ͨ
	CString timeStr=time.Format("%H:%M:%S");

	//��BackColor��Stock����,չ��XXXLib->ͼ��"o-O"(����Events��β��),�һ�->add->add property
	//Ҫ��VB�в���,�ſ��Կ������Բ��޸�
	CBrush brush(TranslateColor(GetBackColor()));//GetBackColor�õ��û����õı���ɫ����,
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

	
	PX_Short(pPX,L"myinterval",m_myinterval,800);//--�־û�����ֵ,VB�п�����myinterval????

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

//-----------�ҵĴ���
int CMFCActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//SetTimer(1,1000,NULL);//ʹ��WM_TIMER��Ϣ����
	//SetTimer(1,m_Interval,NULL);
	SetTimer(1,m_myinterval,NULL);

	return 0;
}

//-----------�ҵĴ���
void CMFCActiveXCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	//Invalidate();//
	if(AmbientUserMode())//��������ʱ����,��Ƶ�ʱ�����,ActiveX Control Test Container��,Option->Design Mode
		InvalidateControl();//��Invalidate()������ͬ
	
	COleControl::OnTimer(nIDEvent);
}
  
void CMFCActiveXCtrl::Hello(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	AfxMessageBox(L"Hello");//ֻ��ActiveX Control Test Container�в��Բſɿ���������
	// TODO: Add your dispatch handler code here
}
 
void CMFCActiveXCtrl::OnmyintervalChanged(void)//�ⲿ�޸�����ʱ����,��myinterval
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//-----------�ҵĴ���
	//wchar_t data[50];
	//swprintf(data,L"m_myinterval=%d",m_myinterval);
	//AfxMessageBox(data);
	if(m_myinterval<0 || m_myinterval>6000)
		m_myinterval = 6000;
	else
		m_myinterval = m_myinterval/1000*1000;//ȡ��
	KillTimer(1);//��ʶ
	SetTimer(1,m_myinterval,NULL);
	
	BoundPropertyChanged(3);//3��"o-O"ͼ����� mynterval����ǰ��IDֵ,֪ͨ��������ֵ
	//-----------�ҵĴ���

	SetModifiedFlag();
}
