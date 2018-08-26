
// MFCSinglePipeChildView.h : interface of the CMFCSinglePipeChildView class
//

#pragma once


class CMFCSinglePipeChildView : public CView
{
protected: // create from serialization only
	CMFCSinglePipeChildView();
	DECLARE_DYNCREATE(CMFCSinglePipeChildView)

// Attributes
public:
	CMFCSinglePipeChildDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCSinglePipeChildView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//-------ÎÒµÄ´úÂë
	virtual void OnInitialUpdate();
	HANDLE m_hRead;
	HANDLE m_hWrite;
	afx_msg void OnMyChildPipeRead();
	afx_msg void OnMyChildPipeWirte();
	
	HANDLE m_hNamedPipe;
	afx_msg void OnMyNamedPipeConn();
	afx_msg void OnMyNamedPipeRead();
	afx_msg void OnMyNamedPipeWrite();
	afx_msg void OnMyMailslotClient();
};

#ifndef _DEBUG  // debug version in MFCSinglePipeChildView.cpp
inline CMFCSinglePipeChildDoc* CMFCSinglePipeChildView::GetDocument() const
   { return reinterpret_cast<CMFCSinglePipeChildDoc*>(m_pDocument); }
#endif

