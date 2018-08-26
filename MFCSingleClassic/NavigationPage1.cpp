// NavigationPage1.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "NavigationPage1.h"
#include "afxdialogex.h"

#include "NavigationSheet.h"//����NavigationPage1.h����,����NavigationPage1.c�оͿ���???
// NavigationPage1 dialog

IMPLEMENT_DYNAMIC(NavigationPage1, CPropertyPage)

NavigationPage1::NavigationPage1()
	: CPropertyPage(NavigationPage1::IDD)
{

	m_occupation = -1;//0��ʾ��һ������
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
	 //---�ҵĴ���
	((NavigationSheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);//|PSWIZB_DISABLEDFINISH
	
	return CPropertyPage::OnSetActive();
}


LRESULT NavigationPage1::OnWizardNext()
{
	 //---�ҵĴ���
	UpdateData(TRUE);//�µ�����
	if(m_occupation==-1)
	{
		MessageBox(_T("��ѡ��ְҵ!"));
		return -1;
	}
	if(m_workLocation==_T(""))
	{
		MessageBox(_T("��ѡ�����ص�!"));
		return -1;
	}

	return CPropertyPage::OnWizardNext();
}


BOOL NavigationPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	
	//----�ҵĴ���,��ʼ��ListBox
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("����"));
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("�Ϻ�"));


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
