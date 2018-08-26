#pragma once

// MFCActiveXPropPage.h : Declaration of the CMFCActiveXPropPage property page class.


// CMFCActiveXPropPage : See MFCActiveXPropPage.cpp for implementation.

class CMFCActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMFCActiveXPropPage)
	DECLARE_OLECREATE_EX(CMFCActiveXPropPage)

// Constructor
public:
	CMFCActiveXPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_MFCACTIVEX };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
public:
	short m_dlgInterval;
};

