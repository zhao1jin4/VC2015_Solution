// NavigationPage3.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "NavigationPage3.h"
#include "afxdialogex.h"

#include "NavigationSheet.h"//����NavigationPage1.h����,����NavigationPage1.c�оͿ���???

// NavigationPage3 dialog

IMPLEMENT_DYNAMIC(NavigationPage3, CPropertyPage)

NavigationPage3::NavigationPage3()
	: CPropertyPage(NavigationPage3::IDD)
{

}

NavigationPage3::~NavigationPage3()
{
}

void NavigationPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NavigationPage3, CPropertyPage)
END_MESSAGE_MAP()


// NavigationPage3 message handlers


BOOL NavigationPage3::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	
	//---�ҵĴ���
	((NavigationSheet*)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);

	return CPropertyPage::OnSetActive();
}
BOOL NavigationPage3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here

	//---�ҵĴ���
	CComboBox * combox=(CComboBox * )GetDlgItem(IDC_COMBO1);

	combox->AddString(_T("1000-3000"));
	combox->AddString(_T("3000-5000"));
	combox->AddString(_T("8000-10000"));
	combox->AddString(_T("10000-15000"));
	//Sort��������ΪFalse
	combox->SetCurSel(1);//���ó�ʼѡ��,��0��ʼ


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL NavigationPage3::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
	
	//---�ҵĴ���
	CComboBox * combox=(CComboBox * )GetDlgItem(IDC_COMBO1);

	int sel=combox->GetCurSel();
	CString salary;
	combox->GetLBText(sel,salary);

	MessageBox(_T("��ѡ�����:"+salary));

	return CPropertyPage::OnWizardFinish();
}
