// MyShape.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleScroll.h"
#include "MyShape.h"


// MyShape
IMPLEMENT_SERIAL(MyShape,CObject,1) //Ϊ�����Serialize,1�ǰ汾��
MyShape::MyShape()
{
}
MyShape::MyShape(DrawType type,CPoint &start,CPoint &end)
{
	m_drawType=type;
	m_start=start;
	m_end=end;
}
 
void MyShape::Draw(CDC * pDC)//�Լ��ķ�װ
{
	pDC->MoveTo(m_start);
	pDC->LineTo(m_end);
		
	/*
	//���ܶ� >>m_drawType
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
		AfxMessageBox(L"���ڲ˵���ѡ��Ҫ����ͼ��");
	}
	*/
	 
}
MyShape::~MyShape()
{
}


// MyShape member functions
void MyShape::Serialize(CArchive& ar)//Ϊ�����Serialize
{
	if (ar.IsStoring())
	{ 
		ar<<m_start<<m_end;
	}
	else
	{ 
		ar>>m_start>>m_end;//���ܶ� >>m_drawType
	}
}
