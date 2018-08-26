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

	//自己使用classwizard 生成的,文本框绑定变量
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDV_MinMaxInt(pDX, m_num1, -1000, 2000);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT3, m_sum);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit_sum);
}

BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &MyDialog::OnBnClickedButtonAdd)//这是生成
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE, &MyDialog::OnBnClickedButtonToggle)//这是生成
END_MESSAGE_MAP()



//-----我的代码
void MyDialog::OnOK()//DefaultButton为true 默认按钮,会关闭窗口,当OK按钮删除时,按回车也执行这里,再加时ID必须为IDOK
{
	//GetDlgItem(IDC_EDIT1)->GetNextWindow()->SetFocus();//对于设置文本的multiline为false
	//GetFocus()->GetNextWindow()->SetFocus();//没有效果???到最后一个再SetFocus 就报错
	GetNextDlgTabItem(GetFocus())->SetFocus();


	//CDialogEx::OnOK();
	//DestroyWindow();//注释为在第一个文本框中按回车到第二
}
//-----我的代码
void MyDialog::OnCancel()
{
	CDialogEx::OnCancel();
	DestroyWindow();
}
//-----我的代码
void MyDialog::OnBnClickedButtonAdd()
{
	CString str;
	GetDlgItem(IDC_NUMBER1)->GetWindowTextW(str);
	if(str == "first")//CString 可以用 ==
		GetDlgItem(IDC_NUMBER1)->SetWindowTextW(_T("第一个数"));
	else
		GetDlgItem(IDC_NUMBER1)->SetWindowTextW(_T("first"));

	/*
	//方法
	CString str1;
	CString str2;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1);
	//方法
	GetDlgItemText(IDC_EDIT2,str2);// 相当于 GetDlgItem(IDC_EDIT2)->GetWindowText(str2)
 
	const wchar_t * w_str1= str1.GetString();
	const wchar_t * w_str2= str2.GetString();
	double num1= wcstod(w_str1,NULL);
	double num2= wcstod(w_str2,NULL);
	double sum=num1+num2;
	wchar_t *result=new wchar_t[sizeof(double)];//要用指针 new ,不能用数组
	swprintf(result,L"%lf",sum);
	//result[7]='\0';//可不加

	SetDlgItemText(IDC_EDIT3,CString(result) );
 */


 /*
	//方法
	BOOL isNum;
	int num1=GetDlgItemInt(IDC_EDIT1,&isNum);//可负数
	int num2=GetDlgItemInt(IDC_EDIT2,&isNum);
	int sum=num1+num2;
	
	char sum_char[10];
	itoa(sum,sum_char,10);
	CString c_sum(sum_char);//从char* 到 CString OK
	GetDlgItem(IDC_EDIT3)->SetWindowText(c_sum);
	*/

	/*
	//方法
	//使用绑定变量 
	//如第一个是数字,后面是字母就报错,  超出设置的范围也会报错
	this->UpdateData(TRUE);//TRUE表示在正初始化
	this->m_sum=this->m_num1 + this->m_num2;
	this->UpdateData(FALSE);//表示接收值完成
	*/

	/*
	//方法
	//使用绑定类CEdit
	CString edit1Str ;
	CString edit2Str ;
	this->m_edit1.GetWindowTextW(edit1Str);
	this->m_edit2.GetWindowTextW(edit2Str);
 
	const wchar_t * w_str1= edit1Str.GetString();
	const wchar_t * w_str2= edit2Str.GetString();
	double num1= wcstod(w_str1,NULL);
	double num2= wcstod(w_str2,NULL);
	double sum=num1+num2;
	wchar_t *result=new wchar_t[sizeof(double)];//要用指针 new ,不能用数组
	swprintf(result,L"%lf",sum);
	//result[7]='\0';//可不加

	this->m_edit_sum.SetWindowTextW(CString(result));
	*/

	//方法
	wchar_t w_str1[10];
	wchar_t w_str2[10];
	//::SendMessage(m_edit1.m_hWnd,WM_GETTEXT,10,(LPARAM)str1);//第一个 wparam 最大数,
	//GetDlgItem(IDC_NUMBER1)->SendMessage(WM_GETTEXT,10,(LPARAM)str1);
	m_edit1.SendMessage(WM_GETTEXT,10,(LPARAM)w_str1);
	m_edit2.SendMessage(WM_GETTEXT,10,(LPARAM)w_str2);
	double num1= wcstod(w_str1,NULL);
	double num2= wcstod(w_str2,NULL);
	double sum=num1+num2;
	wchar_t *result=new wchar_t[sizeof(double)];//要用指针 new ,不能用数组
	swprintf(result,L"%lf",sum);
	//m_edit_sum.SendMessage(WM_SETTEXT,0,(LPARAM)result);//wParam没有使用为0
	//方法
	SendDlgItemMessage(IDC_EDIT3,WM_SETTEXT,0,(LPARAM)result);//使用ID,相当于GetDlgItem(IDC_EDIT3)->SendMessage(WM_SETTEXT,0,(LPARAM)result)

	m_edit_sum.SetFocus();//得到集点
	SendDlgItemMessage(IDC_EDIT3,EM_SETSEL,0,-1);//lParam,结束位置,-1到尾部
}

//---我的代码
void MyDialog::OnBnClickedButtonToggle()
{
	
	CString str;
	if( GetDlgItemText(IDC_BUTTON_TOGGLE,str) , str==_T("收缩<<") )//逗号表达式
	{
		SetDlgItemText(IDC_BUTTON_TOGGLE,_T("展开>>"));
	}else
	{
		SetDlgItemText(IDC_BUTTON_TOGGLE,_T("收缩<<"));
	}
	
	static CRect smallRect;
	static CRect largeRect;
	
	if( largeRect.IsRectNull())//四角全为0
		//largeRect.IsRectEmpty() //宽或高为0
		
	{
		GetWindowRect(&largeRect);
		CRect separator;
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&separator);
		smallRect.left=largeRect.left;
		smallRect.right=largeRect.right;
		smallRect.top=largeRect.top;
		smallRect.bottom=separator.bottom;
	}
	if( str==_T("收缩<<") )
	{
		SetWindowPos(NULL,0,0,smallRect.Width(),smallRect.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}else
	{
 		SetWindowPos(NULL,0,0,largeRect.Width(),largeRect.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}
}

//---我的代码,手工重写的 virtual函数,有 WM_INITDIALOG消息,但在VS2010的 class wizard中找不到
//用于在在第一文本框中按回车时跳到第二个文本框中,要修改Multiline属性为true
WNDPROC previous;
LRESULT CALLBACK myProc(//从WNDCLASS中复制
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
	if(uMsg==WM_CHAR  && wParam =='\r')//测试时不要加断点,会失去焦点
	{
		//::SetFocus(::GetNextWindow(hwnd,GW_HWNDNEXT));
		//::SetFocus(::GetWindow(hwnd,GW_HWNDNEXT));
		::SetFocus(::GetNextDlgTabItem(::GetParent(hwnd),hwnd,FALSE));//FALSE表示下一个
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
