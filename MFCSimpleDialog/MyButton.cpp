// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSimpleDialog.h"
#include "MyButton.h"


// MyButton

IMPLEMENT_DYNAMIC(MyButton, CButton)

MyButton::MyButton()
{

}

MyButton::~MyButton()
{
}


BEGIN_MESSAGE_MAP(MyButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// MyButton message handlers


//-----�Լ���չ�Ĺ���
void MyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	//���õ�һ����ť��Visible ����ΪFalse
	ShowWindow(SW_HIDE);
	m_pAnother->ShowWindow(SW_SHOW);


	CButton::OnMouseMove(nFlags, point);
}
