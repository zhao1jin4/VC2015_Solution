
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar        m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private :
	CBitmap mapRight;
	CBitmap mapWrong;
	CButton m_button;

public:
 //----我的代码
	afx_msg void OnShow();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnMyDynMenuItem();
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);//是为Fram中的消息不在向View中传
	afx_msg void  OnShowMyDiag();

};


