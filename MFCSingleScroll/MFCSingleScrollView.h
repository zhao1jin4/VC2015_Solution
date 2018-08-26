
// MFCSingleScrollView.h : interface of the CMFCSingleScrollView class
//

#pragma once

#include "MyShape.h"
class CMFCSingleScrollView : public CScrollView
{
protected: // create from serialization only
	CMFCSingleScrollView();
	DECLARE_DYNCREATE(CMFCSingleScrollView)

// Attributes
public:
	CMFCSingleScrollDoc* GetDocument() const;
	CPtrArray m_allLine;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCSingleScrollView();
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
	virtual void OnInitialUpdate();
private:
	CPoint m_start;
	
	CMetaFileDC m_metaFileDC;
	CDC m_compatibleDC;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnPaint();
	afx_msg void OnDrawSave();
	afx_msg void OnDrawOpen();
};

#ifndef _DEBUG  // debug version in MFCSingleScrollView.cpp
inline CMFCSingleScrollDoc* CMFCSingleScrollView::GetDocument() const
   { return reinterpret_cast<CMFCSingleScrollDoc*>(m_pDocument); }
#endif

