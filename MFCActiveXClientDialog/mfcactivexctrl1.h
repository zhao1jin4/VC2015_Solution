#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CMfcactivexctrl1 wrapper class

class CMfcactivexctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMfcactivexctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x603943F6, 0x2DA0, 0x4936, { 0xBD, 0x18, 0xDA, 0xE8, 0xB9, 0xBA, 0xCB, 0xF5 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:


// Operations
public:

// _DMFCActiveX

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Hello()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

unsigned long GetForeColor()
{
	unsigned long result;
	GetProperty(DISPID_FORECOLOR, VT_UI4, (void*)&result);
	return result;
}
void SetForeColor(unsigned long propVal)
{
	SetProperty(DISPID_FORECOLOR, VT_UI4, propVal);
}
unsigned long GetBackColor()
{
	unsigned long result;
	GetProperty(DISPID_BACKCOLOR, VT_UI4, (void*)&result);
	return result;
}
void SetBackColor(unsigned long propVal)
{
	SetProperty(DISPID_BACKCOLOR, VT_UI4, propVal);
}
short Getmyinterval()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}
void Setmyinterval(short propVal)
{
	SetProperty(0x3, VT_I2, propVal);
}


};