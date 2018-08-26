// Navigationpage2.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "NavigationPage2.h"
#include "afxdialogex.h"

#include "NavigationSheet.h"//放在NavigationPage1.h不行,放在NavigationPage1.c中就可以???

// NavigationPage2 dialog

IMPLEMENT_DYNAMIC(NavigationPage2, CPropertyPage)

NavigationPage2::NavigationPage2()
	: CPropertyPage(NavigationPage2::IDD)
{

}

NavigationPage2::~NavigationPage2()
{
}

void NavigationPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NavigationPage2, CPropertyPage)
END_MESSAGE_MAP()


// NavigationPage2 message handlers


BOOL NavigationPage2::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	 
	//---我的代码
	((NavigationSheet*)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);//|PSWIZB_DISABLEDFINISH
 
	return CPropertyPage::OnSetActive();
}
