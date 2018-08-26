#pragma once
#include "MainFrm.h"
#include "MFCSingleToolBarView.h"
#include "afxwin.h"
#include "MyStyleButton.h"
// DrawSettingDlg dialog

class DrawSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DrawSettingDlg)

private :
	void drawSample();
	CBrush m_brush;
	CFont m_font;
public:
	DrawSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~DrawSettingDlg();

// Dialog Data
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nLineWidth;
	int m_lineStyle;
	afx_msg void OnBnClickedMyFont();
	afx_msg void OnEnChangeEditLineWidth();
	afx_msg void OnBnClickedLineSolid();
	afx_msg void OnBnClickedLineDash();
	afx_msg void OnBnClickedLineDot();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

 
	
	MyStyleButton m_btnOK;
};
