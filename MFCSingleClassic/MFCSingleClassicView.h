
// MFCSingleClassicView.h : interface of the CMFCSingleClassicView class
//

#pragma once
#include "NavigationSheet.h"

class CMFCSingleClassicView : public CView
{
protected: // create from serialization only
	CMFCSingleClassicView();
	DECLARE_DYNCREATE(CMFCSingleClassicView)

// Attributes
public:
	CMFCSingleClassicDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCSingleClassicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()


//------------ÎÒµÄ´úÂë
private :
	CButton m_button;
	CPoint m_startPoint;
	bool m_bDraw;
	CBitmap caretmap;
	CString m_strLine;
	int m_nWidth;
	CMenu dynMenu;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTest();
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnShow();
	afx_msg void OnNavigation();
};

#ifndef _DEBUG  // debug version in MFCSingleClassicView.cpp
inline CMFCSingleClassicDoc* CMFCSingleClassicView::GetDocument() const
   { return reinterpret_cast<CMFCSingleClassicDoc*>(m_pDocument); }
#endif

