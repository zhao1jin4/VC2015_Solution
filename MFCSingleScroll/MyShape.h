#pragma once

// MyShape command target
enum DrawType{T_POINT,T_LINE,T_ELLIPSE,T_RECTANGLE} ;
class MyShape : public CObject //Ϊ����serializable ҪCObject
{
	DECLARE_SERIAL(MyShape)  //Ϊ����serializable ����
public:
	MyShape();//Ҫ���޲����Ĺ��캯��
	MyShape(DrawType type,CPoint &start,CPoint &end);
	void Draw(CDC * pDC);
	virtual ~MyShape();
	virtual void Serialize(CArchive& ar);
private :
	DrawType m_drawType;
	CPoint m_start;
	CPoint m_end;

};


