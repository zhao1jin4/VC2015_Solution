// MFCActiveXPropPage.cpp : Implementation of the CMFCActiveXPropPage property page class.

#include "stdafx.h"
#include "MFCActiveX.h"
#include "MFCActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMFCActiveXPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CMFCActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMFCActiveXPropPage, "MFCACTIVEX.MFCActiveXPropPage.1",
	0x203275f8, 0x33ea, 0x41c4, 0xa7, 0x71, 0x3f, 0xaa, 0x9b, 0x3d, 0x7d, 0xf3)



// CMFCActiveXPropPage::CMFCActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMFCActiveXPropPage

BOOL CMFCActiveXPropPage::CMFCActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MFCACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CMFCActiveXPropPage::CMFCActiveXPropPage - Constructor

CMFCActiveXPropPage::CMFCActiveXPropPage() :
	COlePropertyPage(IDD, IDS_MFCACTIVEX_PPG_CAPTION)
		, m_dlgInterval(0)//初始化
{

}



// CMFCActiveXPropPage::DoDataExchange - Moves data between page and properties

void CMFCActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);

	DDP_Text(pDX, IDC_EDIT_INTERVAL, m_dlgInterval,_T("Interval"));//--在对话框中自己设计的文本输入框 关联类的成员时,要手工单独加的,没有作用?????????
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_dlgInterval);
	
}



// CMFCActiveXPropPage message handlers
