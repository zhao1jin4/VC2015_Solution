#pragma once

// MFCActiveXCtrl.h : Declaration of the CMFCActiveXCtrl ActiveX Control class.


// CMFCActiveXCtrl : See MFCActiveXCtrl.cpp for implementation.

class CMFCActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMFCActiveXCtrl)

// Constructor
public:
	CMFCActiveXCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CMFCActiveXCtrl();

	DECLARE_OLECREATE_EX(CMFCActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMFCActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMFCActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMFCActiveXCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidmyinterval = 3,
		dispidInterval = 3,
		eventidNewMinute = 1L,
		dispidNewMinute = 1L,
		dispidHello = 2L,
		dispidinterval = 1
	};

	//-----------生成代码声明
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	void OnmyintervalChanged(void);
	SHORT m_myinterval;
	void Hello(void);
	void NewMinute(void)
	{
		FireEvent(eventidNewMinute, EVENT_PARAM(VTS_NONE));
	}
public:
 
	
};

