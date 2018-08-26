// NavigationPage1.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "NavigationPage1.h"
#include "afxdialogex.h"

#include "NavigationSheet.h"//放在NavigationPage1.h不行,放在NavigationPage1.c中就可以???
// NavigationPage1 dialog

IMPLEMENT_DYNAMIC(NavigationPage1, CPropertyPage)

NavigationPage1::NavigationPage1()
	: CPropertyPage(NavigationPage1::IDD)
{

	m_occupation = -1;//0表示第一个被中
	m_workLocation = _T("");
}

NavigationPage1::~NavigationPage1()
{
}

void NavigationPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_occupation);
	DDX_LBString(pDX, IDC_LIST1, m_workLocation);
}


BEGIN_MESSAGE_MAP(NavigationPage1, CPropertyPage)
END_MESSAGE_MAP()


// NavigationPage1 message handlers


BOOL NavigationPage1::OnSetActive()
{
	 //---我的代码
	((NavigationSheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);//|PSWIZB_DISABLEDFINISH
	
	return CPropertyPage::OnSetActive();
}


LRESULT NavigationPage1::OnWizardNext()
{
	 //---我的代码
	UpdateData(TRUE);//新的数据
	if(m_occupation==-1)
	{
		MessageBox(_T("请选择职业!"));
		return -1;
	}
	if(m_workLocation==_T(""))
	{
		MessageBox(_T("请选择工作地点!"));
		return -1;
	}

	return CPropertyPage::OnWizardNext();
}


BOOL NavigationPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	
	//----我的代码,初始化ListBox
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("北京"));
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("上海"));


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
