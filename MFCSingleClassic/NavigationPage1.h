#pragma once


//#include "NavigationSheet.h"//����NavigationPage1.h����,����NavigationPage1.c�оͿ���???

// NavigationPage1 dialog

class NavigationPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(NavigationPage1)

public:
	NavigationPage1();
	virtual ~NavigationPage1();

// Dialog Data
	enum { IDD = IDD_PROPPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	int m_occupation;
	virtual LRESULT OnWizardNext();
	virtual BOOL OnInitDialog();
	CString m_workLocation;
};
