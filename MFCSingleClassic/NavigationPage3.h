#pragma once

 
// NavigationPage3 dialog

class NavigationPage3 : public CPropertyPage
{
	DECLARE_DYNAMIC(NavigationPage3)

public:
	NavigationPage3();
	virtual ~NavigationPage3();

// Dialog Data
	enum { IDD = IDD_PROPPAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();
	virtual BOOL OnWizardFinish();
};
