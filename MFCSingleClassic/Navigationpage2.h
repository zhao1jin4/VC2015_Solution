#pragma once

 
// NavigationPage2 dialog

class NavigationPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(NavigationPage2)

public:
	NavigationPage2();
	virtual ~NavigationPage2();

// Dialog Data
	enum { IDD = IDD_PROPPAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
