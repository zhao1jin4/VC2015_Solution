// MyDialog.cpp : implementation file
//


//#include <string>
//using namespace std;
#include <string.h>
#include <stdio.h>
#include <wchar.h>

#include "stdafx.h"
#include "MFCSingleClassic.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, CDialogEx)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyDialog::IDD, pParent)
{

	m_num1 = 0;
	m_num2 = 0;
	m_sum = 0;
}

MyDialog::~MyDialog()
{
}


void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//�Լ�ʹ��classwizard ���ɵ�,�ı���󶨱���
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDV_MinMaxInt(pDX, m_num1, -1000, 2000);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT3, m_sum);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit_sum);
}

BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &MyDialog::OnBnClickedButtonAdd)//��������
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE, &MyDialog::OnBnClickedButtonToggle)//��������
END_MESSAGE_MAP()



//-----�ҵĴ���
void MyDialog::OnOK()//DefaultButtonΪtrue Ĭ�ϰ�ť,��رմ���,��OK��ťɾ��ʱ,���س�Ҳִ������,�ټ�ʱID����ΪIDOK
{
	//GetDlgItem(IDC_EDIT1)->GetNextWindow()->SetFocus();//���������ı���multilineΪfalse
	//GetFocus()->GetNextWindow()->SetFocus();//û��Ч��???�����һ����SetFocus �ͱ���
	GetNextDlgTabItem(GetFocus())->SetFocus();


	//CDialogEx::OnOK();
	//DestroyWindow();//ע��Ϊ�ڵ�һ���ı����а��س����ڶ�
}
//-----�ҵĴ���
void MyDialog::OnCancel()
{
	CDialogEx::OnCancel();
	DestroyWindow();
}
//-----�ҵĴ���
void MyDialog::OnBnClickedButtonAdd()
{
	CString str;
	GetDlgItem(IDC_NUMBER1)->GetWindowTextW(str);
	if(str == "first")//CString ������ ==
		GetDlgItem(IDC_NUMBER1)->SetWindowTextW(_T("��һ����"));
	else
		GetDlgItem(IDC_NUMBER1)->SetWindowTextW(_T("first"));

	/*
	//����
	CString str1;
	CString str2;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1);
	//����
	GetDlgItemText(IDC_EDIT2,str2);// �൱�� GetDlgItem(IDC_EDIT2)->GetWindowText(str2)
 
	const wchar_t * w_str1= str1.GetString();
	const wchar_t * w_str2= str2.GetString();
	double num1= wcstod(w_str1,NULL);
	double num2= wcstod(w_str2,NULL);
	double sum=num1+num2;
	wchar_t *result=new wchar_t[sizeof(double)];//Ҫ��ָ�� new ,����������
	swprintf(result,L"%lf",sum);
	//result[7]='\0';//�ɲ���

	SetDlgItemText(IDC_EDIT3,CString(result) );
 */


 /*
	//����
	BOOL isNum;
	int num1=GetDlgItemInt(IDC_EDIT1,&isNum);//�ɸ���
	int num2=GetDlgItemInt(IDC_EDIT2,&isNum);
	int sum=num1+num2;
	
	char sum_char[10];
	itoa(sum,sum_char,10);
	CString c_sum(sum_char);//��char* �� CString OK
	GetDlgItem(IDC_EDIT3)->SetWindowText(c_sum);
	*/

	/*
	//����
	//ʹ�ð󶨱��� 
	//���һ��������,��������ĸ�ͱ���,  �������õķ�ΧҲ�ᱨ��
	this->UpdateData(TRUE);//TRUE��ʾ������ʼ��
	this->m_sum=this->m_num1 + this->m_num2;
	this->UpdateData(FALSE);//��ʾ����ֵ���
	*/

	/*
	//����
	//ʹ�ð���CEdit
	CString edit1Str ;
	CString edit2Str ;
	this->m_edit1.GetWindowTextW(edit1Str);
	this->m_edit2.GetWindowTextW(edit2Str);
 
	const wchar_t * w_str1= edit1Str.GetString();
	const wchar_t * w_str2= edit2Str.GetString();
	double num1= wcstod(w_str1,NULL);
	double num2= wcstod(w_str2,NULL);
	double sum=num1+num2;
	wchar_t *result=new wchar_t[sizeof(double)];//Ҫ��ָ�� new ,����������
	swprintf(result,L"%lf",sum);
	//result[7]='\0';//�ɲ���

	this->m_edit_sum.SetWindowTextW(CString(result));
	*/

	//����
	wchar_t w_str1[10];
	wchar_t w_str2[10];
	//::SendMessage(m_edit1.m_hWnd,WM_GETTEXT,10,(LPARAM)str1);//��һ�� wparam �����,
	//GetDlgItem(IDC_NUMBER1)->SendMessage(WM_GETTEXT,10,(LPARAM)str1);
	m_edit1.SendMessage(WM_GETTEXT,10,(LPARAM)w_str1);
	m_edit2.SendMessage(WM_GETTEXT,10,(LPARAM)w_str2);
	double num1= wcstod(w_str1,NULL);
	double num2= wcstod(w_str2,NULL);
	double sum=num1+num2;
	wchar_t *result=new wchar_t[sizeof(double)];//Ҫ��ָ�� new ,����������
	swprintf(result,L"%lf",sum);
	//m_edit_sum.SendMessage(WM_SETTEXT,0,(LPARAM)result);//wParamû��ʹ��Ϊ0
	//����
	SendDlgItemMessage(IDC_EDIT3,WM_SETTEXT,0,(LPARAM)result);//ʹ��ID,�൱��GetDlgItem(IDC_EDIT3)->SendMessage(WM_SETTEXT,0,(LPARAM)result)

	m_edit_sum.SetFocus();//�õ�����
	SendDlgItemMessage(IDC_EDIT3,EM_SETSEL,0,-1);//lParam,����λ��,-1��β��
}

