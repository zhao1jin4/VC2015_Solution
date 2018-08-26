
// MFCSinglePipeParentView.h : interface of the CMFCSinglePipeParentView class
//

#pragma once


class CMFCSinglePipeParentView : public CView
{
protected: // create from serialization only
	CMFCSinglePipeParentView();
	DECLARE_DYNCREATE(CMFCSinglePipeParentView)

// Attributes
public:
	CMFCSinglePipeParentDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCSinglePipeParentView();
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
	afx_msg void OnMyPipeRead();
	afx_msg void OnMyPipeWirte();
	HANDLE m_hRead;
	HANDLE m_hWrite;
	afx_msg void OnMyPipeCreate();

	HANDLE m_hNamedPipe;
	afx_msg void OnMyNamedPipeCreate();
	afx_msg void OnMyNamedPipeWrite();
	afx_msg void OnMyNamedPipeRead();
	afx_msg void OnMyMailslotServer();
};

#ifndef _DEBUG  // debug version in MFCSinglePipeParentView.cpp
inline CMFCSinglePipeParentDoc* CMFCSinglePipeParentView::GetDocument() const
   { return reinterpret_cast<CMFCSinglePipeParentDoc*>(m_pDocument); }
#endif

