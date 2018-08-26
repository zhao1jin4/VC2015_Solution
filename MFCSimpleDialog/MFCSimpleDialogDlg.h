
// MFCSimpleDialogDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MyButton.h"
#define WM_MY_MSGSEND WM_USER+1
// CMFCSimpleDialogDlg dialog
class CMFCSimpleDialogDlg : public CDialogEx
{
// Construction
public:
	CMFCSimpleDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCSIMPLEDIALOG_DIALOG };

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
	//---ÎÒµÄ´úÂë
	MyButton m_btn1;
	MyButton m_btn2;
	SOCKET m_mysock;
	void myInitSocket();
	static DWORD WINAPI recvFunc(LPVOID lpParam);
	struct RECVPARAM {
		SOCKET sock;
		HWND hwnd;
	} ;
	afx_msg LRESULT OnMyRecvMsg(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedMySend();
};
