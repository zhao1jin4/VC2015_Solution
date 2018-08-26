// NavigationSheet.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "NavigationSheet.h"


// NavigationSheet

IMPLEMENT_DYNAMIC(NavigationSheet, CPropertySheet)

NavigationSheet::NavigationSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	
}

NavigationSheet::NavigationSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	//--ÎÒµÄ´úÂë
	AddPage(&m_page1);
	AddPage(&m_page2);
	AddPage(&m_page3);
}

NavigationSheet::~NavigationSheet()
{
}


BEGIN_MESSAGE_MAP(NavigationSheet, CPropertySheet)
END_MESSAGE_MAP()


// NavigationSheet message handlers
