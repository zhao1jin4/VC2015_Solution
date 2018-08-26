#pragma once

#include "NavigationPage1.h"
#include "NavigationPage2.h"
#include "NavigationPage3.h"
 
// NavigationSheet

class NavigationSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(NavigationSheet)

public:
	NavigationSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	NavigationSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~NavigationSheet();
	//---ÎÒµÄ´úÂë
	NavigationPage1 m_page1;
	NavigationPage2 m_page2;
	NavigationPage3 m_page3;

protected:
	DECLARE_MESSAGE_MAP()
};


