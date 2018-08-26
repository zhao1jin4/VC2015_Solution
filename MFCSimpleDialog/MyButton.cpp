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


//-----自己扩展的功能
void MyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	//设置第一个按钮的Visible 属性为False
	ShowWindow(SW_HIDE);
	m_pAnother->ShowWindow(SW_SHOW);


	CButton::OnMouseMove(nFlags, point);
}
