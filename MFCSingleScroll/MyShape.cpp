// MyShape.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleScroll.h"
#include "MyShape.h"


// MyShape
IMPLEMENT_SERIAL(MyShape,CObject,1) //为对象的Serialize,1是版本号
MyShape::MyShape()
{
}
MyShape::MyShape(DrawType type,CPoint &start,CPoint &end)
{
	m_drawType=type;
	m_start=start;
	m_end=end;
}
 
void MyShape::Draw(CDC * pDC)//自己的封装
{
	pDC->MoveTo(m_start);
	pDC->LineTo(m_end);
		
	/*
	//不能读 >>m_drawType
	switch (m_drawType)
	{
	case T_POINT:
		pDC->SetPixel(m_start.x,m_start.y,RGB(255,0,0));
		break;
	case T_LINE:
		pDC->MoveTo(m_start);
		pDC->LineTo(m_end);
		break;
	case T_ELLIPSE:
		pDC->Ellipse(CRect(m_start,m_end));
		break;
	case T_RECTANGLE:
		pDC->Rectangle(CRect(m_start,m_end));
		break;
	default:
		AfxMessageBox(L"请在菜单中选择要画的图形");
	}
	*/
	 
}
MyShape::~MyShape()
{
}


// MyShape member functions
void MyShape::Serialize(CArchive& ar)//为对象的Serialize
{
	if (ar.IsStoring())
	{ 
		ar<<m_start<<m_end;
	}
	else
	{ 
		ar>>m_start>>m_end;//不能读 >>m_drawType
	}
}
