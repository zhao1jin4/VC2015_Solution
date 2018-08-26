
// MFCActiveXClientDialogDlg.h : header file
//

#pragma once
#include "mfcactivexctrl1.h"


// CMFCActiveXClientDialogDlg dialog
class CMFCActiveXClientDialogDlg : public CDialogEx
{
// Construction
public:
	CMFCActiveXClientDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCACTIVEXCLIENTDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMfcactivexctrl1 m_myactivex1;
	CMfcactivexctrl1 m_myactivex2;
	afx_msg void OnBnClickedButton1();
};
