
// MFCAsyncSocketChatDialogDlg.h : header file
//

#pragma once

#define UM_SOCK_READ WM_USER+1 //�û��Զ�����Ϣ

// CMFCAsyncSocketChatDialogDlg dialog
class CMFCAsyncSocketChatDialogDlg : public CDialogEx
{
// Construction
public:
	CMFCAsyncSocketChatDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCASYNCSOCKETCHATDIALOG_DIALOG };

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
	//--------����
	~CMFCAsyncSocketChatDialogDlg();//�ֹ��ӵ�
	afx_msg LRESULT OnMyRecvSock(WPARAM wParam,LPARAM lParam);//�Զ�����Ϣ
	bool MyInitSocket(void);
	SOCKET m_socket;
	afx_msg void OnBnClickedMySend();
private:
	void showError(int err);
};
