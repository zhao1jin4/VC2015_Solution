
// MFCSingleToolBarView.h : interface of the CMFCSingleToolBarView class
//

#pragma once
#include "MainFrm.h"
#include "MFCSingleToolBarDoc.h"
#include "DrawSettingDlg.h"
class CMFCSingleToolBarView : public CListView
{
protected: // create from serialization only
	CMFCSingleToolBarView();
	DECLARE_DYNCREATE(CMFCSingleToolBarView)

// Attributes
public:
	CMFCSingleToolBarDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMFCSingleToolBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPoint();
	afx_msg void OnRectangle();
	afx_msg void OnLine();
	afx_msg void OnEllipse();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPoint m_firstPoint;
	enum DrawType{T_POINT,T_LINE,T_ELLIPSE,T_RECTANGLE} m_drawType;
	afx_msg void OnSetting();
	unsigned int m_lineWith;
	int m_lineStyle;
	afx_msg void OnChooseColor();
	COLORREF m_color;
	CFont m_font;
	virtual void OnDraw(CDC* /*pDC*/);
 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in MFCSingleToolBarView.cpp
inline CMFCSingleToolBarDoc* CMFCSingleToolBarView::GetDocument() const
   { return reinterpret_cast<CMFCSingleToolBarDoc*>(m_pDocument); }
#endif

