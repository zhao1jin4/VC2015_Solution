#pragma once
#include "afxwin.h"


// MyDialog dialog

class MyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MyDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	//----------ÎÒµÄ´úÂë
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButtonAdd();
	int m_num1;
	int m_num2;
	int m_sum;
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit_sum;
	afx_msg void OnBnClickedButtonToggle();
	virtual BOOL OnInitDialog();
};
