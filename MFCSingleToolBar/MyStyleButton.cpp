// MyStyleButton.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleToolBar.h"
#include "MyStyleButton.h"


// MyStyleButton

IMPLEMENT_DYNAMIC(MyStyleButton, CWnd)

MyStyleButton::MyStyleButton()
{

}

MyStyleButton::~MyStyleButton()
{
}


BEGIN_MESSAGE_MAP(MyStyleButton, CWnd)
END_MESSAGE_MAP()



// MyStyleButton message handlers




void MyStyleButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//----------�����Ǵ�MSDN�ϸ��Ƶ�

	 UINT uStyle = DFCS_BUTTONPUSH;

   // This code only works with buttons.
   ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

   // If drawing selected, add the pushed style to DrawFrameControl.
   if (lpDrawItemStruct->itemState & ODS_SELECTED)
      uStyle |= DFCS_PUSHED;

   // Draw the button frame.
   ::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
      DFC_BUTTON, uStyle);

   // Get the button's text.
   CString strText;
   GetWindowText(strText);

   // Draw the button text using the text color red.
   COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255,0,0));
   ::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
      &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
   ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}