//---�ҵĴ���
void MyDialog::OnBnClickedButtonToggle()
{
	
	CString str;
	if( GetDlgItemText(IDC_BUTTON_TOGGLE,str) , str==_T("����<<") )//���ű��ʽ
	{
		SetDlgItemText(IDC_BUTTON_TOGGLE,_T("չ��>>"));
	}else
	{
		SetDlgItemText(IDC_BUTTON_TOGGLE,_T("����<<"));
	}
	
	static CRect smallRect;
	static CRect largeRect;
	
	if( largeRect.IsRectNull())//�Ľ�ȫΪ0
		//largeRect.IsRectEmpty() //����Ϊ0
		
	{
		GetWindowRect(&largeRect);
		CRect separator;
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&separator);
		smallRect.left=largeRect.left;
		smallRect.right=largeRect.right;
		smallRect.top=largeRect.top;
		smallRect.bottom=separator.bottom;
	}
	if( str==_T("����<<") )
	{
		SetWindowPos(NULL,0,0,smallRect.Width(),smallRect.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}else
	{
 		SetWindowPos(NULL,0,0,largeRect.Width(),largeRect.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}
}

//---�ҵĴ���,�ֹ���д�� virtual����,�� WM_INITDIALOG��Ϣ,����VS2010�� class wizard���Ҳ���
//�������ڵ�һ�ı����а��س�ʱ�����ڶ����ı�����,Ҫ�޸�Multiline����Ϊtrue
WNDPROC previous;
LRESULT CALLBACK myProc(//��WNDCLASS�и���
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
	if(uMsg==WM_CHAR  && wParam =='\r')//����ʱ��Ҫ�Ӷϵ�,��ʧȥ����
	{
		//::SetFocus(::GetNextWindow(hwnd,GW_HWNDNEXT));
		//::SetFocus(::GetWindow(hwnd,GW_HWNDNEXT));
		::SetFocus(::GetNextDlgTabItem(::GetParent(hwnd),hwnd,FALSE));//FALSE��ʾ��һ��
		return 1;
	}else
	{
		return previous(hwnd, uMsg,wParam, lParam);
	}
}

BOOL MyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	previous=(WNDPROC)SetWindowLong(GetDlgItem(IDC_EDIT1)->m_hWnd,GWL_WNDPROC,(LONG)myProc);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
